/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:		modelo_main_define_interrup.c
 * Dependencias:		Veja a seção INCLUDES abaixo
 * Microcontrolador:	PIC18F4550
 * Opção de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:			C18 v3.37 ou superior
 * Empresa:				SEMPRA
 * Plataforma:			Placa E-P18 v3.6
 * Autor:				SEMPRA
 * Versão:				v1.0
 * Descrição:	
 *	
 *	
 *	
 *	
 *	
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>// Necessário para que o compilador adicione a biblioteca
                   // com as definições do PIC selecionado no projeto, neste
		  // caso, o modelo 18F4550.

#include <timers.h> // Necessário para utilizar as funções do timer

#include <pwm.h> // Necessário para utilizar as funções do PWM

#include "TimeDelay.h"


/** D E F I N E S ************************************************************/



/** V A R I A V E I S   G L O B A I S ****************************************/

int DC = 0 ; // variavel que recebe o valor do duty cycle

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void) ;


/**  P R O T O T I P O S   D A S   F U N Ç Õ E S   D E   I N T E R R U P Ç Ã O*/
void ConfiguraInterrupcao(void) ;
void Tratamento_High_Interrupt(void) ;
void Tratamento_Low_Interrupt(void) ;

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:		void main(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição:	Função principal do programa.
 *****************************************************************************/
void main(void)
{

	//Função que faz configurações do firmware
	ConfiguraSistema();

	// Laço de repetição infinito que executa aplicação do firmware
	while(1)
	{
            // verifica se o botão 1 está precionado e botão 2 solto
            if(PORTAbits.RA3 == 1 && PORTEbits.RE2 == 0)
            {
                // soma um na variavel DC
                DC = DC + 1 ;
                // verifica se DC é maior ou igual a 1023
                if(DC >= 1023)
                {
                    DC = 1023 ;
                }
                // usa a varial DC para determinar o duty cycle
                SetDCPWM1(DC);
                // tempo dado para que a variação do brilho do led não seja muito
                // rapida
                DelayMs(100);

            }
            // verifica se o botão 2 está precionado e botão 1 solto
            if(PORTEbits.RE2 == 1 && PORTAbits.RA3 == 0)
            {
                // soma um na variavel DC
                DC = DC - 1 ;
                // verifica se DC é menor ou igual a 0
                if(DC <= 0)
                {
                    DC = 0 ;
                }
                // usa a varial DC para determinar o duty cycle
                SetDCPWM1(DC);
                // tempo dado para que a variação do brilho do led não seja mto
                // rapida
                DelayMs(100);

            }


	
	}//end while(1)
	
}//end main

/******************************************************************************
 * Funcao:		void ConfiguraSistema(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição:	ConfiguraSistema é a rotina de configuração principal do PIC.
 *		Seu objetivo é configurar as portas de I/O e os periféricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
	// Desabilita pinos analógicos
	ADCON1 = ADCON1 | 0x0f;

        // configura o pino RC2 como saida digital
        TRISCbits.TRISC2 = 0 ;
        LATCbits.LATC2 = 0 ;// garante estado inicial desligado do led
        // configura os botões 1 e 2 como entrada digital
        TRISAbits.TRISA3 = 1 ;
        TRISEbits.TRISE2 = 1 ;
        // abre o timer2
        OpenTimer2(TIMER_INT_OFF & T0_PS_1_16) ;
        // inicia o pwm com frequencia de 2,44 KHz
        OpenPWM1(255) ;
        // seta o valor inicial do duty cycle
        SetDCPWM1(0) ;

	// Função que configura as interrupções do firmware
	ConfiguraInterrupcao();
		
}//end ConfiguraSistema


/******************************************************************************
 * Funcao:		void ConfiguraInterrupcao(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição:	Função que configura as interrupções utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	//Configuração Global das Interrupções
        INTCONbits.GIE = 0 ;    // Desabilita todos as interrupcoes
	RCONbits.IPEN = 1 ;	// Habilita prioridades de interrupcao
	INTCONbits.GIEH = 0 ;	// Desabilita vetor de alta prioridade
	INTCONbits.GIEL = 0 ;	// Desabilita vetor de baixa prioridade


}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição:	Função de tratamento das interrupções de ALTA prioridade
 *		Nessa função deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupção, comparando 
 *		os flags de cada tipo de interrupção.
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
	// Escreva a função de tratamento de interrupção de Alta prioridade aqui
	
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição:	Função de tratamento das interrupções de BAIXA prioridade
 *		Nessa função deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupção, comparando 
 *		os flags de cada tipo de interrupção.
 *			2- tratar a interrupção selecionada.
 *			3- limpar o flag que causou a interrupção!!! Importante 
 *		para garantir que não ocorrerá uma chamada indesejada ao sair 
 *		do tratamento da interrupção.
 *
 *		Ao sair dessa função é usado o retorno do tipo "retfie",
 *		pois esta função é declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrupção de Baixa prioridade aqui

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Seção necessária para informar ao compilador C18 onde são os novos endereços
//da memória de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupção.

//
// ATENÇÃO: Copiar esta parte do código dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para gravação in-circuit.

// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal 
// no endereço 0x1000 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Alocação da função de tratamento das interrupções de ALTA prioridade
// no endereço 0x1008 da memória de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Alocação da função de tratamento das interrupções de BAIXA prioridade 
// no endereço 0x1018 da memória de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a alocação dos endereços 
				// da memória de programa para seus valores padrão

/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/