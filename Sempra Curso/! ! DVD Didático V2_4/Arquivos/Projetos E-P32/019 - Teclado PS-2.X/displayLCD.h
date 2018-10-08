/******************************************************************************
 *
 *           SEMPRA Bibliotecas (PIC32MX775F512L) - Display de LCD Alfanumerico
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.h
 * Dependencias:    	<displayLCDconfig> (e suas dependecias: <p18cxxx.h> <delays.h> <stdlib.h> )
 * Processador:       	PIC32MX775F512L
 * Op��o de Clock:      HS 8MHz (externo) - CPU: 80MHz(interno)
 *                      Barramento de Perif�rico (PBU) = 80MHz (interno)
 * Compilador:        	C32 v 1.01 ou superior*
 *                      obs: a vers�o 2.02 do compilador C32 j� possui incluso
 *                      em sua biblioteca algumas fun��es que podem gerar
 *                      algum conflito com as bibliotecas criadas pela SEMPRA
 *                      com o mesmo nome.
 * Empresa:         	SEMPRA
 * 
 * Plataforma:		Kit E-P32
 *
 * Autores:		M.Sc. Henrique Resende Martins
 * 			Mauricio Ferrari Santos Corr�a
 *			Bruno Silveira Avelar
 *                      James Hamilton Oliveira Junior
 *
 * Data:		v1 - 06/Fev/2011 - Bruno Silveira Avelar
 *                      v2 - 04/Set/2012 - Bruno Silveira Avelar
 *
 * Descri��o:		Biblioteca para escrita no display de LCD
 *			alfanum�rico. No projeto do Kit E-P32 o display
 *			LCD � ligado � portas digitais diversas do 
 *			PIC 32. O Kit utilizam os seguintes
 *                      pinos para comunica��o com o display LCD:
 *
 *                     PIC32MX775F512L(pino)    ::   Display LCD
 *				RA0   (17)  	::	  D4
 *				RA1   (38)  	::	  D5
 *				RRA4  (60)  	::	  D6
 *				RA5   (61)  	::	  D7
 *				RG8   (12)  	:: 	  RS
 *                              RG14  (96)  	::	  E
 *			   	RG13  (97)	::	  R/W
 *
 *
 *	 OBS: o pino R/W do display � ligado na placa de desenvolvimento
 *	      ao GND atrav�s de um resistor de pull-down, assim o
 *            LCD opera no modo escrite(Write) o tempo todo. No entanto o
 *	      c�digo C foi escrito mostrando a imlementa��o onde um pino do
 *	     PIC � utilizado para a fun��o R/W, assim comentando o inicio das
 *	     linhas correspondentes com "//n�o usado //".
 *   Notas:
 *	  - Essa bliblioteca de rotinas foi escrita pensando em um LCD
 *        16x2 FDCC1602E implementado com o controlador SPLC780D, mas pode
 * 	  ser utilizado com qualquer LCD 16x2 com controladores equivalentes
 *        como, por exemplo, o controlador Hitachi HD44780 LCD controller.
 *
 *          -- Cursor e/ou Blink:
 *             O usu�rio poder� definir se quer visualizar cursor, blink 
 *             ou nenhum dos dois.
 *          
 *          -- O sincronismo da comunica��o com o LCD:
 *             As temporiza��es entre o envio de comandos, n�o foi utilizado
 *	       o bit de Busy do LCD, mas sim, atrav�s de fun��es de atraso.
 *	       A fun��o utilizada foi a Delay10KTCYx() da bilioteca padr�o C18
 *	       delays.h que aparece na se��o INCLUDE deste arquivo.
 * 	       Os tempos de delay escolhidos est�o colocados nos defines:
 *	       DELAY_SINC e DELAY_INICIO, que foram ecolhidos bem acima do
 *	       tempo m�nimo requerido pelo display de LCD (5ms o de sincronismo
 *             e 15ms o inicial).
 *
 *            Controle de vers�es:
 *
 *             v1 - Lan�amento
 *             v2 - Mudan�a do Hardware Profile para incorporar as defini��es do LCD
 *
 *****************************************************************************/
#ifndef __DISPLAY_LCD_H
#define __DISPLAY_LCD_H

/** I N C L U D E S **********************************************************/

#include "displayLCDconfig.h" // Arquivo contendo as configura��es do LCD
							  // definidas pelo usu�rio

/*** D E F I N E S   D E   U S O *********************************************/
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Remove todos os caracteres do display e retorna a posi��o do
 *				cursor para a linha 1 e coluna 1
 *****************************************************************************/
#define LimpaDisplay()  	EscreveComandoLCD(LIMPA_DISPLAY)
/******************************************************************************
 * Define:		LigaDisplay()
 * Descri��o: 	Liga o display de LCD e retira o cursor do visor.
 *****************************************************************************/
#define LigaDisplay()  		EscreveComandoLCD(LIGA_DISPLAY)
/******************************************************************************
 * Define:		DesligaDisplay()
 * Descri��o: 	Desliga o display. (N�o apaga o backlight)
 *****************************************************************************/
#define DesligaDisplay()  	EscreveComandoLCD(DESLIGA_DISPLAY)
/******************************************************************************
 * Define:		LigaCursor()
 * Descri��o: 	Faz com que o cursor apare�a no LCD caso este esteja ligado
 *				e liga a tela com o cursor caso este esteja desligado.
 *****************************************************************************/
#define LigaCursor()		EscreveComandoLCD(LIGA_CURSOR)
/******************************************************************************
 * Define:		DesligaCursor()
 * Descri��o: 	Faz com o cursor suma do LCD caso este esteja ligada e com que
 *				ligue o LCD sem o cursor caso este esteja desligado
 *****************************************************************************/
#define DesligaCursor()		EscreveComandoLCD(DESLIGA_CURSOR)
/******************************************************************************
 * Define:		PiscaCursor()
 * Descri��o: 	Faz com que o cursor apare�a no LCD e fique piscando caso este 
 *              esteja ligado e liga a tela com o cursor piscando caso este 
 *              esteja desligado.
 *****************************************************************************/
#define PiscaCursor()		EscreveComandoLCD(PISCA_CURSOR)


/**  P R O T O T I P O  D E  F U N C O E S  **********************************/
/******************************************************************************
 * Funcao:		void ConfiguraLCD(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:           Configura portas do PIC 18F4550 que est�o conectadas ao
 *			display LCD como saida. Essa rotina � baseada no controlador 
 *			de LCD Hitachi HD44780. Configura os parametros de comunica��o
 *			com o display, tais como:
 *				- modo de opera��o (4 bits)
 *				- tipo de cursor
 *				- tamanho da fonte
 *			Ao final da configura��o limpa o display.
 *****************************************************************************/
 extern void ConfiguraLCD(void);

/******************************************************************************
 * Funcao:		void EscreveComandoLCD(unsigned char cmd)
 * Entrada:		cmd: comando que ser� enviado para o LCD
 * Sa�da:		Nenhuma (void)
 * Descri��o:           Escreve um comando para o display de LCD.
 *****************************************************************************/
 extern void EscreveComandoLCD(unsigned char cmd);
 
/******************************************************************************
 * Funcao:		void EnderecoCursor(unsigned char endereco)
 * Entrada:		endereco: endere�o da memoria de dados do display que se deseja apontar
 * Sa�da:		Nenhuma (void)
 * Descri��o: 		Essa rotina seta o endere�o da memoria RAM de dados do 
 *                      display LCD para o endere�o	que se deseja escrever um caracter
 *			usando as fun��es EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
 extern void EnderecoCursor(unsigned char endereco);
 
/******************************************************************************
 * Funcao:		void PosicaoCursorLCD(unsigned char endereco)
 * Entrada:		N�mero da linha e da coluna em que se desja escrever o caracter 
 * Sa�da:		Nenhuma (void)
 * Descri��o: 		Essa rotina posiciona o cursor do display de LCD para a linha
 *                      e coluna em que se deseja escrever um caracter usando as fun��es
 *                  	EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
extern void PosicaoCursorLCD(unsigned char linha, unsigned char coluna);

/******************************************************************************
 * Funcao:		void EscreveCaractereLCD(unsigned char data)
 * Entrada:		data: Byte de dados para ser escrito na memoria RAM do LCD
 * Sa�da:		Nenhuma (void)
 * Descri��o: 		Essa rotina escreve o byte de caracteres no display a partir da
 *                      posi��o de memoria atual do cursor ou da posi��o de mem�ria
 *			escolhida com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveCaractereLCD(char data);
 
 #ifdef PERMITE_NUMEROS

/******************************************************************************
 * Funcao:		char * itoa(int value)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) 
 * Sa�da:		char * ponteiro para um string
 * Descri��o:           Esta fun��o converte numeros inteiros positivos e negativos
 *			para strings.
 *****************************************************************************/
 
char * itoa(int value);
 
/******************************************************************************
 * Funcao:		void EscreveInteiroLCD(int valor)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) a ser escrito no
 *			display.
 * Sa�da:		Nenhuma (void)
 * Descri��o:           Essa rotina escreve o numero inteiro no display a partir da posi��o
 *			de memoria atual do cursor ou da posi��o de mem�ria escolhida com as
 *			fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveInteiroLCD(int valor);
 
 /******************************************************************************
 * Funcao:		void EscreveFloatLCD(float valor, char formatacao)
 * Entrada:		valor: float com sinal a ser escrito no	display.
 *			formata�ao: numero de casas decimais desejadas (0 a 4 casas decimais)
 * Sa�da:		Nenhuma (void)
 * Descri��o:           Essa rotina escreve o numero float no display a partir da posi��o
 *			de memoria atual do cursor ou da posi��o de mem�ria escolhida com as
 *			fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFloatLCD(float valor, char formatacao);
 
 #endif
 
/******************************************************************************
 * Funcao:		void EscreveFraseRamLCD(char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de dados(RAM)
 * Sa�da:		Nenhuma (void)
 * Descri��o:           Essa rotina copia uma string terminada com caracter nulo
 *			da memoria de dados do microcontrolador para o display de LCD.
 *			A string apontada por *buffer � copiada no display a partir da
 *			posi��o de memoria atual do cursor ou da posi��o de mem�ria
 *			escolhida com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseRamLCD(char *buffer);

#ifdef PERMITE_FUNCOES_PGM

/******************************************************************************
 * Funcao:		void EscreveFraseRomLCD(const rom char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de programa(ROM)
 * Sa�da:		Nenhuma (void)
 * Descri��o:           Essa rotina copia uma string terminada com caracter nulo
 *			da memoria de programa do microcontrolador para o display de LCD.
 *			A string apontada por *buffer � copiada no display a partir da
 *			posi��o de memoria atual do cursor ou da posi��o de mem�ria escolhida
 *			com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
 extern void EscreveFraseConstLCD(const char *buffer);

#endif


#endif
