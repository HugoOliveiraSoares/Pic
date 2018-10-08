/******************************************************************************
 *
 *            SEMPRA PROJETOS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     Display7seg_main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Opção de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Prática: 			
 * Plataforma:		Placa E-P32
 *
 * Autor:		Bruno Avelar
 * Versão:		v1.0
 * Descrição:           Faz contagem de 0000 a 9999 no display de 7 segmentos
 *			multiplexado da placa de desenvolvimento PICMinas32 com
 *			o intervalo de 0,5 segundos (500ms).
 *****************************************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.

#include "HardwareProfile.h"
#include "display_7seg.h"
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
    long i,j; //Declaração de Variáveis
	
    SystemConfig(); //Configura o sistema
	
    while (1)
    {
        for(i=0;i<10000;i++) //Itera o valor de i de 0 a 9999
        {
            EscreveDisplay7Seg(i,0); //Escreve o valor de i no display

            for (j= 0 ; j<600;j++) //Atraso na contagem de i
            {
                UpdateDisplay7Seg(); //Atualiza o valor do display multiplexado
                DelayMsx(1); //Cria atraso de 1ms na execução do programa
            }//end for
        }//end for
    }//end while
}//end main

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

    //Configura o Display de 7 Segmentos
    AD1PCFG = 0xffffffff; // Todos os pinos como digital

    ConfigDisplay7Seg();
}	