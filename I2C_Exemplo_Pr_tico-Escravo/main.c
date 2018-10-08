/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c escravo
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Descri��o:		Configura o PIC para trabalhar como escravo de 7 bits
 *                      Esse firmware reconhece somente um comando, mas pode ser
 *                      usado como base para projetos mais complexos.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>// Biblioteca do compilador C18 com configura�oes da
                    // fam�lia PIC18

#include <i2c.h>// Biblioteca do compilador C18 com fun�oes para uso do m�dulo
                // I2C

/** V A R I A V E I S   G L O B A I S ****************************************/
unsigned char codigo = 0;

/**  P R O T O T I P O S   D A S   F U N � � E S   D E   I N T E R R U P � � O*/
void ConfiguraInterrupcao(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:      void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa
 *		principal, e isto � relacionado a esta fun��o pois eh a
 *		mesma � a primeira a ser chamada apos o reset da PIC.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{
    // Configura todos os pinos como digitais
    ADCON1 |= 0x0F;
    
    // Configura��o dos pinos conforme pedido no Datasheet
    TRISBbits.TRISB0 = 1;// Configura o pino RB0(SDA) como entrada 
    TRISBbits.TRISB1 = 1;// Configura o pino RB1(SCL) como entrada 
    
    TRISCbits.TRISC2 = 0;// Configura o pino RC1 como sa�da (LED)

    // Modo escravo de 7 bits e comunica��o de 100kHz
    OpenI2C(SLAVE_7, SLEW_OFF);
    // Define o endere�o do perif�rico Slave no barramento I2C
    SSPADD = 0xA0;

    // Fun��o que configura as interrup��es do sistema
    ConfiguraInterrupcao();

    // Inicia o programa com o LED desligado
    LATCbits.LATC2 = 0;

    // Habilita��o GERAL DE TODAS as interrup��es
    INTCONbits.GIE = 1;

    while (1)
    {
        // Executa fun��o de acordo com o Byte recebido no barramento I2C
        if (codigo == 1)
        {
            // Inverte o estado do LED
            LATCbits.LATC2 = !LATCbits.LATC2;
            codigo = 0;// Coloca o c�digo em 0 para uma nova leitura
        }// Fim if
    }// end while(1)
}//end main

/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Fun��o que configura as interrup��es utilizadas no projeto
 *
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
    RCONbits.IPEN = 0;// Desabilita prioridade de interrup��o
    INTCONbits.GIE = 0;// Desabilita TODAS as interrup��es

    INTCONbits.PEIE = 1;// Habilita interrup��o de perif�ricos

    // Configura��es da interrup��o do m�dulo I2C
    IPR1bits.SSPIP = 1;// Interrup��o tratada no vetor de Alta Prioridade
    PIE1bits.SSPIE = 1;// Habilita a interrup��o de SSP (I2C)
    PIR1bits.SSPIF = 0;// Limpa o flag da interrup��o de SSP (I2C)

}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de ALTA prioridade
 *		Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup��o, comparando
 *                          os flags de cada tipo de interrup��o.
 *			2- tratar a interrup��o selecionada.
 *			3- limpar o flag que causou a interrup��o!!! Importante
 *		para garantir que n�o ocorrer� uma chamada indesejada ao sair
 *		do tratamento da interrup��o.
 *
 *		Ao sair dessa fun��o � usado o retorno do tipo "retfie fast",
 *		pois esta fun��o � declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
    // Testa se ocorreu interrup��o de I2C
    if(PIR1bits.SSPIF)
    {
        unsigned char estado = 0;

        // Le o status do I2C para descobrir o tipo de Byte recebido
        //bit0 	BufferFull:   0=vazio            1=cheio
        //bit1  X             X                  X
        //bit2 	Read/Write:   0=Escrita          1=Leitura
        //bit3 	Start:        0=N�o Start        1=Start
        //bit4  Stop:         0=N�o Stop         1=Stop
        //bit5 	Data/Address: 0=Address          1=Data
        //bit6  X             X                  X
        //bit7  X             X                  X
        estado = (SSPSTAT&0b00101101);
        switch (estado)
        {
            // estado 1: Buffer est� cheio, e o byte recebido foi um ENDERE�O
            // Endere�o recebido, leitura deve ser feita para se esvaziar
            // o buffer
            case 0b00001001:
            /* 
             * bit0 = 1 Buffer est� cheio
             * bit1 = X X 
             * bit2 = 0 Opera��o de escrita
             * bit3 = 1 Start recebido
             * bit4 = 0 Stop n�o recebido
             * bit5 = 0 Byte recebido � um endere�o
             * bit6 = X X
             * bit7 = X X 
             */
                // Leitura do Buffer para zera a flag
                ReadI2C();
            break;

            // estado 2: Buffer est� cheio e o byte recebido foi um DADO.
            // Opera��o de escrita
            // Dado recebido. Deve-se armazenar o dado recebido e trata-lo no
            // while(1)
            case 0b00101001:
            /* 
             * bit0 = 1 Buffer est� cheio
             * bit1 = X X 
             * bit2 = 0 Opera��o de escrita
             * bit3 = 1 Start
             * bit4 = 0 Stop n�o recebido
             * bit5 = 1 Byte recebido � um dado
             * bit6 = X X
             * bit7 = X X 
             */
                // Armazenamos o byte recebido na vari�vel codigo para trata-lo
                // posteriormente no while(1)
                codigo = ReadI2C();
            break;

            // estado 3: Buffer cheio, byte recebido � um endere�o
            // Opera��o de Leitura
            case 0b00001101:
            /*
             * bit0 = 1 Buffer est� cheio
             * bit1 = X X
             * bit2 = 1 Opera��o de leitura
             * bit3 = 1 Start
             * bit4 = 0 Stop n�o recebido
             * bit5 = 0 Byte recebido � um endere�o
             * bit6 = X X
             * bit7 = X X
             */
                //Envia o dado solicitado pelo mestre
                WriteI2C(1);
            break;
        }
        // Limpa o flag da interrup��o do I2C
        PIR1bits.SSPIF = 0;
    }// Fim if
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:	void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de BAIXA prioridade
 *		Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup��o, comparando
 *                          os flags de cada tipo de interrup��o.
 *			2- tratar a interrup��o selecionada.
 *			3- limpar o flag que causou a interrup��o!!! Importante
 *                          para garantir que n�o ocorrer� uma chamada
 *                          indesejada ao sair do tratamento da interrup��o.
 *
 *		Ao sair dessa fun��o � usado o retorno do tipo "retfie",
 *		pois esta fun��o � declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrup��o de baixa prioridade aqui

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Se��o necess�ria para informar ao compilador C18 onde s�o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup��o.
//
//ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
//UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal
// no endere�o 0x800 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x808 da mem�ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x001008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de BAIXA prioridade
// no endere�o 0x818 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x001018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code  	// Diretiva que retorna a aloca��o dos endere�os
				// da mem�ria de programa para seus valores padr�o
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/