/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:        	C18 v3.37 ou superior
 * Empresa:         	SEMPRA
 * Plataforma:			Placa E-P18 v3.6
 * Autor:				SEMPRA
 * Vers�o:				v1.0
 * Pr�tica: 			
 * Descri��o:   	
 *
 *
 *
 *
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
						// com as defini��es do PIC selecionado no projeto, neste
						// caso, o modelo 18F4550.

#include <delays.h>		// Bilioteca com fun��es de atraso (delay)


/** B I T S   D E   C O N F I G U R A � � O   D O   P I C 1 8 F 4 5 5 0 ******/

// As seguintes configura�oes do PIC18F4550 s� devem ser utilizadas se o
// for feita a grava��o SEM BOOTLOADER, ou seja, atrav�s de um Programador
// Compativel com a fam�lia PIC18 Microchip.

	#pragma config FOSC     = HSPLL_HS	// Habilita PLL, CPU e USB com cristal de alta velocidade (High Speed)
	#pragma config PLLDIV   = 5         // Oscilador de entrada de 20 MHz
	#pragma config CPUDIV   = OSC1_PLL2	// Clock CPU = 96MHz PLL/2
	#pragma config USBDIV   = 2         // Clock da USB = 96MHz PLL/2
	#pragma config FCMEN    = OFF		// Fail Safe Clock Monitor
	#pragma config IESO     = OFF		// Mudan�a do Oscilador int/ext 
	#pragma config PWRT     = OFF		// Power up Timer
	#pragma config BOR      = OFF		// Brown-out Reset
	#pragma config BORV     = 3			// Tens�o de Brown-out Reset = 2.05V
	#pragma config VREGEN   = ON      	// Regulator Interno da USB de 3,3V
	#pragma config WDT      = OFF		// Watch Dog Timer
	#pragma config WDTPS    = 32768		// Postcaler do Watch Dog Timer
	#pragma config MCLRE    = ON		// Master Clear Reset pino RE3
	#pragma config LPT1OSC  = OFF		// Timer1 em Low-Power Oscilator
	#pragma config PBADEN   = OFF		// PORTB<4:0> Analogicas no Reset
	#pragma config CCP2MX   = ON		// CCP2 Mux ligado a RC1(ON) ou RB3(OFF)
	#pragma config STVREN   = ON		// Stack Full / Overflow Reset
	#pragma config LVP      = OFF		// Single Supply ICSP, Low-Voltage ICSP
	#pragma config DEBUG    = OFF       // Pinos RB6 e RB7 dedicados para In Circuit Debug
	#pragma config ICPRT    = OFF       // Pinos RB6 e RB7 dedicados para grava��o ICSP
	#pragma config XINST    = OFF       // Instru��es Extendidas
	// Prote��o contra Leitura Externa dos Blocos da Flash
	#pragma config CP0      = OFF	// Bloco0		 
	#pragma config CP1      = OFF	// Bloco1
	#pragma config CP2      = OFF	// Bloco2
	#pragma config CP3      = OFF	// Bloco3
	#pragma config CPB      = OFF	// Bloco Boot
	#pragma config CPD      = OFF	// EEPROM
	// Prote��o contra Escrita nos Blocos da Flash
	#pragma config WRT0     = OFF	// Bloco0
	#pragma config WRT1     = OFF	// Bloco1
	#pragma config WRT2     = OFF	// Bloco2
	#pragma config WRT3     = OFF	// Bloco3
	#pragma config WRTB     = OFF	// Bloco Boot
	#pragma config WRTC     = OFF	// Bits de Configura��o
	#pragma config WRTD     = OFF	// EEPROM
	// Prote��o contra Leitura do Bloco via TBLRD localizadas em outros blocos
	#pragma config EBTR0    = OFF	// Bloco0	
	#pragma config EBTR1    = OFF	// Bloco1
	#pragma config EBTR2    = OFF	// Bloco2
	#pragma config EBTR3    = OFF	// Bloco3
	#pragma config EBTRB    = OFF	// Bloco Boot

/** D E F I N E S ************************************************************/




/** V A R I A V E I S   G L O B A I S ****************************************/

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);

/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:        	void main(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Fun��o principal do programa. 
 *****************************************************************************/
void main(void)
{

	// Configura as portas e perif�ricos do PIC.
	ConfiguraSistema();
	

	
    while(1)	// La�o infinito que executa o funcionamento principal do projeto.    	
	{
		

	}//end while(1)
	
}//end main

/******************************************************************************
 * Funcao:        	void ConfiguraSistema(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       ConfiguraSistema � a rotina de configura��o principal do PIC.
 *					Seu objetivo � configurar as portas de I/O e os perif�ricos
 *					do microcontrolador para que os mesmos trabalhem da maneira
 *					desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema(void)
{
	// Desabilita todas as anal�gicas
	ADCON1 = ADCON1 | 0x0F;


	
}//end ConfiguraSistema


/** FIM DO ARQUIVO main.c ***************************************************************/
