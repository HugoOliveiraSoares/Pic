/* 
 * File:   newmain.c
 * Author: Hugo
 * Contador com display 7 segementos
 * Created on 31 de Março de 2017
 */

// INCLUDES
#include <p18cxxx.h>
#include "Display7seg.h"
#include <delays.h>

void main()
{ 
    ConfiguraDisplay();

    while(1)
    { 
        numero(0);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        numero(1);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        numero(2);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        numero(3);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        numero(4);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        numero(5);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        numero(6);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        
        
    } // end while

} // end main

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