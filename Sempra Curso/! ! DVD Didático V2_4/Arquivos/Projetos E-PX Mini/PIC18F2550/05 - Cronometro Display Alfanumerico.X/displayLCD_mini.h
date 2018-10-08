/******************************************************************************
 *
 *            SEMPRATEC - Sistemas Microcontrolados
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.c
 * Dependencias:    	Veja arquivo "my_xlcd.h"
 * Processador:       	PIC18F4550 ou PIC18F2550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz	
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
#include <p18cxxx.h>	// Biblioteca com as definições do PIC selecionado 
						//no projeto, neste caso, o modelo 18F4550.

#include <delays.h>		// Biblioteca padrão C18 Microchip para uso de rotinas de atraso (delay)
						// mais informações nos arquivos de ajuda da biblioteca C18
						// presentes na propria pasta de instalação, por exemplo,
						// C:\MCC18\doc\hlpC18Lib.chm
						// Procure pelo item: "Delay Functions"

#include <stdlib.h>		// Biblioteca padrão C18 Microchip para uso de rotinas de conversão
						// de tipos como itoa(). Mais informações nos arquivos de ajuda da
						// biblioteca C18 presentes na propria pasta de instalação, por exemplo,
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
//não usado // #define RW_PIN   PORTBbits.RB2

// Define os TRIS dos pinos de CONTROLE do LCD para o KIT PICMINAS v3.0
#define TRIS_RS  TRISCbits.TRISC6
#define TRIS_E   TRISCbits.TRISC7
//não usado // #define TRIS_RW  TRISBbits.TRISB2

// Define o valor dos delays baseado no clock da CPU de 48 MHz
#define DELAY_SINC()	Delay1KTCYx(12)		// Delay de 1ms para Fosc=48MHz
											// Geralmente 1ms é suficiente, mas
											// depende do controlador do display
											// Aumente conforme a necessidade!
											
#define DELAY_5ms()		Delay10KTCYx(6)		// Delay de 5ms para Fosc=48MHz




/*** D E F I N E S D E C O N F I G U R A C A O *******************************/
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descrição: 	Remove todos os caracteres do display e retorna a posição do
 *				cursor para a linha 1 e coluna 1
 *****************************************************************************/
#define LimpaDisplay()  	EscreveComandoLCD(0b0000000001)
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descrição: 	Liga o display de LCD e retira o cursor do visor.
 *****************************************************************************/
#define LigaDisplay()  		EscreveComandoLCD(0b0000001000)
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descrição: 	Desliga o display. (Não apaga o backlight)
 *****************************************************************************/
#define DesligaDisplay()  	EscreveComandoLCD(0b0000001100)
/******************************************************************************
 * Define:		LigaCursor()
 * Descrição: 	Faz com que o cursor apareça no LCD caso este esteja ligado
 *				e liga a tela com o cursor caso este esteja desligado.
 *****************************************************************************/
#define LigaCursor()		EscreveComandoLCD(0b0000001110)
/******************************************************************************
 * Define:		DesligaCursor()
 * Descrição: 	Faz com o cursor suma do LCD caso este esteja ligada e com que
 *				ligue o LCD sem o cursor caso este esteja desligado
 *****************************************************************************/
#define DesligaCursor()		EscreveComandoLCD(0b0000001100)
/******************************************************************************
 * Define:		PiscaCursor()
 * Descrição: 	Faz com que o cursor apareça no LCD e fique piscando caso este 
 *              esteja ligado e liga a tela com o cursor piscando caso este 
 *              esteja desligado.
 *****************************************************************************/
#define PiscaCursor()		EscreveComandoLCD(0b0000001111)


/**  P R O T O T I P O  D E  F U N C O E S  **********************************/
/******************************************************************************
 * Funcao:		void ConfiguraLCD(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição: 	Configura portas do PIC 18F4550 que estão conectadas ao 
 *				display LCD como saida. Essa rotina é baseada no controlador 
 *				de LCD Hitachi HD44780. Configura os parametros de comunicação
 *				com o display, tais como:
 *					- modo de operação (4 ou 8 data bits)
 *					- tipo de cursor
 *					- tamanho da fonte
 *				Ao final da configuração limpa o display.
 *****************************************************************************/
 extern void ConfiguraLCD(void);

/******************************************************************************
 * Funcao:		void EscreveComandoLCD(unsigned char cmd)
 * Entrada:		cmd: comando que será enviado para o LCD
 * Saída:		Nenhuma (void)
 * Descrição: 	(Write a command to the LCD)
 *				Escreve um comando para o display de LCD.
 *****************************************************************************/
 extern void EscreveComandoLCD(unsigned char cmd);
 
/******************************************************************************
 * Funcao:		void EnderecoCursor(unsigned char endereco)
 * Entrada:		endereco: endereço da memoria de dados do display que se deseja apontar
 * Saída:		Nenhuma (void)
 * Descrição: 	(Set the Display Data RAM Address)
 *				Essa rotina seta o endereço da memoria RAM de dados do 
 *				display LCD para o endereço	que se deseja escrever um caracter
 *				usando as funções EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
 extern void EnderecoCursor(unsigned char endereco);
 
/******************************************************************************
 * Funcao:		void PosicaoCursorLCD(unsigned char endereco)
 * Entrada:		Número da linha e da coluna em que se desja escrever o caracter 
 * Saída:		Nenhuma (void)
 * Descrição: 	(Set the Display Data RAM Address)
 *				Essa rotina posiciona o cursor do display de LCD para a linha
 *				e coluna em que se deseja escrever um caracter usando as funções
 *				EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
extern void PosicaoCursorLCD(unsigned char linha, unsigned char coluna);

/******************************************************************************
 * Funcao:		void EscreveCaractereLCD(unsigned char data)
 * Entrada:		data: Byte de dados para ser escrito na memoria RAM do LCD
 * Saída:		Nenhuma (void)
 * Descrição: 	(Write a Data byte to the LCD)
 *				Essa rotina escreve o byte de caracteres no display a partir da
 *				posição de memoria atual do cursor ou da posição de memória
 *				escolhida com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveCaractereLCD(char data);
 
/******************************************************************************
 * Funcao:		void EscreveInteiroLCD(int valor)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) a ser escrito no
 *				display.
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina escreve o numero inteiro no display a partir da posição
 *				de memoria atual do cursor ou da posição de memória escolhida com as
 *				funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
extern void EscreveInteiroLCD(int valor);
 
/******************************************************************************
 * Funcao:		void EscreveFraseRamLCD(char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de dados(RAM)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina copia uma string terminada com caracter nulo
 *				da memoria de dados do microcontrolador para o display de LCD.
 *				A string apontada por *buffer é copiada no display a partir da
 *				posição de memoria atual do cursor ou da posição de memória
 *				escolhida com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseRamLCD(char *buffer);

/******************************************************************************
 * Funcao:		void EscreveFraseRomLCD(const rom char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de programa(ROM)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina copia uma string terminada com caracter nulo
 *				da memoria de programa do microcontrolador para o display de LCD.
 *				A string apontada por *buffer é copiada no display a partir da
 *				posição de memoria atual do cursor ou da posição de memória escolhida
 *				com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseRomLCD(const rom char *buffer);

#endif
