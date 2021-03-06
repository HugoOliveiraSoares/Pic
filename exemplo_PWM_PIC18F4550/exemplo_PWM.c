/******************************************************************************
 *
 *            PICMINAS PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:        	C18 v3.37 ou superior
 * Empresa:         	PICMinas
 * Pr�tica:
 * Plataforma:			Placa PICMINAS18 v3.6
 * Autor:				PICMinas
 * Vers�o:				v1.0
 * Descri��o:
 *
 *
 *
 *
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>// Necess�rio para que o compilador adicione a biblioteca
                   // com as defini��es do PIC selecionado no projeto, neste
                  // caso, o modelo 18F4550.

#include <pwm.h>    // Necess�rio para que o modo PWM funcione
#include <timers.h>// Necess�rio porque o PWM usa o timer2

/** D E F I N E S ************************************************************/

/** V A R I A V E I S   G L O B A I S ****************************************/

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);

/**  P R O T O T I P O S   D A S   F U N � � E S   D E   I N T E R R U P � � O*/
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

/** F U N C O E S ************************************************************/

void main(void)
{
	ConfiguraSistema();	// Configura as portas e perif�ricos do PIC.

        // La�o infinito que executa a opera��o principal do projeto.
	while (1)
	{
            // Fun��o que determina o valor do Duty Cycle, 0 a 1023
            SetDCPWM1(376); // Nesse caso 50%

        }//end while
}//end main

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	ConfiguraSistema � a rotina de configura��o principal do projeto.
 *				Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *				do microcontrolador para que operem da maneira desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema (void)
{
	// Desabilita todas as 13 portas anal�gicas ANx
        // assim as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;

        //Configura o pino RC2 como saida digital
        TRISCbits.TRISC2 = 0;
        LATCbits.LATC2 = 0 ;

        // Liga o timer2 com prescale de 16
	OpenTimer2( TIMER_INT_OFF & T0_PS_1_16 ) ;

        // Fun��o que habilita e configura a frequencia do PWM, 0 a 255
        OpenPWM1(187); // Nesse caso 4KHz

}//end ConfiguraSistema 


/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de ALTA prioridade
 *				Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *					1- verificar qual foi a causa da interrup��o, comparando
 *				os flags de cada tipo de interrup��o.
 *					2- tratar a interrup��o selecionada.
 *					3- limpar o flag que causou a interrup��o!!! Importante
 *				para garantir que n�o ocorrer� uma chamada indesejada ao sair
 *				do tratamento da interrup��o.
 *
 *				Ao sair dessa fun��o � usado o retorno do tipo "retfie fast",
 *				pois esta fun��o � declarada como ALTA prioridade com a diretiva
 *				#pragma interrupt
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	// Escreva a fun��o de tratamento de interrup��o de alta prioridade aqui


   

}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de BAIXA prioridade
 *				Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *					1- verificar qual foi a causa da interrup��o, comparando
 *				os flags de cada tipo de interrup��o.
 *					2- tratar a interrup��o selecionada.
 *					3- limpar o flag que causou a interrup��o!!! Importante
 *				para garantir que n�o ocorrer� uma chamada indesejada ao sair
 *				do tratamento da interrup��o.
 *
 *				Ao sair dessa fun��o � usado o retorno do tipo "retfie",
 *				pois esta fun��o � declarada como BAIXA prioridade com a diretiva
 *				#pragma interruptlow
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
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x808 da mem�ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de BAIXA prioridade
// no endere�o 0x818 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code  	// Diretiva que retorna a aloca��o dos endere�os
				// da mem�ria de programa para seus valores padr�o

/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/