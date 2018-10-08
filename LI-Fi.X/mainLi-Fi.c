/* 
 * File:   mainLi-Fi.c
 * Author: Hugo
 *
 * Created on 29 de Abril de 2017, 12:34
 */

#include <p18cxxx.h>
#include "TimeDelay.h"

#define Led_1  LATBbits.LATB0 
#define Led_2  LATBbits.LATB1
#define Led_3  LATBbits.LATB2
#define Led_4  LATBbits.LATB3
#define Led_5  LATBbits.LATB4
#define Led_6  LATBbits.LATB5
#define Led_7  LATBbits.LATB6
#define Led_8  LATBbits.LATB7
#define Receptor LATDbits.LATD0

void configura_sistema(void);


void main()
{
    int byt = 0;
    configura_sistema(void);
    
    while(1)
    {
        
    } // end while
    
} // end void main

void configura_sistema()
{
    TRISDbits.TRISD0 = 1;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
}

/** V E C T O R   R E M A P P I N G ******************************************/
// Seção necessária para informar ao compilador C18 onde são os novos endereços
//da memória de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupção.
// ATENÇÃO: Copiar esta parte do código dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para gravação in-circuit.
// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal 
// no endereço 0x1000 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}