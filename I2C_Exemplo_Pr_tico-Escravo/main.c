/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c escravo
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:		HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Descrição:		Configura o PIC para trabalhar como escravo de 7 bits
 *                      Esse firmware reconhece somente um comando, mas pode ser
 *                      usado como base para projetos mais complexos.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>// Biblioteca do compilador C18 com configuraç±oes da
                    // família PIC18

#include <i2c.h>// Biblioteca do compilador C18 com funç±oes para uso do módulo
                // I2C

/** V A R I A V E I S   G L O B A I S ****************************************/
unsigned char codigo = 0;

/**  P R O T O T I P O S   D A S   F U N Ç Õ E S   D E   I N T E R R U P Ç Ã O*/
void ConfiguraInterrupcao(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:      void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa
 *		principal, e isto é relacionado a esta função pois eh a
 *		mesma é a primeira a ser chamada apos o reset da PIC.
 *		Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{
    // Configura todos os pinos como digitais
    ADCON1 |= 0x0F;
    
    // Configuração dos pinos conforme pedido no Datasheet
    TRISBbits.TRISB0 = 1;// Configura o pino RB0(SDA) como entrada 
    TRISBbits.TRISB1 = 1;// Configura o pino RB1(SCL) como entrada 
    
    TRISCbits.TRISC2 = 0;// Configura o pino RC1 como saída (LED)

    // Modo escravo de 7 bits e comunicação de 100kHz
    OpenI2C(SLAVE_7, SLEW_OFF);
    // Define o endereço do periférico Slave no barramento I2C
    SSPADD = 0xA0;

    // Função que configura as interrupções do sistema
    ConfiguraInterrupcao();

    // Inicia o programa com o LED desligado
    LATCbits.LATC2 = 0;

    // Habilitação GERAL DE TODAS as interrupções
    INTCONbits.GIE = 1;

    while (1)
    {
        // Executa função de acordo com o Byte recebido no barramento I2C
        if (codigo == 1)
        {
            // Inverte o estado do LED
            LATCbits.LATC2 = !LATCbits.LATC2;
            codigo = 0;// Coloca o código em 0 para uma nova leitura
        }// Fim if
    }// end while(1)
}//end main

/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Saída:          Nenhuma (void)
 * Descrição:      Função que configura as interrupções utilizadas no projeto
 *
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
    RCONbits.IPEN = 0;// Desabilita prioridade de interrupção
    INTCONbits.GIE = 0;// Desabilita TODAS as interrupções

    INTCONbits.PEIE = 1;// Habilita interrupção de periféricos

    // Configurações da interrupção do módulo I2C
    IPR1bits.SSPIP = 1;// Interrupção tratada no vetor de Alta Prioridade
    PIE1bits.SSPIE = 1;// Habilita a interrupção de SSP (I2C)
    PIR1bits.SSPIF = 0;// Limpa o flag da interrupção de SSP (I2C)

}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de ALTA prioridade
 *		Nessa função deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupção, comparando
 *                          os flags de cada tipo de interrupção.
 *			2- tratar a interrupção selecionada.
 *			3- limpar o flag que causou a interrupção!!! Importante
 *		para garantir que não ocorrerá uma chamada indesejada ao sair
 *		do tratamento da interrupção.
 *
 *		Ao sair dessa função é usado o retorno do tipo "retfie fast",
 *		pois esta função é declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
    // Testa se ocorreu interrupção de I2C
    if(PIR1bits.SSPIF)
    {
        unsigned char estado = 0;

        // Le o status do I2C para descobrir o tipo de Byte recebido
        //bit0 	BufferFull:   0=vazio            1=cheio
        //bit1  X             X                  X
        //bit2 	Read/Write:   0=Escrita          1=Leitura
        //bit3 	Start:        0=Não Start        1=Start
        //bit4  Stop:         0=Não Stop         1=Stop
        //bit5 	Data/Address: 0=Address          1=Data
        //bit6  X             X                  X
        //bit7  X             X                  X
        estado = (SSPSTAT&0b00101101);
        switch (estado)
        {
            // estado 1: Buffer está cheio, e o byte recebido foi um ENDEREÇO
            // Endereço recebido, leitura deve ser feita para se esvaziar
            // o buffer
            case 0b00001001:
            /* 
             * bit0 = 1 Buffer está cheio
             * bit1 = X X 
             * bit2 = 0 Operação de escrita
             * bit3 = 1 Start recebido
             * bit4 = 0 Stop não recebido
             * bit5 = 0 Byte recebido é um endereço
             * bit6 = X X
             * bit7 = X X 
             */
                // Leitura do Buffer para zera a flag
                ReadI2C();
            break;

            // estado 2: Buffer está cheio e o byte recebido foi um DADO.
            // Operação de escrita
            // Dado recebido. Deve-se armazenar o dado recebido e trata-lo no
            // while(1)
            case 0b00101001:
            /* 
             * bit0 = 1 Buffer está cheio
             * bit1 = X X 
             * bit2 = 0 Operação de escrita
             * bit3 = 1 Start
             * bit4 = 0 Stop não recebido
             * bit5 = 1 Byte recebido é um dado
             * bit6 = X X
             * bit7 = X X 
             */
                // Armazenamos o byte recebido na variável codigo para trata-lo
                // posteriormente no while(1)
                codigo = ReadI2C();
            break;

            // estado 3: Buffer cheio, byte recebido é um endereço
            // Operação de Leitura
            case 0b00001101:
            /*
             * bit0 = 1 Buffer está cheio
             * bit1 = X X
             * bit2 = 1 Operação de leitura
             * bit3 = 1 Start
             * bit4 = 0 Stop não recebido
             * bit5 = 0 Byte recebido é um endereço
             * bit6 = X X
             * bit7 = X X
             */
                //Envia o dado solicitado pelo mestre
                WriteI2C(1);
            break;
        }
        // Limpa o flag da interrupção do I2C
        PIR1bits.SSPIF = 0;
    }// Fim if
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:	void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de BAIXA prioridade
 *		Nessa função deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupção, comparando
 *                          os flags de cada tipo de interrupção.
 *			2- tratar a interrupção selecionada.
 *			3- limpar o flag que causou a interrupção!!! Importante
 *                          para garantir que não ocorrerá uma chamada
 *                          indesejada ao sair do tratamento da interrupção.
 *
 *		Ao sair dessa função é usado o retorno do tipo "retfie",
 *		pois esta função é declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrupção de baixa prioridade aqui

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Seção necessária para informar ao compilador C18 onde são os novos endereços
//da memória de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupção.
//
//ATENÇÃO: COPIAR ESTA SEÇÃO DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
//UTILIZAM O BOOTLOADER PARA GRAVAÇÃO IN-CIRCUIT.

// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal
// no endereço 0x800 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Alocação da função de tratamento das interrupções de ALTA prioridade
// no endereço 0x808 da memória de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x001008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Alocação da função de tratamento das interrupções de BAIXA prioridade
// no endereço 0x818 da memória de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x001018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code  	// Diretiva que retorna a alocação dos endereços
				// da memória de programa para seus valores padrão
/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/