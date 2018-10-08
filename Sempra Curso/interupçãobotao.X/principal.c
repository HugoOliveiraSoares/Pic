#include <p18cxxx.h>



void main()
{
    TRISCbits.TRISC2 = 0;
    
    TRISEbits.TRISE2 = 1;
    
    ADCON1 = 0x0f;

    while(1)
    {
        if(PORTEbits.RE2 == 1)
        {
             LATCbits.LATC2 = 1;
        }
        else
        {
             LATCbits.LATC2 = 0;
        }
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
