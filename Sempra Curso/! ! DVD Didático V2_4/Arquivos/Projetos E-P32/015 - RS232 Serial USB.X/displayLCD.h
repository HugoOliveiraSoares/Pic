/******************************************************************************
 *
 *            PICMINAS PROJETOS - Bibliotecas (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.h
 * Dependencias:    	<displayLCDconfig> (e suas dependecias: <p18cxxx.h> <delays.h> <stdlib.h> )
 * Processador:       	PIC32MX775F256L
 * Opção de Clock:		HS 20MHz (externo) - CPU: 80MHz	
 * Compilador:        	C32 
 * Empresa:         	SEMPRA
 *
 * Plataforma:			Kit E-P32
 *
 * Autores:				M.Sc. Henrique Resende Martins
 * 						Mauricio Ferrari Santos Corrêa
 *						Bruno Silveira Avelar
 *						James Hamilton Oliveira Junior
 *
 * Data:				v1 - 06/Fev/2011 - Bruno Silveira Avelar
 *
 * Descrição:			Biblioteca para escrita no display de LCD 
 *						alfanumérico. No projeto do Kit E-P32 o display
 *						LCD é ligado à portas digitais diversas do 
 *						PIC 18F4550. O Kit E-P32 V3.X utiliza os 
 *						seguintes pinos para comunicação com o display LCD:
 *
 *								PIC18F4550(pino):: Display LCD
 *									RD4 (27)  	::	  D4
 *									RD5 (28)  	::	  D5
 *									RD6 (29)  	::	  D6
 *									RD7 (30)  	::	  D7
 *									RD2 (21)  	:: 	  RS
 *									RD3 (22)  	::	  E
 *							    	GND			::	  R/W
 *
 *	 OBS: o pino R/W do display é ligado na placa de desenvolvimento
 *	      PICMINAS18 ao GND através de um resistor de pull-down, assim o
 *	   	  LCD opera no modo escrite(Write) o tempo todo. No entanto o 
 *		  código C foi escrito mostrando a imlementação onde um pino do
 *		  PIC é utilizado para a função R/W, assim comentando o inicio das 
 *		  linhas correspondentes com "//não usado //".
 *   Notas:
 *		- Essa bliblioteca de rotinas foi escrita pensando em um LCD
 *        16x2 FDCC1602E implementado com o controlador SPLC780D, mas pode
 * 		  ser utilizado com qualquer LCD 16x2 com controladores equivalentes
 *        como, por exemplo, o controlador Hitachi HD44780 LCD controller.
 *
 *          -- Cursor e/ou Blink:
 *             O usuário poderá definir se quer visualizar cursor, blink 
 *			   ou nenhum dos dois.
 *          
 *			-- O sincronismo da comunicação com o LCD:
 *             As temporizações entre o envio de comandos, não foi utilizado
 *			   o bit de Busy do LCD, mas sim, através de funções de atraso.
 *			   A função utilizada foi a Delay10KTCYx() da bilioteca padrão C18
 *			   delays.h que aparece na seção INCLUDE deste arquivo.
 * 			   Os tempos de delay escolhidos estão colocados nos defines:
 *			   DELAY_SINC e DELAY_INICIO, que foram ecolhidos bem acima do 
 *			   tempo mínimo requerido pelo display de LCD (5ms o de sincronismo e
 *			   15ms o inicial).
 *****************************************************************************/
#ifndef __DISPLAY_LCD_H
#define __DISPLAY_LCD_H

/** I N C L U D E S **********************************************************/

#include "displayLCDconfig.h" // Arquivo contendo as configurações do LCD
							  // definidas pelo usuário

/*** D E F I N E S   D E   U S O *********************************************/
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descrição: 	Remove todos os caracteres do display e retorna a posição do
 *				cursor para a linha 1 e coluna 1
 *****************************************************************************/
#define LimpaDisplay()  	EscreveComandoLCD(LIMPA_DISPLAY)
/******************************************************************************
 * Define:		LigaDisplay()
 * Descrição: 	Liga o display de LCD e retira o cursor do visor.
 *****************************************************************************/
#define LigaDisplay()  		EscreveComandoLCD(LIGA_DISPLAY)
/******************************************************************************
 * Define:		DesligaDisplay()
 * Descrição: 	Desliga o display. (Não apaga o backlight)
 *****************************************************************************/
#define DesligaDisplay()  	EscreveComandoLCD(DESLIGA_DISPLAY)
/******************************************************************************
 * Define:		LigaCursor()
 * Descrição: 	Faz com que o cursor apareça no LCD caso este esteja ligado
 *				e liga a tela com o cursor caso este esteja desligado.
 *****************************************************************************/
#define LigaCursor()		EscreveComandoLCD(LIGA_CURSOR)
/******************************************************************************
 * Define:		DesligaCursor()
 * Descrição: 	Faz com o cursor suma do LCD caso este esteja ligada e com que
 *				ligue o LCD sem o cursor caso este esteja desligado
 *****************************************************************************/
#define DesligaCursor()		EscreveComandoLCD(DESLIGA_CURSOR)
/******************************************************************************
 * Define:		PiscaCursor()
 * Descrição: 	Faz com que o cursor apareça no LCD e fique piscando caso este 
 *              esteja ligado e liga a tela com o cursor piscando caso este 
 *              esteja desligado.
 *****************************************************************************/
#define PiscaCursor()		EscreveComandoLCD(PISCA_CURSOR)


/**  P R O T O T I P O  D E  F U N C O E S  **********************************/
/******************************************************************************
 * Funcao:		void ConfiguraLCD(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição: 	Configura portas do PIC 18F4550 que estão conectadas ao 
 *				display LCD como saida. Essa rotina é baseada no controlador 
 *				de LCD Hitachi HD44780. Configura os parametros de comunicação
 *				com o display, tais como:
 *					- modo de operação (4 bits)
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
 
 #ifdef PERMITE_NUMEROS

/******************************************************************************
 * Funcao:		char * itoa(int value)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) 
 * Saída:		char * ponteiro para um string
 * Descrição: 	Esta função converte numeros inteiros positivos e negativos
 *				para strings.
 *****************************************************************************/
 
char * my_itoa(int value);
 
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
 * Funcao:		void EscreveFloatLCD(float valor, char formatacao)
 * Entrada:		valor: float com sinal a ser escrito no	display.
 *				formataçao: numero de casas decimais desejadas (0 a 4 casas decimais)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina escreve o numero float no display a partir da posição
 *				de memoria atual do cursor ou da posição de memória escolhida com as
 *				funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFloatLCD(float valor, char formatacao);
 
 #endif
 
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

#ifdef PERMITE_FUNCOES_PGM

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
 extern void EscreveFraseConstLCD(const char *buffer);

#endif


#endif
