/******************************************************************************
 *
 *	            Biblioteca PICMINAS (PIC32MX775F256L)
 *
 ***********************************************************************************************************************************************************
 * Nome do Arquivo:     displayLCDconfig.h
 * Dependencias:    	
 * Empresa:         	PICMINAS
 * Plataforma:			Placa de Desenvolvimento PICMINAS32 v1.0
 * Descri��o:			Este arquivo possui as configura��es da biblioteca de
 *						LCD utilizada pelo PICMinas. 
 *
 ****************************************************************************/

#include "Delays.h"		// Biblioteca padr�o C18 Microchip para uso de rotinas de atraso (delay)
						// mais informa��es nos arquivos de ajuda da biblioteca C18
						// presentes na propria pasta de instala��o, por exemplo,
						// C:\mplabc18\doc\hlpC18Lib.chm
						// Procure pelo item: "Delay Functions"

#include <stdlib.h>		// Biblioteca padr�o C18 Microchip para uso de rotinas de convers�o
						// de tipos como itoa(). Mais informa��es nos arquivos de ajuda da
						// biblioteca C18 presentes na propria pasta de instala��o, por exemplo,
						// C:\mplabc18\doc\hlpC18Lib.chm
						// Procure pelo item: "Data Conversion Functions"
#include <math.h>						 

/** PINOS DE COMUNICA��O ************************************************************/

#define OPEN_COLECTOR_A ODCA   |= 0x00000033 //0b0000000000110011;
#define OPEN_COLECTOR_G ODCG   |= 0x00006100 //0b0110000100000000;

// Define dos pinos de DADOS do LCD 
#define D4       LATAbits.LATA0
#define D5       LATAbits.LATA1
#define D6		 LATAbits.LATA4
#define D7       LATAbits.LATA5

// Define do TRIS dos pinos de DADOS do LCD
#define TRIS_D4  TRISAbits.TRISA0
#define TRIS_D5  TRISAbits.TRISA1
#define TRIS_D6  TRISAbits.TRISA4
#define TRIS_D7  TRISAbits.TRISA5

// Define dos pinos de CONTROLE do LCD
#define RS_PIN   LATGbits.LATG8
#define E_PIN    LATGbits.LATG14
#define RW_PIN   LATGbits.LATG13

// Define os TRIS dos pinos de CONTROLE do LCD 
#define TRIS_RS  TRISGbits.TRISG8
#define TRIS_E   TRISGbits.TRISG14
#define TRIS_RW  TRISGbits.TRISG13



/** TEMPOS DE SINCRONISMO ************************************************************/

// Define o valor dos delays baseado no clock da CPU de 48 MHz
#define DELAY_SINC()	DelayMsx(1)	  		// Delay de 1ms
											// Geralmente 1ms � suficiente, mas
											// depende do controlador do display
											// Aumente conforme a necessidade!
											
#define DELAY_5ms()		DelayMsx(5)			// Delay de 5ms



/** LISTA DE COMANDOS ******************************************************************/

#define LIMPA_DISPLAY	0b0000000001
#define LIGA_DISPLAY	0b0000001000
#define DESLIGA_DISPLAY	0b0000001100
#define LIGA_CURSOR	0b0000001110
#define DESLIGA_CURSOR	0b0000001100
#define PISCA_CURSOR	0b0000001111


/** LISTA DE FUNCIONALIDADES ******************************************************************
 * Voce deve comentar neste arquivo as funcionalidades que n�o deseja utilizar em sua aplica��o.
 * Desta forma voc� economizar� espa�o na mem�ria de programa de seu microcontrolador. 
 *********************************************************************************************/

// Informa��o: Este define habilita/desabilita as fun��es de escrita atrav�s da mem�ria de programa
// Descri��o:  Habilitando este define voc� poder� utilizar a fu��o: EscreveFraseRomLCD. Caso
// 			   sua aplica��o na fa�a uso desta fun��o comente o define PERMITE_FUNCOES_PGM e 
//			   economize espa�o em sua mem�ria de programa.

#define PERMITE_FUNCOES_PGM

// Informa��o: Este define habilita/desabilita as fun��es que escrevem n�meros no LCD
// Descri��o:  Habilitando este define voc� poder� utilizar a fu��es: EscreveInteiroLCD e EscreveFloatLCD. Caso
// 			   sua aplica��o na fa�a uso desta fun��o comente o define PERMITE_NUMEROS e 
//			   economize espa�o em sua mem�ria de programa.

#define PERMITE_NUMEROS



