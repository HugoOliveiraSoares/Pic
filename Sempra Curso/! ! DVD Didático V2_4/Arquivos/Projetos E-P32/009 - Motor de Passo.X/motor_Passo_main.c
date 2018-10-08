/******************************************************************************
 *
 *            SEMPRA PROJETOS (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     motor_Passo_main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Opção de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Prática: 			
 * Plataforma:		Placa E-P32
 *
 * Autor:		James Hamilton
 *                      Bruno Avelar
 * Versão:		v1.0
 * Descrição:   	Programa para acionamento de um motor de passo. Quando o
 *                      botão 1 é acionado o motor gira.
 *		
 *****************************************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include "HardwareProfile.h"
#include "Delays.h"

#ifdef NOT_BOOTLOADER
// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 10 MHz
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

    //Desliga todas as boninas do motor de passo
    STP1 = 1;
    STP2 = 1;
    STP3 = 1;
    STP4 = 1;


    while (1)
    {
        //Desliga todas as boninas do motor de passo
        STP1 = 1;
        STP2 = 1;
        STP3 = 1;
	STP4 = 1;

        LED_0_Off();
		
	if(BUTTON_1)
	{
            LED_0_On();

            //Passo na direção da bobina 1
            STP1 = 0;
            STP2 = 1;
            STP3 = 1;
            STP4 = 1;

            DelayMsx(50);//Atrasa a rotação do motor

            //Passo na direção da bobina 2
            STP1 = 1;
            STP2 = 0;
            STP3 = 1;
            STP4 = 1;

            DelayMsx(50);//Atrasa a rotação do motor

            //Passo na direão da bobina 3
            STP1 = 1;
            STP2 = 1;
            STP3 = 0;
            STP4 = 1;
			
            DelayMsx(50);//Atrasa a rotação do motor

            //Passo na direção da bobina 4
            STP1 = 1;
            STP2 = 1;
            STP3 = 1;
            STP4 = 0;

            DelayMsx(50);//Atrasa a rotação do motor
        }//end if
    }//end while
    
    return 0;

}//end main

void SystemConfig()
{
    /* Quando o PIC32 é iniciado ele é configurado para:
     *  - NO Caching turned on
     *  - NO Prefetch buffer enabled
     *  - 7 FLASH wait states
     *  - 1 SRAM wait states.
     * 
     *  Todas estas configurações afetam a perfomasse do microcontrolador
     *  fazendo que ele funcione significamente mais lento do que o esperado.
     *  Para configurar corretamente, utilizamos a função SYSTEMConfigPerformance(80000000);
     *  passando o valor do clock da CPU como parametro. Esta função configurará
     *  as propriedades de performasse como numero correto de esperas (wait state) da
     *  memória Flash e memória RAM e o uso da memória cache.
     */
    SYSTEMConfigPerformance(80000000);
    
    mOSCSetPBDIV (OSC_PB_DIV_1);

    AD1PCFG = 0xffffffff; // Todos os pinos como digital

    ConfigAllLEDs();//Configura LEDs
    ConfigAllButtons();//Configura Botões
    ConfigStepMotor();//Configura Motor
}