#include <p18cxxx.h>
#include <delays.h>

void main()
{
    TRISDbits.TRISD0 = 0;   //A
    TRISDbits.TRISD1 = 0;   //B
    TRISDbits.TRISD2 = 0;   //C
    TRISDbits.TRISD3 = 0;   //D
    TRISDbits.TRISD4 = 0;   //E
    TRISDbits.TRISD5 = 0;   //F
    TRISDbits.TRISD6 = 0;   //G 
    
    ADCON1 = 0x0f;
   

    while(1)
    {
             LATDbits.LATD0 = 0;
             LATDbits.LATD1 = 0;
             LATDbits.LATD2 = 0;
             LATDbits.LATD3 = 0;
             LATDbits.LATD4 = 0;
             LATDbits.LATD5 = 0;
             LATDbits.LATD6 = 0;
             Delay10KTCYx(100);
             Delay10KTCYx(100);
             Delay10KTCYx(100);
             Delay10KTCYx(100);
             Delay10KTCYx(100);
             LATDbits.LATD0 = 1;
             LATDbits.LATD1 = 1;
             LATDbits.LATD2 = 1;
             LATDbits.LATD3 = 1;
             LATDbits.LATD4 = 1;
             LATDbits.LATD5 = 1;
             LATDbits.LATD6 = 1;
             Delay10KTCYx(200);
             Delay10KTCYx(200);
             Delay10KTCYx(200);
             
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

