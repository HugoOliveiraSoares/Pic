
#include <p18cxxx.h>

void main()
{
    TRISAbits.TRISA5 = 0;
    
    TRISAbits.TRISA3 = 1;
    
    ADCON1 = 0XF;

    while(1)
    {
        if(PORTAbits.RA3 == 1)
        {
             LATAbits.LATA5 = 1;
        }
        else
        {
             LATAbits.LATA5 = 0;
        }
    }
    
}


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
