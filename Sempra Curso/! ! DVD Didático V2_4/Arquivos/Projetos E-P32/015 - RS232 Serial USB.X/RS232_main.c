/******************************************************************************
 *
 *            PICMINAS PROJETOS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     RS232_main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F256L
 * Opção de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Prática: 			
 * Plataforma:		Placa PICMINAS32
 *
 * Autor:		Bruno Avelar
 *			James Hamilton
 * Versão:		v1.0
 * Descrição:   	Programa exemplo para RS232
 *****************************************************************************/

#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.

#include "HardwareProfile.h"
#include "displayLCD.h"
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

#pragma config UPLLEN = ON
#pragma config UPLLIDIV = DIV_2

#pragma config CP         = OFF    // Code Protect
#pragma config BWP        = OFF    // Boot Flash Write Protect
#pragma config PWP        = OFF    // Program Flash Write Protect

#endif


/**  P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.
void DelayMsx(unsigned int ms);
/****************************************************************************/

char intStatus = 0;

int main(void)
{
    SystemConfig();

    AllLedsOff();

    //Configuração Da UART4
    PosicaoCursorLCD(1,1);
    EscreveFraseConstLCD("Dado recebido: ");
    
    while (1)
    {
        if(BUTTON_1)
        {
            U4TXREG = 't';//Escreve "t" no Registrador de Transmissão
            DelayMsx(300);
        }
        PosicaoCursorLCD(1,1);
        //EscreveInteiroLCD(U4RXREG);
        EscreveCaractereLCD(U4RXREG);//Escreve no LCD o caractere que está no
                                     //Registrador de Recepção
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
    
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    DDPCONbits.JTAGEN = 0;
    DDPCONbits.TROEN  = 0;
    DDPCONbits.TDOEN  = 0;
    
    ConfiguraLCD();

    //Desabilita as interrupcoes
    intStatus = INTDisableInterrupts();

    U4MODEbits.SIDL = 0; // Continue operation in Idle mode
    U4MODEbits.IREN = 0; // 0 = IrDA is disabled
    //U4MODEbits.RTSMD = 1; //1 = UxRTS pin is in Simplex mode
    U4MODECLR = 0b1100000000; // UxTX and UxRX pins are enabled and used; UxCTS
                              //and UxRTS/UxBCLK pins are controlled by
                              //corresponding bits in the PORTx register
    U4MODEbits.WAKE = 0; //0 = Wake-up disabled
    U4MODEbits.LPBACK = 0; //0 = Loopback mode is disabled
    U4MODEbits.ABAUD = 0; // Baud rate measurement disabled or completed
    U4MODEbits.RXINV = 0; // 0 = UxRX Idle state is ‘1’
    U4MODEbits.BRGH = 0;//0 = Standard Speed mode – 16x baud clock enabled
    U4MODECLR = 0b0000000110; // 00 = 8-bit data, no parity
    U4MODEbits.STSEL = 0;

    U4STAbits.ADM_EN = 0;
    U4STACLR = 0b0100000000000000;
    U4STASET = 0b1000000000000000;
    U4STAbits.UTXINV = 0; //0 = UxTX Idle state is ‘1’
    U4STAbits.URXEN = 1; // 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1)
    U4STAbits.UTXBRK = 0; //0 = Break transmission is disabled or completed
    U4STAbits.UTXEN = 1;
    U4STACLR = 0b0000000011000000; //Interrupt flag bit is set when a character is received
    U4STAbits.ADDEN = 0; //0 = Address Detect mode is disabled
    U4BRG = 2082;

    U4MODEbits.ON  = 1; //Liga o módulo UART
    //Configura os LEDs
    ConfigAllLEDs();

}		
