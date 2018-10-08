/******************************************************************************
 *
 *            SEMPRA PROJETOS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     pwm_main.c
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
 * Descrição:   		
 *****************************************************************************/

//#define NOT_BOOTLOADER

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
    int i = 326;
	
    SystemConfig();

    while (1)
    {
        if (BUTTON_1)
        {
            DelayMsx(10); //Atraso de 10ms
            i++;//Incrementa o valor do ciclo de trabalho(duty cicle) do PWM
            SetDCOC3PWM(i);//Redefine o duty cicle do PWM pelo incrementado
            if (i == 650)
            {
                i = 0;
            }//end if
        }//end if
	if (BUTTON_4)
	{
            DelayMsx(10);//Atraso de 10ms
            i--;//Decrementa o valor do ciclo de trabalho(duty cicle) do PWM
            SetDCOC3PWM(i);//Redefine o duty cicle do PWM pelo decrementado
            if (i == 1)
            {
                i = 650;
            }//end if
        }//end if
      
        while (BUTTON_1 && BUTTON_4)
        {
            DelayMsx(5);//Atraso de 5ms
            i++;//Incrementa o valor do ciclo de trabalho(duty cicle) do PWM
            SetDCOC3PWM(i);//Redefine o duty cicle do PWM pelo incrementado
            if (i == 650)
            {
                i = 0;
            }//end if
        }//end while
    }//end while

    return 0;
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
    
    AD1PCFG = 0xffffffff; // Todos os pinos como digital


    ConfigAllButtons();

    TRISDbits.TRISD2 = 0; // LED PWM

    //Configuração do timer
    // Tempo = 1/PBCK x Preescaler x PRx
    // Onde:
    // PBCK - Frequencia do barramento de periférico
    // Preescaler - Divisão do clock (1:1, 1:2, 1:4, 1:8, 1:16, 1:32, 1:64, 1:256)
    // PRx - Periodo do timer.
    OpenTimer3(T3_ON |		//Módulo do Timer3 habilitado
            T3_PS_1_256,	//Preescaler de 1:256
            652);		//Período do timer 652, Tempo = 2ms

    
    OpenOC3(OC_ON |                 //Habilita Módulo OC(output compare)
            OC_TIMER_MODE16 |        //Modo 16 bits
            OC_TIMER3_SRC |          //Seleciona o Timer3 como clock
            OC_PWM_FAULT_PIN_DISABLE,//PWM no OC3, pino de falha desabilitado
            326,                     //Valor para comparação secundário
            326);                    //Valor para comparação primário
	SetDCOC3PWM(250);


}