/******************************************************************************
 *
 *            SEMPRATEC - Sistemas Microcontrolados
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.h
 * Dependencias:    	Veja arquivo "my_xlcd.h"
 * Processador:       	PIC18F2550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA - Axoon - UFMG
 *
 *
 *
 *                                  Porta	::      Display LCD
 *
 *								
 *                                  RB3  	::	  D4
 *                                  RB4   	::	  D5
 *                                  RB5  	::	  D6
 *                                  RB6  	::	  D7
 *
 *									
 *                                  RB2  	:: 	  EN
 *                                  GND		::	  R/W
 *                                  RB0 	::	  RS
 *
 *
 *       Conexão do display de LCD 16 Pinos: (na ordem que segue)
 * Pino:        1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 15 
 * Função:      D  D  D  D  N  N  N  N  E  R  R  V  V  V  V  V
 *              7  6  5  4  C  C  C  C	N  W  S  0  D  S  D  S
 *             |----------| |--------| |-------| |-------------|
 *               Dados      Não Usados Comandos  Contraste e alimentação
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
#define D4       LATBbits.LATB3
#define D5       LATBbits.LATB4
#define D6	 LATBbits.LATB5
#define D7       LATBbits.LATB6

// Define do TRIS dos pinos de DADOS do LCD para o KIT PICMINAS v3.0
#define TRIS_D4  TRISBbits.TRISB3
#define TRIS_D5  TRISBbits.TRISB4
#define TRIS_D6  TRISBbits.TRISB5
#define TRIS_D7  TRISBbits.TRISB6

// Define dos pinos de CONTROLE do LCD para o KIT PICMINAS v3.0
#define RS_PIN   PORTBbits.RB0
#define E_PIN    PORTBbits.RB2
#define RW_PIN   PORTBbits.RB1

// Define os TRIS dos pinos de CONTROLE do LCD para o KIT PICMINAS v3.0
#define TRIS_RS  TRISBbits.TRISB0
#define TRIS_E   TRISBbits.TRISB2
#define TRIS_RW  TRISBbits.TRISB1

// Define o valor dos delays baseado no clock da CPU de 48 MHz
#define DELAY_SINC()	Delay1KTCYx(12)		// Delay de 1ms para Fosc=48MHz
						// Geralmente 1ms é suficiente, mas
						// depende do controlador do display
						// Aumente conforme a necessidade!
											
#define DELAY_5ms()	Delay10KTCYx(6)		// Delay de 5ms para Fosc=48MHz




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
 *		display LCD como saida. Essa rotina é baseada no controlador 
 *		de LCD Hitachi HD44780. Configura os parametros de comunicação
 *		com o display, tais como:
 *			- modo de operação (4 ou 8 data bits)
 *			- tipo de cursor
 *			- tamanho da fonte
 *		Ao final da configuração limpa o display.
 *****************************************************************************/
 extern void ConfiguraLCD(void);

/******************************************************************************
 * Funcao:	void EscreveComandoLCD(unsigned char cmd)
 * Entrada:	cmd: comando que será enviado para o LCD
 * Saída:	Nenhuma (void)
 * Descrição: 	(Write a command to the LCD)
 *				Escreve um comando para o display de LCD.
 *****************************************************************************/
 extern void EscreveComandoLCD(unsigned char cmd);
 
/******************************************************************************
 * Funcao:	void EnderecoCursor(unsigned char endereco)
 * Entrada:	endereco: endereço da memoria de dados do display que se deseja apontar
 * Saída:	Nenhuma (void)
 * Descrição: 	(Set the Display Data RAM Address)
 *		Essa rotina seta o endereço da memoria RAM de dados do 
 *		display LCD para o endereço	que se deseja escrever um caracter
 *		usando as funções EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
 extern void EnderecoCursor(unsigned char endereco);
 
/******************************************************************************
 * Funcao:	void PosicaoCursorLCD(unsigned char endereco)
 * Entrada:	Número da linha e da coluna em que se desja escrever o caracter 
 * Saída:	Nenhuma (void)
 * Descrição: 	(Set the Display Data RAM Address)
 *		Essa rotina posiciona o cursor do display de LCD para a linha
 *		e coluna em que se deseja escrever um caracter usando as funções
 *		EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
extern void PosicaoCursorLCD(unsigned char linha, unsigned char coluna);

/******************************************************************************
 * Funcao:	void EscreveCaractereLCD(unsigned char data)
 * Entrada:	data: Byte de dados para ser escrito na memoria RAM do LCD
 * Saída:	Nenhuma (void)
 * Descrição: 	(Write a Data byte to the LCD)
 *		Essa rotina escreve o byte de caracteres no display a partir da
 *		posição de memoria atual do cursor ou da posição de memória
 *		escolhida com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveCaractereLCD(char data);
 
/******************************************************************************
 * Funcao:		void EscreveInteiroLCD(int valor)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) a ser escrito no
 *			display.
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina escreve o numero inteiro no display a partir da posição
 *		de memoria atual do cursor ou da posição de memória escolhida com as
 *		funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
extern void EscreveInteiroLCD(int valor);
 
/******************************************************************************
 * Funcao:		void EscreveFraseRamLCD(char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de dados(RAM)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina copia uma string terminada com caracter nulo
 *		da memoria de dados do microcontrolador para o display de LCD.
 *		A string apontada por *buffer é copiada no display a partir da
 *		posição de memoria atual do cursor ou da posição de memória
 *		escolhida com as funções PosicaoCursorLCD() ou EnderecoCursor().
 ****************************************************************************/
 extern void EscreveFraseRamLCD(char *buffer);

/******************************************************************************
 * Funcao:		void EscreveFraseRomLCD(const rom char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de programa(ROM)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina copia uma string terminada com caracter nulo
 *		da memoria de programa do microcontrolador para o display de LCD.
 *		A string apontada por *buffer é copiada no display a partir da
 *		posição de memoria atual do cursor ou da posição de memória escolhida
 *		com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseRomLCD(const rom char *buffer);

#endif
