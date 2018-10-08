/******************************************************************************
 *
 *            PICMINAS PROJETOS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F256L
 * Opção de Clock:		HS 10MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	PICMinas
 * Prática: 			
 * Plataforma:			Placa PICMINAS32
 *
 * Autor:				Bruno Avelar
 * Versão:				v1.0
 * Descrição:   		Botão Relé.
 *						Pressiona o BOTAO1 o relé sera armado, pressionando o botao4
 *						o relé será desarmado.
 *						Este programa é uma atualização do hardware profile.
 *****************************************************************************/

#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.

#include "HardwareProfile.h"

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
	
	while (1)
	{
		if(BUTTON_2 || BUTTON_3)
		{
			Rele_On();
		}
		if(BUTTON_1)
		{
			Rele_Off();
		}	
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


	// Desabilita a porta de JTAG
    DDPCONbits.JTAGEN = 0;

	ConfigAllButtons();
	ConfigRele(); 
	
		AD1PCFG = 0xffffffff; // Todos os pinos como digital   
}		
