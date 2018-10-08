/******************************************************************************
 *
 *            SEMPRA PROJETOS (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     motor_Passo_main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Op��o de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Pr�tica: 			
 * Plataforma:		Placa E-P32
 *
 * Autor:		James Hamilton
 *                      Bruno Avelar
 * Vers�o:		v1.0
 * Descri��o:   	Programa para acionamento de um motor de passo. Quando o
 *                      bot�o 1 � acionado o motor gira.
 *		
 *****************************************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.
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

            //Passo na dire��o da bobina 1
            STP1 = 0;
            STP2 = 1;
            STP3 = 1;
            STP4 = 1;

            DelayMsx(50);//Atrasa a rota��o do motor

            //Passo na dire��o da bobina 2
            STP1 = 1;
            STP2 = 0;
            STP3 = 1;
            STP4 = 1;

            DelayMsx(50);//Atrasa a rota��o do motor

            //Passo na dire�o da bobina 3
            STP1 = 1;
            STP2 = 1;
            STP3 = 0;
            STP4 = 1;
			
            DelayMsx(50);//Atrasa a rota��o do motor

            //Passo na dire��o da bobina 4
            STP1 = 1;
            STP2 = 1;
            STP3 = 1;
            STP4 = 0;

            DelayMsx(50);//Atrasa a rota��o do motor
        }//end if
    }//end while
    
    return 0;

}//end main

void SystemConfig()
{
    /* Quando o PIC32 � iniciado ele � configurado para:
     *  - NO Caching turned on
     *  - NO Prefetch buffer enabled
     *  - 7 FLASH wait states
     *  - 1 SRAM wait states.
     * 
     *  Todas estas configura��es afetam a perfomasse do microcontrolador
     *  fazendo que ele funcione significamente mais lento do que o esperado.
     *  Para configurar corretamente, utilizamos a fun��o SYSTEMConfigPerformance(80000000);
     *  passando o valor do clock da CPU como parametro. Esta fun��o configurar�
     *  as propriedades de performasse como numero correto de esperas (wait state) da
     *  mem�ria Flash e mem�ria RAM e o uso da mem�ria cache.
     */
    SYSTEMConfigPerformance(80000000);
    
    mOSCSetPBDIV (OSC_PB_DIV_1);

    AD1PCFG = 0xffffffff; // Todos os pinos como digital

    ConfigAllLEDs();//Configura LEDs
    ConfigAllButtons();//Configura Bot�es
    ConfigStepMotor();//Configura Motor
}