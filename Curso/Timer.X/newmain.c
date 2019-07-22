/*
 * File:   newmain.c
 * Author: hugo
 *
 * Created on 15 de Julho de 2019, 17:34
 */


#include <xc.h>
#include <p18cxxx.h>

#pragma config FOSC = HS    // Oscilador externo
#pragma config WDT = OFF    // Watchdog Timer desligado
#pragma config MCLRE = OFF  // Master Clear desabilitado


#define _XTAL_FREQ 4000000          // Definição de clock de 4Mhz

void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

void main(void)
{
    INTCONbits.GIE = 1;     // Habilita interrupção global
    INTCONbits.TMR0IE = 1;  // Interrupção do timer 0
    ///INTCONbits.TMR0IF = 0;	// Limpa a sinalizao da interrupcao, 
                                //para garantir que nao entre na interrupcao por sujeira na memoria.
    
    T08BIT = 0;     // Modo 16 bits
    T0CS = 0;       // Source do clock 
    PSA = 1;        // Desabilita Prescaler
    TMR0H = 0x3C;   // Começa a contar de 15535
    TMR0L = 0xAF;   // até 65535 (conta 50 mil vezes)
    TMR0ON = 1;     // Liga o timer
    
    TRISAbits.RA5 = 0;    
}

#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if(INTCONbits.TMR0IF)
	{
        LATAbits.LA5 = !LATAbits.LA5;
        TMR0H = 0x3C;           // Começa a contar de 15535
        TMR0L = 0xAF;           // até 65535 (conta 50 mil vezes)
        INTCONbits.TMR0IF = 0;	// Limpa a sinalizao da interrupcao
	}
}

#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	
}



/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necessária para o compilador XC8 saber onde é o início do vetor de
// "reset".
// Copiar na íntegra esta parte do código dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
    #pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
    #pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018

/** EOF main.c ***************************************************************/
