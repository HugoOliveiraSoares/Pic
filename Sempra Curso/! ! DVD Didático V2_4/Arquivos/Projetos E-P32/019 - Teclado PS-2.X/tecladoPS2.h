/******************************************************************************
 *
 *           SEMPRA Bibliotecas (PIC32MX775F512L)- tecladoPS2
 *
 ******************************************************************************
 * Nome do Arquivo:     tecladoPS2.h
 * Dependencias:    	Veja se��o INCLUDES
 * Processador:       	PIC32MX775F512L
 * Op��o de Clock:      HS 8MHz (externo) - CPU: 80MHz
 *                      Barramento de Perif�rico (PBU) = 80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P32 SEMPRA V1.01
 *
 * Autor:		Bruno Silveira Avelar
 *			James Hamilton Oliveira Junior
 *
 * Data:		v1 - 01/Fev/2011 - Bruno Silveira Avelar
 *                      v2 - 04/Set/2012 - Bruno Silveira Avelar
 *
 * Descri��o:		Biblioteca desenvolvida para trabalhar com teclado 
 *			de computador (PS/2) no PIC.
 *
 * 			H A R D W A R E:
 *
 *  			Conector Femea:		Pinos | Porta | Fun��o
 *                                        1      RA15    Teclado Data
 *      	6 [] 5			  2      RA15	 MOUSE Data
 *             4      3                   3       - 	 GND
 *                                        4       -	 VCC
 *            	 2  1                     5      RA10	 Telcado Clock
 *                                        6      RA10	 MOUSE Clock
 *
 *		F I R M W A R E:
 *					
 *		Estados do barramentos:
 *
 *		Data 5V, Clock 5V - Idle
 *		Data 5V, Clock 0V - Impede comunica��o
 *		Data 0V, Clock 5V - PIC � requisita envio de dados
 *	
 *		Comunica��o Telcado -> PIC
 *
 *		1 start bit.  Sempre 0 (Pode ser usado para ativar interrup��o).
 *		8 data bits, Menos significante primeiro.
 *		1 bit de paridade (paridade �mpar
 *		1 stop bit.  Sempre 1.
 *
 *              O respons�vel por gerar o clock � o teclado.
 *
 * Notas:
 *		- A fun��o char LeDadoTeclado() pode ser chamada como pulling ou
 *		ser chamada em uma SRF. A configura��o da interrup��o e a
 *              rotina de tratamento devem ser feitas pelo usu�rio em seu
 *              programa.
 *		
 *****************************************************************************/
/*****************************************************************************  
 * Log de modifica��es:
 * 29/02/2012   -   Adapta��o para plataforma E-P32
 * 04/09/2012   -   Melhoria do algoritimo de leitura do telcaodo
 *
******************************************************************************/

#include <p32xxxx.h>
#include "HardwareProfile.h"


#define MISSMATCH_ERRO 0
#define TIMEOUT_ERRO   1
#define PARIDADE_ERRO  2

/******************************************************************************
 * Funcao:		char LeDadoTeclado()
 * Entrada:		Nenhuma (void)
 *
 * Sa�da:	    - ASCII correspondente a tecla pressionada.
 *		    - MISSMATCH_ERRO caso a tecla n�o foi encontrada
 *                  - TIMEOUT_ERRO caso o teclado pare de responder.
 *                  - PARIDADE_ERRO caso o valor recebido nao possua o bit de paridade correto
 *
 * Descri��o: 	A fun��o deve ser chamada quando houver dado a ser recebido.
 *		Ela receber� o dado e retornar� o ASCII correspondente.
 *		Caso o valor n�o seja reconhecido o retorno ser� 0.
 *		Caso ocorra um erro de comunica��o o retorno sera 256.
 *		Alguns valores uteis (ASCII)
 *			Enter: 0x0D
 *			BackSpace: 0x08
 *			Esc: 
 *
 * Nota:   	Esta fun��o pode ser utilizada atrav�s de  pulling. Para isto
 *		ela deve ser chamada dentro de um if que verifica o barramento
 *		de dados:
 *		if(!PS2_DATAPIN)
 *		{
 *			caractere = LeDadoTeclado();
 *		}
 *		A fun��o tamb�m pode ser chamada dentro de uma rotina de tratamento
 *		de interrup��o.
 *
 *****************************************************************************/
 unsigned char LeDadoTeclado();


