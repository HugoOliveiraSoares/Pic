/******************************************************************************
 *
 *            SEMPRA PROJETOS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     Mostradisplay7seg_main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F256L
 * Op��o de Clock:	HS 10MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Pr�tica: 			
 * Plataforma:          KIT E-P32
 *
 * Autor:		Bruno Avelar
 * Vers�o:		v1.0
 * Descri��o:   	O firmware � a implementa��o de um contador de cliques.
 *			O display multiplexado foi utilizado para mostrar o n�mero
 *			atual da contagem. Quando o usu�rio pressiona o bot�o 1 do
 *                      placa de desenvolvimento E-P32 o contador � incrementado de 1.
 *			Quando o usuario pressiona o botao 2 o contador despara a contagem
 *			at� que o usuario solta o botao 2. O mesmo � feito para os botoes 3 e 4
 *			sendo que estes fazem contagem regressiva.
 *			Caso o contador ultrapasse 9999 ele retornar� a 0 e caso ultrapasse 0 ele
 *			ser� levado a 9999.
 *****************************************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.

#include "HardwareProfile.h"
#include "display_7seg.h"
#include "Delays.h"
 
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
	int cont = 0;
	
	
	SystemConfig();
	EscreveDisplay7Seg(0,0);
	
	while (1)
	{
		if(BUTTON_1|BUTTON_2)
		{
			DelayMsx(1);			
			cont++;
			if(cont > 9999)
			{
				cont = 0;
			}	
			EscreveDisplay7Seg(cont,0);
			while(BUTTON_1)
			{
				DelayMsx(1);
				UpdateDisplay7Seg();
			}
		}
		if(BUTTON_3|BUTTON_4)
		{
			DelayMsx(1);
			cont--;
			if(cont < 0)
			{
				cont = 10000;
			}
			else
			{	
				EscreveDisplay7Seg(cont,0);	
				while(BUTTON_4)
				{
					DelayMsx(1);
					UpdateDisplay7Seg();
				}
			}
		}	
		DelayMsx(1);
		UpdateDisplay7Seg();
	}
	
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
	* Para configurar corretamente, utilizamos a fun��o SYSTEMConfigPerformance(80000000);
	* passando o valor do clock da CPU como parametro. Esta fun��o configurar�
	* as propriedades de performasse como numero correto de esperas (wait state) da
	* mem�ria Flash e mem�ria RAM e o uso da mem�ria cache.
	*/
	SYSTEMConfigPerformance(80000000);
   /*
    *
    */
	mOSCSetPBDIV (OSC_PB_DIV_1);	


	// Desabilita a porta de JTAG
    DDPCONbits.JTAGEN = 0;

	ConfigAllButtons();
    
    // Configura o display de 7 segmentos multiplexado
    ConfigDisplay7Seg();	    
    
}		
