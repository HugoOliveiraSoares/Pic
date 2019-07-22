/*
 * File:   Led.c
 * Author: hugo
 * Pisca led
 * 
 * Oscilação de 1Mhz
 * 
 * Created on 14 de Julho de 2019, 09:10
 */

#include <xc.h>
#include <p18cxxx.h>

//#pragma config PLLDIV = 1
//#pragma config CPUDIV = OSC1_PLL2     // Oscilador do sistema / 1 e  96MHz do circuito PLL / 2
//#pragma config FOSC = HS              // Oscilador HS 
#pragma config FOSC = INTOSCIO_EC       // Oscilador interno, EC usado para USB com RA6 como IO

//#define _XTAL_FREQ 20000000   // Cristal de 20Mhz
#define _XTAL_FREQ 1000000      // Definição de clock de 1Mhz

void Delay(int ms);

void main(void) 
{
    ADCON1 = 0x0F;
    OSCCON = 0b01000111;    // Configuração: utilizar o oscilador interno e
                            // usar poscaler  para gerar clock de 1Mhz
    
    TRISAbits.RA5 = 0;
    
    while(1)
    {
        LATAbits.LATA5 = 1;
        Delay(1000);
        LATAbits.LATA5 = 0;
        Delay(1000);
        
    }
}

void Delay(int ms)
{
    ms = ms / 10;
    for(int x = 0; x < ms; x++)
    {
        __delay_ms(10);
    }
}

/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necessária para o compilador XC8 saber onde é o início do vetor de
// "reset".
// Copiar na íntegra esta parte do código dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);
	#pragma code REMAPPED_RESET_VECTOR = 0x1000

/** EOF main.c ***************************************************************/