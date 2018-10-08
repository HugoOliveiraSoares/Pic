/******************************************************************************
 *
 *            PICMINAS PROJETOS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F256L
 * Opção de Clock:		HS 8MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	Sempra
 * Prática: 			
 * Plataforma:			Placa E-P32
 *
 * Autor:				Bruno Avelar
 * Versão:				v1.0
 * Descrição:   		Este firmware cria arquivos e diretórios em um cartao SD
 *						conectado ao KIT. Para cada tecla do teclado matricial pressionada
 *						será criada um diretório ou um arquivo naquele diretório.
 *						Quando pressionar o botao 0 os diretórios existentes do cartao
 *						com todos os arquivos e sub deretórios serão apagados mas os 
 *						arquivos na pasta raiz será mantido.
 *					
 *****************************************************************************/

#define NOT_BOOTLOADER


#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include <string.h>

#include "HardwareProfile.h"
#include "MDD File System/FSIO.h"
#include "Delays.h"




#ifdef NOT_BOOTLOADER
// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto
// Configuration Bit settings

// Clock da CPU:
// SYSCLK = 80 MHz (8MHz Cristal * FPLLIDIV * FPLLMUL * FPLLODIV)
// SYSCLK = 80 MHz (8MHz * 1/2 * 20 * 1/1)

// Clock do barramento de periféricos:
// PBCLK = 80 MHz (SYSCLK * 1/FPBDIV)
// PBCLK = 80 MHz (80MHz * 1/1)

// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF


    #pragma config FPLLMUL  = MUL_20        // PLL Multiplier
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = OFF            // Background Debugger Enable

#endif

/**  P R O T O T I P O S   P R I V A D O S *********************************/

void SystemConfig(); // Configura o estado inicial do sistema.

/***************************************************************************/
/**  V A R I A V E I S    G L O B A I S ************************************/

char *sendBuffer;
char send2[] = "2";
char receiveBuffer[50];

/***************************************************************************/
/**  D E F I N E S *********************************************************/


/***************************************************************************/

/*
 *
 *
 *
 */
int main (void)
{
   FSFILE * pointer;
   unsigned int result;		

   SystemConfig();
   
   while (1)
   {   

    }
}


void SystemConfig()
{

   /* Quando o PIC32 é iniciado ele é configurado para:
	* - NO Caching turned on
	* - NO Prefetch buffer enabled
	* - 7 FLASH wait states 
	* - 1 SRAM wait states. 
	*
	* Todas estas configurações afetam a perfomasse do microcontrolador
	* fazendo que ele funcione significamente mais lento do que o esperado.
	* Para configurar corretamente, utilizamos a função SYSTEMConfigPerformance(80000000);
	* passando o valor do clock da CPU como parametro. Esta função configurará
	* as propriedades de performasse como numero correto de esperas (wait state) da
	* memória Flash e memória RAM e o uso da memória cache.
	*/
	SYSTEMConfigPerformance(80000000);
   /*
    *
    */
	mOSCSetPBDIV (OSC_PB_DIV_1);	

    // Turn on the interrupts
  	INTEnableSystemMultiVectoredInt();

	// Desabilita a porta de JTAG
    DDPCONbits.JTAGEN = 0;

    AD1PCFG = 0xffffffff; // Todos pinos como digital
	

	//Porta do CS do SPI
	TRISDbits.TRISD9 = 0;
	PORTDbits.RD9 = 0;
	
   while (!FSInit()) {}

}	
