/*******************************************************************************
 *                  SEMPRA  E-P32 Acende LED    			       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     AcendeLed_main.c                                       *
 * Dependencias:    	Veja a seção INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Opção de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.0                                                   *
 * Descrição:        	Este programa introdutório utiliza portas digitais     *
 *                      do PIC32MX para ligar e desligar os LEDs da placa      *
 *                      E-P32.                                                 *
 *                                                                             *
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   31/01/2012 	 Versão inicial - Bruno S. Avelar		       *
 ******************************************************************************/

#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.

#include "HardwareProfile.h"
#include "Delays.h"

#ifdef NOT_BOOTLOADER
// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto
// Configuration Bit settings

// Clock da CPU:
// SYSCLK = 80 MHz (8MHz Cristal * FPLLIDIV * FPLLMUL * FPLLODIV)
// SYSCLK = 80 MHz (8MHz * 1/2 * 20 * 1/1)

// Clock do barramento de periféricos:
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
    
	LED_0_Off();
	LED_1_Off();
	LED_2_Off();
	LED_3_Off();
	LED_4_Off();
	LED_5_Off();
	LED_6_Off();
	LED_7_Off();

	while (1)
	{
		LED_0_Toggle();
		DelayMsx(100);
		LED_1_Toggle();
		DelayMsx(100);
		LED_2_Toggle();
		DelayMsx(100);
		LED_3_Toggle();
		DelayMsx(100);
		LED_4_Toggle();
		DelayMsx(100);
		LED_5_Toggle();
		DelayMsx(100);
		LED_6_Toggle();
		DelayMsx(100);
		LED_7_Toggle();
		DelayMsx(100);
	}

        return 0;
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
* Para configurar corretamente, utilizamos a função 
* SYSTEMConfigPerformance(80000000); passando o valor do clock da CPU como
* parametro. Esta função configurará as propriedades de performasse como numero
* correto de esperas (wait state) da memória Flash e memória RAM e o uso
* da memória cache.
*/
    SYSTEMConfigPerformance(80000000);
    mOSCSetPBDIV (OSC_PB_DIV_1);

    //Configura os LEDs
    ConfigAllLEDs();
}		
