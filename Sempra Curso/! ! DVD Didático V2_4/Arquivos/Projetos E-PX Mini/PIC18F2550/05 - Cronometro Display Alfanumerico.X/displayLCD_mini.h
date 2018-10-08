/******************************************************************************
 *
 *            SEMPRATEC - Sistemas Microcontrolados
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.c
 * Dependencias:    	Veja arquivo "my_xlcd.h"
 * Processador:       	PIC18F4550 ou PIC18F2550
 * Op��o de Clock:	HS 20MHz (externo) - CPU: 48MHz	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA - Axoon - UFMG
 *
 * 
 *
 *			Porta	 ::  Display LCD
 *
 * 			RB0 	::	  D0
 *			RB1   	::	  D1
 *			RB2   	::	  D2
 *			RB3  	::	  D3
 *      		RB4  	::	  D4
 *			RB5   	::	  D5
 *			RB6  	::	  D6
 *			RB7   	::	  D7
 *
 *									
 *			RD7     :: 	  EN
 *			RD6	::	  R/W
 *			RD5    	::	  RS
 *
 *									
 *****************************************************************************/
#ifndef __DISPLAY_LCD_H
#define __DISPLAY_LCD_H

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Biblioteca com as defini��es do PIC selecionado 
						//no projeto, neste caso, o modelo 18F4550.

#include <delays.h>		// Biblioteca padr�o C18 Microchip para uso de rotinas de atraso (delay)
						// mais informa��es nos arquivos de ajuda da biblioteca C18
						// presentes na propria pasta de instala��o, por exemplo,
						// C:\MCC18\doc\hlpC18Lib.chm
						// Procure pelo item: "Delay Functions"

#include <stdlib.h>		// Biblioteca padr�o C18 Microchip para uso de rotinas de convers�o
						// de tipos como itoa(). Mais informa��es nos arquivos de ajuda da
						// biblioteca C18 presentes na propria pasta de instala��o, por exemplo,
						// C:\MCC18\doc\hlpC18Lib.chm
						// Procure pelo item: "Data Conversion Functions"

/** D E F I N E S ************************************************************/
// Define dos pinos de DADOS do LCD para o KIT PICMINAS v3.0
#define D4       PORTBbits.RB4
#define D5       PORTBbits.RB5
#define D6		 PORTBbits.RB6
#define D7       PORTBbits.RB7

// Define do TRIS dos pinos de DADOS do LCD para o KIT PICMINAS v3.0
#define TRIS_D4  TRISBbits.TRISB4
#define TRIS_D5  TRISBbits.TRISB5
#define TRIS_D6  TRISBbits.TRISB6
#define TRIS_D7  TRISBbits.TRISB7

// Define dos pinos de CONTROLE do LCD para o KIT PICMINAS v3.0
#define RS_PIN   PORTCbits.RC6
#define E_PIN    PORTCbits.RC7
//n�o usado // #define RW_PIN   PORTBbits.RB2

// Define os TRIS dos pinos de CONTROLE do LCD para o KIT PICMINAS v3.0
#define TRIS_RS  TRISCbits.TRISC6
#define TRIS_E   TRISCbits.TRISC7
//n�o usado // #define TRIS_RW  TRISBbits.TRISB2

// Define o valor dos delays baseado no clock da CPU de 48 MHz
#define DELAY_SINC()	Delay1KTCYx(12)		// Delay de 1ms para Fosc=48MHz
											// Geralmente 1ms � suficiente, mas
											// depende do controlador do display
											// Aumente conforme a necessidade!
											
#define DELAY_5ms()		Delay10KTCYx(6)		// Delay de 5ms para Fosc=48MHz




/*** D E F I N E S D E C O N F I G U R A C A O *******************************/
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Remove todos os caracteres do display e retorna a posi��o do
 *				cursor para a linha 1 e coluna 1
 *****************************************************************************/
#define LimpaDisplay()  	EscreveComandoLCD(0b0000000001)
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Liga o display de LCD e retira o cursor do visor.
 *****************************************************************************/
#define LigaDisplay()  		EscreveComandoLCD(0b0000001000)
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Desliga o display. (N�o apaga o backlight)
 *****************************************************************************/
#define DesligaDisplay()  	EscreveComandoLCD(0b0000001100)
/******************************************************************************
 * Define:		LigaCursor()
 * Descri��o: 	Faz com que o cursor apare�a no LCD caso este esteja ligado
 *				e liga a tela com o cursor caso este esteja desligado.
 *****************************************************************************/
#define LigaCursor()		EscreveComandoLCD(0b0000001110)
/******************************************************************************
 * Define:		DesligaCursor()
 * Descri��o: 	Faz com o cursor suma do LCD caso este esteja ligada e com que
 *				ligue o LCD sem o cursor caso este esteja desligado
 *****************************************************************************/
#define DesligaCursor()		EscreveComandoLCD(0b0000001100)
/******************************************************************************
 * Define:		PiscaCursor()
 * Descri��o: 	Faz com que o cursor apare�a no LCD e fique piscando caso este 
 *              esteja ligado e liga a tela com o cursor piscando caso este 
 *              esteja desligado.
 *****************************************************************************/
#define PiscaCursor()		EscreveComandoLCD(0b0000001111)


/**  P R O T O T I P O  D E  F U N C O E S  **********************************/
/******************************************************************************
 * Funcao:		void ConfiguraLCD(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	Configura portas do PIC 18F4550 que est�o conectadas ao 
 *				display LCD como saida. Essa rotina � baseada no controlador 
 *				de LCD Hitachi HD44780. Configura os parametros de comunica��o
 *				com o display, tais como:
 *					- modo de opera��o (4 ou 8 data bits)
 *					- tipo de cursor
 *					- tamanho da fonte
 *				Ao final da configura��o limpa o display.
 *****************************************************************************/
 extern void ConfiguraLCD(void);

/******************************************************************************
 * Funcao:		void EscreveComandoLCD(unsigned char cmd)
 * Entrada:		cmd: comando que ser� enviado para o LCD
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	(Write a command to the LCD)
 *				Escreve um comando para o display de LCD.
 *****************************************************************************/
 extern void EscreveComandoLCD(unsigned char cmd);
 
/******************************************************************************
 * Funcao:		void EnderecoCursor(unsigned char endereco)
 * Entrada:		endereco: endere�o da memoria de dados do display que se deseja apontar
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	(Set the Display Data RAM Address)
 *				Essa rotina seta o endere�o da memoria RAM de dados do 
 *				display LCD para o endere�o	que se deseja escrever um caracter
 *				usando as fun��es EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
 extern void EnderecoCursor(unsigned char endereco);
 
/******************************************************************************
 * Funcao:		void PosicaoCursorLCD(unsigned char endereco)
 * Entrada:		N�mero da linha e da coluna em que se desja escrever o caracter 
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	(Set the Display Data RAM Address)
 *				Essa rotina posiciona o cursor do display de LCD para a linha
 *				e coluna em que se deseja escrever um caracter usando as fun��es
 *				EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
extern void PosicaoCursorLCD(unsigned char linha, unsigned char coluna);

/******************************************************************************
 * Funcao:		void EscreveCaractereLCD(unsigned char data)
 * Entrada:		data: Byte de dados para ser escrito na memoria RAM do LCD
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	(Write a Data byte to the LCD)
 *				Essa rotina escreve o byte de caracteres no display a partir da
 *				posi��o de memoria atual do cursor ou da posi��o de mem�ria
 *				escolhida com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveCaractereLCD(char data);
 
/******************************************************************************
 * Funcao:		void EscreveInteiroLCD(int valor)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) a ser escrito no
 *				display.
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	Essa rotina escreve o numero inteiro no display a partir da posi��o
 *				de memoria atual do cursor ou da posi��o de mem�ria escolhida com as
 *				fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
extern void EscreveInteiroLCD(int valor);
 
/******************************************************************************
 * Funcao:		void EscreveFraseRamLCD(char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de dados(RAM)
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	Essa rotina copia uma string terminada com caracter nulo
 *				da memoria de dados do microcontrolador para o display de LCD.
 *				A string apontada por *buffer � copiada no display a partir da
 *				posi��o de memoria atual do cursor ou da posi��o de mem�ria
 *				escolhida com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseRamLCD(char *buffer);

/******************************************************************************
 * Funcao:		void EscreveFraseRomLCD(const rom char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de programa(ROM)
 * Sa�da:		Nenhuma (void)
 * Descri��o: 	Essa rotina copia uma string terminada com caracter nulo
 *				da memoria de programa do microcontrolador para o display de LCD.
 *				A string apontada por *buffer � copiada no display a partir da
 *				posi��o de memoria atual do cursor ou da posi��o de mem�ria escolhida
 *				com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseRomLCD(const rom char *buffer);

#endif
