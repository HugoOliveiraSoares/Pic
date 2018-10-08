/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:		modelo_main_define_interrup.c
 * Dependencias:		Veja a se��o INCLUDES abaixo
 * Microcontrolador:	PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:			C18 v3.37 ou superior
 * Empresa:				SEMPRA
 * Plataforma:			Placa E-P18 v3.6
 * Autor:				SEMPRA
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

#include <timers.h> // Necess�rio para utilizar as fun��es do timer

#include <pwm.h> // Necess�rio para utilizar as fun��es do PWM

#include "TimeDelay.h"


/** D E F I N E S ************************************************************/



/** V A R I A V E I S   G L O B A I S ****************************************/

int DC = 0 ; // variavel que recebe o valor do duty cycle

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void) ;


/**  P R O T O T I P O S   D A S   F U N � � E S   D E   I N T E R R U P � � O*/
void ConfiguraInterrupcao(void) ;
void Tratamento_High_Interrupt(void) ;
void Tratamento_Low_Interrupt(void) ;

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:		void main(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	Fun��o principal do programa.
 *****************************************************************************/
void main(void)
{

	//Fun��o que faz configura��es do firmware
	ConfiguraSistema();

	// La�o de repeti��o infinito que executa aplica��o do firmware
	while(1)
	{
            // verifica se o bot�o 1 est� precionado e bot�o 2 solto
            if(PORTAbits.RA3 == 1 && PORTEbits.RE2 == 0)
            {
                // soma um na variavel DC
                DC = DC + 1 ;
                // verifica se DC � maior ou igual a 1023
                if(DC >= 1023)
                {
                    DC = 1023 ;
                }
                // usa a varial DC para determinar o duty cycle
                SetDCPWM1(DC);
                // tempo dado para que a varia��o do brilho do led n�o seja muito
                // rapida
                DelayMs(100);

            }
            // verifica se o bot�o 2 est� precionado e bot�o 1 solto
            if(PORTEbits.RE2 == 1 && PORTAbits.RA3 == 0)
            {
                // soma um na variavel DC
                DC = DC - 1 ;
                // verifica se DC � menor ou igual a 0
                if(DC <= 0)
                {
                    DC = 0 ;
                }
                // usa a varial DC para determinar o duty cycle
                SetDCPWM1(DC);
                // tempo dado para que a varia��o do brilho do led n�o seja mto
                // rapida
                DelayMs(100);

            }


	
	}//end while(1)
	
}//end main

/******************************************************************************
 * Funcao:		void ConfiguraSistema(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	ConfiguraSistema � a rotina de configura��o principal do PIC.
 *		Seu objetivo � configurar as portas de I/O e os perif�ricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
	// Desabilita pinos anal�gicos
	ADCON1 = ADCON1 | 0x0f;

        // configura o pino RC2 como saida digital
        TRISCbits.TRISC2 = 0 ;
        LATCbits.LATC2 = 0 ;// garante estado inicial desligado do led
        // configura os bot�es 1 e 2 como entrada digital
        TRISAbits.TRISA3 = 1 ;
        TRISEbits.TRISE2 = 1 ;
        // abre o timer2
        OpenTimer2(TIMER_INT_OFF & T0_PS_1_16) ;
        // inicia o pwm com frequencia de 2,44 KHz
        OpenPWM1(255) ;
        // seta o valor inicial do duty cycle
        SetDCPWM1(0) ;

	// Fun��o que configura as interrup��es do firmware
	ConfiguraInterrupcao();
		
}//end ConfiguraSistema


/******************************************************************************
 * Funcao:		void ConfiguraInterrupcao(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	Fun��o que configura as interrup��es utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	//Configura��o Global das Interrup��es
        INTCONbits.GIE = 0 ;    // Desabilita todos as interrupcoes
	RCONbits.IPEN = 1 ;	// Habilita prioridades de interrupcao
	INTCONbits.GIEH = 0 ;	// Desabilita vetor de alta prioridade
	INTCONbits.GIEL = 0 ;	// Desabilita vetor de baixa prioridade


}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	Fun��o de tratamento das interrup��es de ALTA prioridade
 *		Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup��o, comparando 
 *		os flags de cada tipo de interrup��o.
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
	// Escreva a fun��o de tratamento de interrup��o de Alta prioridade aqui
	
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	Fun��o de tratamento das interrup��es de BAIXA prioridade
 *		Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup��o, comparando 
 *		os flags de cada tipo de interrup��o.
 *			2- tratar a interrup��o selecionada.
 *			3- limpar o flag que causou a interrup��o!!! Importante 
 *		para garantir que n�o ocorrer� uma chamada indesejada ao sair 
 *		do tratamento da interrup��o.
 *
 *		Ao sair dessa fun��o � usado o retorno do tipo "retfie",
 *		pois esta fun��o � declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrup��o de Baixa prioridade aqui

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Se��o necess�ria para informar ao compilador C18 onde s�o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup��o.

//
// ATEN��O: Copiar esta parte do c�digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para grava��o in-circuit.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x1000 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x1008 da mem�ria de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de BAIXA prioridade 
// no endere�o 0x1018 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o

/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/