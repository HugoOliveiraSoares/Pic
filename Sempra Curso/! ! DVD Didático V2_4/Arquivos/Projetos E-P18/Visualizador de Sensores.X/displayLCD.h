/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.h
 * Dependencias:    	Veja se��o INCLUDES
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU: 48MHz	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:          Placa E-P18 v3.0, v3.5 e v3.6
 *
 * Autor:		M.Sc. Henrique Resende Martins
 * 			Mauricio Ferrari Santos Corr�a
 *			Bruno Silveira Avelar
 *			James Hamilton Oliveira Junior
 *
 * Data:		v1 - 15/Fev/2009 - M.Sc. Henrique Resende Martins
 *			v2 - 28/Abr/2009 - Mauricio Ferrari Santos Corr�a
 *			v3 - 16/Jun/2009 - Mauricio Ferrari Santos Corr�a
 *			v4 - 18/Nov/2009 - Mauricio Ferrari Santos Corr�a
 *			v5 - 05/Dez/2009 - Mauricio Ferrari Santos Corr�a
 *			v6 - 28/fev/2010 - Bruno Silveira Avelar
 *			v7 - 10/Mar/2010 - Mauricio Ferrari Santos Corr�a
 *			v8 - 15/Out/2010 - Mauricio Ferrari Santos Corr�a
 *			v9 - 15/Dez/2010 - Mauricio Ferrari Santos Corr�a
 *			v10- 17/Jan/2011 - Mauricio Ferrari Santos Corr�a
 *			v11- 19/Jan/2011 - James Hamilton Oliveira Junior
 *			v12- 02/Mai/2011 - Mauricio Ferrari Santos Corr�a
 *			v13- 05/Out/2011 - Mauricio Ferrari Santos Corr�a
 *
 * Descri��o:		No projeto da placa E-P18 o display LCD � ligado �s portas
 *			digitais diversas do PIC 18F4550. A placa E-P18 utiliza
 *			os seguintes pinos para comunica��o com o display LCD:
 *                          PIC18F4550(pino):: Display LCD
 *				RD4 (27)  	::	  D4
 *				RD5 (28)  	::	  D5
 *				RD6 (29)  	::	  D6
 *				RD7 (30)  	::	  D7
 *				RD2 (21)  	:: 	  RS
 *				RD3 (22)  	::	  E
 *				 GND		::	  R/W
 *			OBS: o pino R/W do display � ligado na placa E-P18 ao GND
 *			atrav�s de um resistor de pull-down, assim o LCD opera no 
 *			modo escrite(Write) o tempo todo. No entanto o c�digo C foi
 *			escrito mostrando a imlementa��o onde um pino do PIC � 
 *			utilizado para a fun��o R/W, assim comentando o inicio das 
 *      		linhas correspondentes com "//n�o usado //".
 *   Notas:
 *              	- Essa bliblioteca de rotinas foi escrita pensando em um LCD
 *                      16x2 FDCC1602E implementado com o controlador SPLC780D, mas pode
 *                      ser utilizado com qualquer LCD 16x2 com controladores equivalentes
 *                      como, por exemplo, o controlador Hitachi HD44780 LCD controller.
 *
 *                      - O usu�rio deve definir os seguintes itens:
 *                      -- O tipo de interface de comunica��o do LDC com o PIC (4 ou 8-bits):
 *                      Se for o modo 4-bit, utilizar o upper nibble (nibble � metade de um Byte)
 *			 , ou seja, enviar primeiro os 4 bits mais significativos (upper nibble)
 *			 e depois os 4 bits menos sgnificativos (lower nibble).
 *
 *                      -- Cursor e/ou Blink:
 *                          O usu�rio poder� definir se quer visualizar cursor, blink
 *                          ou nenhum dos dois.
 *          
 *			-- O sincronismo da comunica��o com o LCD:
 *                      As temporiza��es entre o envio de comandos, n�o foi utilizado
 *			   o bit de Busy do LCD, mas sim, atrav�s de fun��es de atraso.
 *			   A fun��o utilizada foi a Delay10KTCYx() da bilioteca padr�o C18
 *			   delays.h que aparece na se��o INCLUDE deste arquivo.
 * 			   Os tempos de delay escolhidos est�o colocados nos defines:
 *			   DELAY_SINC e DELAY_INICIO, que foram ecolhidos bem acima do 
 *			   tempo m�nimo requerido pelo display de LCD (5ms o de sincronismo e
 *			   15ms o inicial).
 *****************************************************************************/
#ifndef __DISPLAYLCD_H
#define __DISPLAYLCD_H

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
// Define dos pinos de DADOS do LCD ligados no PIC18F4550
#define D4       LATDbits.LATD4
#define D5       LATDbits.LATD5
#define D6		 LATDbits.LATD6
#define D7       LATDbits.LATD7

// Define do TRIS dos pinos de DADOS do LCD ligados no PIC18F4550
#define TRIS_D4  TRISDbits.TRISD4
#define TRIS_D5  TRISDbits.TRISD5
#define TRIS_D6  TRISDbits.TRISD6
#define TRIS_D7  TRISDbits.TRISD7

// Define dos pinos de CONTROLE do LCD ligados no PIC18F4550
#define RS_PIN   LATDbits.LATD2
#define E_PIN    LATDbits.LATD3
//n�o usado // #define RW_PIN   LATBbits.LATB2

// Define os TRIS dos pinos de CONTROLE do LCD ligados no PIC18F4550
#define TRIS_RS  TRISDbits.TRISD2
#define TRIS_E   TRISDbits.TRISD3
//n�o usado // #define TRIS_RW  TRISBbits.TRISB2

// Define o valor dos delays baseado no clock da CPU de 48 MHz
#define DELAY_SINC()	Delay1KTCYx(12)		// Delay de 1ms para Fosc=48MHz
											// Geralmente 1ms � suficiente, mas
											// depende do controlador do display
											// Aumente conforme a necessidade!
											
#define DELAY_5ms()	Delay10KTCYx(6)		// Delay de 5ms para Fosc=48MHz




/*** D E F I N E S D E C O N F I G U R A C A O *******************************/
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Remove todos os caracteres do display e retorna a posi��o do
 *				cursor para a linha 1 e coluna 1
 *****************************************************************************/
#define LimpaDisplay()  	EscreveComandoLCD(0b00000001)
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Liga o display de LCD e retira o cursor do visor.
 *****************************************************************************/
#define LigaDisplay()  		EscreveComandoLCD(0b00001000)
/******************************************************************************
 * Define:		LimpaDisplay()
 * Descri��o: 	Desliga o display. (N�o apaga o backlight)
 *****************************************************************************/
#define DesligaDisplay()  	EscreveComandoLCD(0b00001100)
/******************************************************************************
 * Define:		LigaCursor()
 * Descri��o: 	Faz com que o cursor apare�a no LCD caso este esteja ligado
 *				e liga a tela com o cursor caso este esteja desligado.
 *****************************************************************************/
#define LigaCursor()		EscreveComandoLCD(0b00001110)
/******************************************************************************
 * Define:		DesligaCursor()
 * Descri��o: 	Faz com o cursor suma do LCD caso este esteja ligada e com que
 *				ligue o LCD sem o cursor caso este esteja desligado
 *****************************************************************************/
#define DesligaCursor()		EscreveComandoLCD(0b00001100)
/******************************************************************************
 * Define:		PiscaCursor()
 * Descri��o: 	Faz com que o cursor apare�a no LCD e fique piscando caso este 
 *              esteja ligado e liga a tela com o cursor piscando caso este 
 *              esteja desligado.
 *****************************************************************************/
#define PiscaCursor()		EscreveComandoLCD(0b00001111)


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
 * Entrada:		N�mero da linha e da coluna em que se deseja escrever o caracter 
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
