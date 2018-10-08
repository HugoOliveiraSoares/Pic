/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess∑rio para que o compilador adicione a biblioteca
			// com as defini¡?es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include "TimeDelay.h"	// Biblioteca para delays

/** D E F I N E S ************************************************************/
// SaÃdas Digitais
#define	LED_AMARELO	LATCbits.LATC2

//Entradas digitais
#define	BOTAO          PORTBbits.RB1

/** V A R I A V E I S   G L O B A I S ****************************************/


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);

/**  P R O T O T I P O S   D A S   F U N ´ ? E S   D E   I N T E R R U P ´ ? O*/
void ConfiguraInterrupcao(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);


void main(void)
{
	//Fun¡?o que faz configura¡?es do firmware
	ConfiguraSistema();

	// La¡o de repeti¡?o infinito que executa aplica¡?o do firmware
	while(1)
	{
        LATDbits.LATD1 = 1;
        DelayMs(1000);
        LATDbits.LATD1 = 0;
        DelayMs(1000);
        
	}//end while(1)

}//end main

/******************************************************************************
 * Funcao:		void ConfiguraSistema(void)
 * Entrada:		Nenhuma (void)
 * SaÃda:		Nenhuma (void)
 * Descri¡?o:	ConfiguraSistema » a rotina de configura¡?o principal do PIC.
 *		Seu objetivo » configurar as portas de I/O e os perif»ricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
	// Desabilita pinos anal€gicos
	ADCON1 = ADCON1 | 0x0f;

	// Configura saidas digitais
	TRISCbits.TRISC2 = 0;	//RC2 (LED_AMARELO)
    TRISDbits.TRISD1 = 0;
    
        LED_AMARELO = 0; // Define o estado inicial do LED

	// Configura entradas digitais
	TRISBbits.TRISB1 = 1;	//RB1 (BOTAO)

	//Configura¡?o Global das Interrup¡?es
	RCONbits.IPEN = 1;	// Habilita prioridades de interrupcao
	INTCONbits.GIEH = 0;	// Desabilita vetor de alta prioridade
	INTCONbits.GIEL = 0;	// Desabilita vetor de baixa prioridade

        INTCON2bits.INTEDG1 = 1;// Configura interrupÁ„o na borda de subida
        
	INTCON2bits.RBPU = 1;	// Desabilita os resistores de pull-up internos
							//do PORTB
        INTCON3bits.INT1IE = 1; // Habilita a interrupÁ„o INT1
        INTCON3bits.INT1IP = 1; // Define a interrupÁ„o como alta prioridade
        INTCON3bits.INT1IF = 0; // Limpa o flag para que n„o haja interrupÁ„o
                                    // por lixo na memÛria


        	// Habilita vetores de Alta Prioridade
	INTCONbits.GIEH = 1;

}//end ConfiguraSistema

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * SaÃda:		Nenhuma (void)
 * Descri¡?o:	Fun¡?o de tratamento das interrup¡?es de ALTA prioridade
 *		Nessa fun¡?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup¡?o, comparando
 *		os flags de cada tipo de interrup¡?o.
 *			2- tratar a interrup¡?o selecionada.
 *			3- limpar o flag que causou a interrup¡?o!!! Importante
 *		para garantir que n?o ocorrer∑ uma chamada indesejada ao sair
 *		do tratamento da interrup¡?o.
 *****************************************************************************/
// ATEN´?O NA SINTAXE de declara¡?o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
    // Verifica se o motivo da chamada da interrup¡?o foi mudan¡a
	//de estado no PORTB
	if(INTCON3bits.INT1IF = 1)
	{
		// Variavel temporaria, usada para corrigir erro na Note1 p101 do Datasheet
		// do PIC18F4550 revE.
		char temp;
        char i = 0;// Variavel usada para piscar o LED 5 no for
		// Leitura do PORTB para corrigir erro de limpeza do flag RBIF
		temp = PORTB;

                // For que pisca o LED 5 vezes 
                for (i = 0; i < 5; i++)
                {
                    // Inverte estado do LED_AMARELO (Toggle)
                    LED_AMARELO = !(LED_AMARELO);
                    DelayMs(250);
                    LED_AMARELO = !(LED_AMARELO);
                    DelayMs(250);
                }//end for

		//Limpa flag da interrup¡?o do PORTB
		INTCON3bits.INT1IF = 0;
	}// end (if) tratamento da interrup¡?o do PORTB (INTCONbits.RBIF)
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * SaÃda:		Nenhuma (void)
 * Descri¡?o:	Fun¡?o de tratamento das interrup¡?es de BAIXA prioridade
 *		Nessa fun¡?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup¡?o, comparando
 *		os flags de cada tipo de interrup¡?o.
 *			2- tratar a interrup¡?o selecionada.
 *			3- limpar o flag que causou a interrup¡?o!!! Importante
 *		para garantir que n?o ocorrer∑ uma chamada indesejada ao sair
 *		do tratamento da interrup¡?o.
 *
 *		Ao sair dessa fun¡?o » usado o retorno do tipo "retfie",
 *		pois esta fun¡?o » declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATEN´?O NA SINTAXE de declara¡?o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Se¡?o necess∑ria para informar ao compilador C18 onde s?o os novos endere¡os
//da mem€ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup¡?o.

//
// ATEN´?O: Copiar esta parte do c€digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para grava¡?o in-circuit.

// prot€tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca¡?o da fun¡?o de tratamento do "reset" da aplica¡?o principal
// no endere¡o 0x1000 da mem€ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca¡?o da fun¡?o de tratamento das interrup¡?es de ALTA prioridade
// no endere¡o 0x1008 da mem€ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca¡?o da fun¡?o de tratamento das interrup¡?es de BAIXA prioridade
// no endere¡o 0x1018 da mem€ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a aloca¡?o dos endere¡os
				// da mem€ria de programa para seus valores padr?o

/** F I M  D A  S E ´ ? O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/