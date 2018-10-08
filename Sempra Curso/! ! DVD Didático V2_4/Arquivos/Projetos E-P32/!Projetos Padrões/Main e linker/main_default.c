/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Op��o de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 *                      Barramento de Perif�ricos - 80MHz(interno)
 *
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Pr�tica: 			
 * Plataforma:			Placa SEMPRA E-P32 V1.0
 *
 * Autor:				SEMPRA
 * Vers�o:				v1.0
 * Descri��o:   	|
 * 
 * 
 * 
 *****************************************************************************/

/** I N C L U D E S ****************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>    // Biblioteca do compilador que cont�m algumas 
                        // fun��es destinadas aos PICS da fam�lias 32

#include <plib.h>       // Biblioteca do compilador para uso dos perif�ricos 
                        // do PIC32.

#include "HardwareProfile - PICMinas32.h"  // Biblioteca da SEMPRA que cont�m
                                           // informa��es e defines de alguns
                                           // dispositivos e perif�ricos ligados
                                           // �s portas do PIC32, presentes no
                                           // kit de desenvolvimento E-P32


/** C O N F I G U R A � � O ********************************************/

// Diretiva utilizada para configura��o do sistema caso o usu�rio deseje gravar
// com gravadora pr�pria, sem necessidade do bootloader.
// #define NOT_BOOTLOADER

#ifdef NOT_BOOTLOADER

// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto
// Configuration Bit settings

// Clock da CPU:
// SYSCLK = 80 MHz (8MHz Cristal * FPLLIDIV * FPLLMUL * FPLLODIV)
// SYSCLK = 80 MHz (8MHz * 1/2 * 20 * 1/1)

// Clock do barramento de perif�ricos:
// PBCLK = 10 MHz (SYSCLK * 1/FPBDIV)
// PBCLK = 10 MHz (80MHz * 1/8)

// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF

#pragma config FPLLMUL    = MUL_20
#pragma config FPLLIDIV   = DIV_2
#pragma config FPLLODIV   = DIV_1
#pragma config FWDTEN     = OFF
#pragma config POSCMOD    = HS
#pragma config FNOSC      = PRIPLL
#pragma config FPBDIV     = DIV_1

#pragma config CP         = OFF    // Code Protect
#pragma config BWP        = OFF    // Boot Flash Write Protect
#pragma config PWP        = OFF    // Program Flash Write Protect

#endif


/** D E F I N E S ******************************************************/


/** P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.

/** F U N C O E S ************************************************************/


/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *		pois esta � a primeira a ser chamada ap�s o	reset do
 *		microcontrolador.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/
int main(void)
{	
                // Declara��o de vari�veis

    SystemConfig();  // Configura as portas e otimiza o desempenho do PIC 

    AD1PCFG = 0xffffffff; // Todos pinos como digital
    ODCBSET = 0x00000000; // Porta B com coletor aberto (falar pro Bruninho que isso nao funciona)

    while(1)   // La�o infinito que executa o principal funcionamento do projeto

    {


    // Linhas de instru��es e comandos definidos pelo programador


    } // end while(1)
} // end main

/******************************************************************************
 * Funcao:    	void SystemConfig(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Configura��o do sistema. Configura��o necess�ria para que o
 *              microcontrolador funcione de acordo com as aplica��es
 *              desejadas. Configura os pinos digitais de entrada e sa�da
 *              e os demais perif�ricos utilizados no projeto.
 *****************************************************************************/
void SystemConfig()
{
	/* ********************************************************************
        *
        *  Quando o PIC32 � iniciado ele � configurado para:
	* - NO Caching turned on
	* - NO Prefetch buffer enabled
	* - 7 FLASH wait states 
	* - 1 SRAM wait states. 
	*
	* Todas estas configura��es afetam a perfomasse do microcontrolador
	* fazendo que ele funcione significamente mais lento do que o esperado.
	* Para configurar corretamente, utilizamos a fun��o 
        * SYSTEMConfigPerformance(80000000);
	* passando o valor do clock da CPU como parametro. Esta fun��o 
        * configurar� as propriedades de performasse como numero correto de 
        * esperas (wait state) da mem�ria Flash e mem�ria RAM e o uso da 
        * mem�ria cache.
        * 
	**********************************************************************/
	
        SYSTEMConfigPerformance(80000000);
  
	mOSCSetPBDIV (OSC_PB_DIV_1);

            
        DDPCONbits.JTAGEN = 0;  // Desabilita a porta de JTAG


} // end SystemConfig()
