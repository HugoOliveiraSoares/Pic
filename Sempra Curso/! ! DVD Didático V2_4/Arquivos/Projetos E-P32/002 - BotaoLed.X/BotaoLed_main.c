/*******************************************************************************
 *                  SEMPRA  E-P32 Bot�o LED     			       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     BotaoLed_main.c                                        *
 * Dependencias:    	Veja a se��o INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Op��o de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Vers�o:		v1.0                                                   *
 * Descri��o:        	Este programa introdut�rio utiliza portas digitais     *
 *                      do PIC32MX. Ao pressionar o Bot�o 1 do KIT E-P32 o     *
 *                      LED0 ir� acender, ao solta-lo o LED1 ir� apagar.       *
 *                      O mesmo ocorre com os Bot�es 2, 3 e 4 com os LEDs 1, 2 *
 *                      e 3.                                                   *
 *******************************************************************************
 * *****************************************************************************
 * Log de modifica��es:							       *
 * Rev   Data         Descri��o						       *
 * 1.0   31/01/2012 	 Vers�o inicial - Bruno S. Avelar		       *
 ******************************************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.

#include "HardwareProfile.h"

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


/**  P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.
/****************************************************************************/

int main(void)
{
	SystemConfig();
        AllLedsOff();

        while (1)
	{
            	if(BUTTON_1)
		{
                    LED_0_On();
		}
		else
		{
                    LED_0_Off();
		}
		if(BUTTON_2)
		{
                    LED_1_On();
		}
		else
		{
                    LED_1_Off();
		}
		if(BUTTON_3)
		{
                    LED_2_On();
		}
		else
		{
	   		LED_2_Off();
		}
		if(BUTTON_4)
		{
			LED_7_On();
		}
		else
		{
	   		LED_7_Off();
		}
	}

        return 0;
}

void SystemConfig()
{
/* Quando o PIC32 � iniciado ele � configurado para:
* - NO Caching turned on
* - NO Prefetch buffer enabled
* - 7 FLASH wait states 
* - 1 SRAM wait states. 
*
* Todas estas configura��es afetam a perfomasse do microcontrolador
* fazendo que ele funcione significamente mais lento do que o esperado.
* Para configurar corretamente, utilizamos a fun��o 
* SYSTEMConfigPerformance(80000000); passando o valor do clock da CPU como
* parametro. Esta fun��o configurar� as propriedades de performasse como numero
* correto de esperas (wait state) da mem�ria Flash e mem�ria RAM e o uso
* da mem�ria cache.
*/
    SYSTEMConfigPerformance(80000000);
    mOSCSetPBDIV (OSC_PB_DIV_1);

    //Configura os LEDs
    ConfigAllLEDs();
    //Configura os Bot�es
    ConfigAllButtons();
}		
