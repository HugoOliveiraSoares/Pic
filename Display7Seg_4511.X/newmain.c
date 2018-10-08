/* 
 * File:   newmain.c
 * Author: Hugo
 * Uso do Display de 7 segmentos com o circuito integrado 4511
 * Created on 18 de Março de 2017, 21:28
 */

// INCLUDES
#include <p18cxxx.h>
#include "TimeDelay.h"

// DEFINES
#define Led_A  LATDbits.LATD0
#define Led_B  LATDbits.LATD1
#define Led_C  LATDbits.LATD2
#define Led_D  LATDbits.LATD3

// FUNÇÕES ADICIONAS
void Configura_Sistema(void);
void num0(void);
void num1(void);
void num2(void);
void num3(void);
void num4(void);
void num5(void);
void num6(void);
void num7(void);
void num8(void);
void num9(void);

void main()
{   
    Configura_Sistema();
    
    while(1)
    {   
        num0();
        DelayMs(1000);
        num1();
        DelayMs(1000);
        num2();
        DelayMs(1000);
        num3();
        DelayMs(1000);
        num4();
        DelayMs(1000);
        num5();
        DelayMs(1000);
        num6();
        DelayMs(1000);
        num7();
        DelayMs(1000);
        num8();
        DelayMs(1000);
        num9();
        DelayMs(1000);
        
    } //end while
    
    
} // end main


void num0()
{
        Led_A = 0;
        Led_B = 0;
        Led_C = 0;
        Led_D = 0;
} // end num0

void num1()
{
        Led_A = 1;
        Led_B = 0;
        Led_C = 0;
        Led_D = 0;
} // end num1

void num2()
{
        Led_A = 0;
        Led_B = 1;
        Led_C = 0;
        Led_D = 0;
} // end num2

void num3()
{
        Led_A = 1;
        Led_B = 1;
        Led_C = 0;
        Led_D = 0;
} // end num3

void num4()
{
        Led_A = 0;
        Led_B = 0;
        Led_C = 1;
        Led_D = 0;
} // end num4

void num5()
{
        Led_A = 1;
        Led_B = 0;
        Led_C = 1;
        Led_D = 0;
} // end num5

void num6()
{
        Led_A = 0;
        Led_B = 1;
        Led_C = 1;
        Led_D = 0;
} // end num6

void num7()
{
        Led_A = 1;
        Led_B = 1;
        Led_C = 1;
        Led_D = 0;
} // end num7

void num8()
{
        Led_A = 0;
        Led_B = 0;
        Led_C = 0;
        Led_D = 1;
} // end num8

void num9()
{
        Led_A = 1;
        Led_B = 0;
        Led_C = 0;
        Led_D = 1;
} // end num9

void Configura_Sistema()
{
    ADCON1 = 0x0F;          // Configura todas as portas como digitais
    TRISDbits.TRISD0 = 0;   //A
    TRISDbits.TRISD1 = 0;   //B
    TRISDbits.TRISD2 = 0;   //C
    TRISDbits.TRISD3 = 0;   //D
    
} // end Configura_Sistema

/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necessária para o compilador C18 saber onde é o início do vetor de
// "reset".
// Copiar na íntegra esta parte do código dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
/** EOF main.c ***************************************************************/