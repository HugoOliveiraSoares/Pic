/******************************************************************************
 *
 *           SEMPRA Bibliotecas (PIC32MX775F512L) - Display de LCD Alfanumerico
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCDconfig.h
 * Dependencias:    	<p18cxxx.h> <delays.h> <stdlib.h> (Veja se��o INCLUDES)
 * Empresa:         	SEMPRA
 * Plataforma:			kit de Desenvolvimento E-P32 v1.01
 *
 * Descri��o:			Este arquivo possui as configura��es da biblioteca de
 *				LCD utilizada pela Sempra. Este cabe�alho foi
 *                              desenvolvido de modo que permitisse a altera��o
 *                              do usu�rio de maneira mais simples caso haja
 *                              migra��o de plataforma. Assim, as fun��es s�o
 *                              as mesmas, s� a configura��o das portas aos
 *                              pinos de dados e controle � que sofrem altera��o
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

#include "HardwareProfile.h"

/** LISTA DE COMANDOS ******************************************************************/

#define LIMPA_DISPLAY	0b0000000001
#define LIGA_DISPLAY	0b0000001000
#define DESLIGA_DISPLAY	0b0000001100
#define LIGA_CURSOR		0b0000001110
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



