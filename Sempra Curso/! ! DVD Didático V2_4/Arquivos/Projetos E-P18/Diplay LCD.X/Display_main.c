/******************************************************************************
 *
 *            		 PICMINAS PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P18
 * Pr�tica:	 	Uso do display de LCD Alfanum�rico 16x2
 *						
 * Descri��o:	Usar a biblioteca de usuario displayLCD.h para escrever no display
 *		alfanumerico 16x2. Escrever no display na primeira linha 
 *		a frase "OLA MUNDO" e na segunda "SEMPRA".
 * 
 *****************************************************************************/


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.
						
#include "displayLCD.h"	// Biblioteca com de rotinas para usar o display LCD no
			// KIT E-P18 V3.6



/** V A R I A V E I S   G L O B A I S ****************************************/

// armazena variavel na mem�ria de dados (SDRAM)
// outro tipo sintaxe C para inicializar a vari�vel na DECLARA��O
rom unsigned char linha2[20]="Curso SEMPRA";

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *				pois esta � a primeira a ser chamada ap�s o	reset do 
 *				microcontrolador.
 *				Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{
	// Configura as portas e perif�ricos usados no projeto
	ConfiguraSistema();
	
	
	// Seleciona o endere�o inicial da linha 1 (0x00) do display 
	EnderecoCursor(0x00);
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD("OLA MUNDO");

	// Seleciona o endere�o inicial da linha 2 (0x40) do display 
	EnderecoCursor(0x40);
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRamLCD(linha2);

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
 *				Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *				do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	// Desabilita todas as 13 portas anal�gicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	//Configura os pinos que s�o usados pelo LCD 16x2 alfa-numerico
	ConfiguraLCD();
	
}//end ConfiguraSistema

/** V E C T O R   R E M A P P I N G ******************************************/

// ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x1000 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
