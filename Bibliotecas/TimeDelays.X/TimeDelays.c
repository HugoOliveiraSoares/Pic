/* 
 * File:   TimeDelays.c
 * Author: Hugo
 *
 * Created on 11 de Mar�o de 2017, 16:05
 */

#include <p18cxxx.h>
#include "TimeDelay.h"

void main()
{
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA4 = 0;
    
    while(1)
    {
        LATAbits.LATA5 = 1;
        LATAbits.LATA4 = 0;
        DelayMs(5000);
        LATAbits.LATA5 = 0;
        LATAbits.LATA4 = 1;
        DelayMs(5000);
    }
    
}

/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necess�ria para o compilador C18 saber onde � o in�cio do vetor de
// "reset".
// Copiar na �ntegra esta parte do c�digo dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
/** EOF main.c ***************************************************************/

