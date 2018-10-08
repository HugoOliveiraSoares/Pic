/******************************************************************************
 *
 *            		SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-P18mini
 * Pr�tica:	 	OLA MUNDO
 *
 * Autor:               Bruno A. Dayrell
 * Vers�o:		v1.0	
 *						
 * Descri��o:       	Inicializa��o do Display alfanum�rico LCD, escrevendo
 *			nele o "OLA MUNDO". Exemplifica��o sobre o uso de 
 *			bibliotecas propriet�rias. Comunica��o com um
 *			dispositivo inteligente externo ao PIC.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.


#include "displayLCD_mini.h"						 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
//atribui��o:	0 = LED desligado
//		1 = LED ligado
#define LED_AMARELO	LATCbits.LATC1
#define LED_VERMELHO    LATCbits.LATC2


/** V A R I A V E I S   G L O B A I S ****************************************/

// armazena variavel na mem�ria de dados (SDRAM)
// outro tipo sintaxe C para inicializar a vari�vel na DECLARA��O
rom unsigned char linha2[20]="Curso SEMPRA";

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *		pois esta � a primeira a ser chamada ap�s o	reset do 
 *		microcontrolador.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/

void main(void)
{
	// Configura as portas e perif�ricos usados no projeto
	ConfiguraSistema();
			
	
	// Configura e inicializa o display LCD
	ConfiguraLCD();
	
	LimpaDisplay();
	
	// Posiciona o cursro na linha 1 e na primeira coluna do display
	PosicaoCursorLCD (1,1);
	
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD ("OLA MUNDO");

	// Posiciona o cursor na linha 2 e primeira coluna do display
	PosicaoCursorLCD(2,1);
	
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD (linha2);

	// La�o infinito
	while(1)
   	{ 
		
	}//end while
	
}//end main

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	ConfiguraSistema � a rotina de configura��o principal do projeto.
 *		Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *		do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	
	// Desabilita todas as 13 portas anal�gicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Configura LED do Kit PICMINAS: saida digital	
	TRISCbits.TRISC1=0;	// RC1: saida digital - LED_AMARELO
	TRISCbits.TRISC2=0; 	// RC2: saida digital - LED_VERDE

	// Configura Bot�o do Kit PICMINAS: entradas digital
	TRISBbits.TRISB4=1;	// RB4: entrada digital - BOTAO BOOT
	
	
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x800 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/