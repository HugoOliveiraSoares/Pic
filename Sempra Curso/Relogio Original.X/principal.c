#include <p18cxxx.h>
#include "displayLCD.h"


void main()
{
    int seg = 0;
    int min = 0;
    int hor = 0;
    
    ConfiguraLCD();
    TRISEbits.TRISE1 = 1; // configura o botao como entrada digital
    TRISCbits.TRISC0 = 0; // configura o rele como saida digital
    LATCbits.LATC0 = 1; //liga o rele
    
    DesligaCursor();
    
    EscreveFraseRomLCD("SEMPRA");

    while(1)
    {

        seg = seg+1;
        
        if(seg >= 60)
        {
            seg = 0;
            min = min+1;
        }
        if(min >= 60)
        {
            min = 0;
            hor = hor+1;
        }
    
        if(hor == 0 && min == 5 && seg == 32)
        {
            LATCbits.LATC0 = 0;
        }
        //contador += 1;
        //contador++;
        
        PosicaoCursorLCD(2,1);
        if(hor < 10)
        {
            EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(hor);
        EscreveFraseRomLCD(":");
        if(min < 10)
        {
            EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(min);
        EscreveFraseRomLCD(":");
        if(seg < 10)
        {
            EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(seg);
//        Delay10KTCYx(200);
//        Delay10KTCYx(200);
//        Delay10KTCYx(200);
//        Delay10KTCYx(200);
//        Delay10KTCYx(200);
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
