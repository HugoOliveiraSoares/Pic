/******************************************************************************
 *
 *           SEMPRA Bibliotecas (PIC32MX775F512L)- tecladoPS2
 *
 ******************************************************************************
 * Nome do Arquivo:     tecladoPS2.h
 * Dependencias:    	Veja seção INCLUDES
 * Processador:       	PIC32MX775F512L
 * Opção de Clock:      HS 8MHz (externo) - CPU: 80MHz
 *                      Barramento de Periférico (PBU) = 80MHz (interno)
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
 * Descrição:		Biblioteca desenvolvida para trabalhar com teclado 
 *			de computador (PS/2) no PIC.
 *
 * 			H A R D W A R E:
 *
 *  			Conector Femea:		Pinos | Porta | Função
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
 *		Data 5V, Clock 0V - Impede comunicação
 *		Data 0V, Clock 5V - PIC ñ requisita envio de dados
 *	
 *		Comunicação Telcado -> PIC
 *
 *		1 start bit.  Sempre 0 (Pode ser usado para ativar interrupção).
 *		8 data bits, Menos significante primeiro.
 *		1 bit de paridade (paridade ímpar
 *		1 stop bit.  Sempre 1.
 *
 *              O responsável por gerar o clock é o teclado.
 *
 * Notas:
 *		- A função char LeDadoTeclado() pode ser chamada como pulling ou
 *		ser chamada em uma SRF. A configuração da interrupção e a
 *              rotina de tratamento devem ser feitas pelo usuário em seu
 *              programa.
 *		
 *****************************************************************************/
/*****************************************************************************  
 * Log de modificações:
 * 29/02/2012   -   Adaptação para plataforma E-P32
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
 * Saída:	    - ASCII correspondente a tecla pressionada.
 *		    - MISSMATCH_ERRO caso a tecla não foi encontrada
 *                  - TIMEOUT_ERRO caso o teclado pare de responder.
 *                  - PARIDADE_ERRO caso o valor recebido nao possua o bit de paridade correto
 *
 * Descrição: 	A função deve ser chamada quando houver dado a ser recebido.
 *		Ela receberá o dado e retornará o ASCII correspondente.
 *		Caso o valor não seja reconhecido o retorno será 0.
 *		Caso ocorra um erro de comunicação o retorno sera 256.
 *		Alguns valores uteis (ASCII)
 *			Enter: 0x0D
 *			BackSpace: 0x08
 *			Esc: 
 *
 * Nota:   	Esta função pode ser utilizada através de  pulling. Para isto
 *		ela deve ser chamada dentro de um if que verifica o barramento
 *		de dados:
 *		if(!PS2_DATAPIN)
 *		{
 *			caractere = LeDadoTeclado();
 *		}
 *		A função também pode ser chamada dentro de uma rotina de tratamento
 *		de interrupção.
 *
 *****************************************************************************/
 unsigned char LeDadoTeclado();


