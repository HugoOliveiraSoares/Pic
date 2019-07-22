/*
 * File:   Botao.c
 * Author: hugo
 * 
 * Created on 14 de Julho de 2019, 14:34
 */


#include <xc.h>
#include<p18cxxx.h>

#pragma config FOSC = INTOSCIO_EC   // Oscilador interno, EC usado para USB com RA6 como IO

#define LED_1 LATAbits.LATA5    // LED AZUL (PLACA
#define LED_2 LATDbits.LATD0    // LED (PORTOBOARD)

#define BOTAO1 PORTAbits.RA3    // BOTAO NO RA3 (PLACA)
#define BOTAO2 PORTBbits.RB0    // BOTAO NO RB0 (PORTOBOARD)

void main(void) 
{
    ADCON1 = 0XF;
    
    TRISDbits.RD0 = 0; // LED_2
    TRISAbits.RA5 = 0; // LED_1
  
    
    while(1)
    {
        if(BOTAO1 == 0) // Botao com resistor de pull up, logica inversa
        {
            LED_1 = 1;
        }else
        {
            LED_1 = 0;
        }
        
        if(BOTAO2 == 1)
        {
            LED_2 = 1;
        }else
        {
            LED_2 = 0;
        }
                
        //LED_1 = !BOTAO1;  // Botao com resistor de pull up, logica inversa
        //LED_2 = BOTAO2;   // Atribui o estado da porta do botao a porta do led
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