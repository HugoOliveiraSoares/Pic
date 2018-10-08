
#include <p18cxxx.h>
#include <delays.h>

#define Led_A  LATBbits.LATB0
#define Led_B  LATBbits.LATB1
#define Led_C  LATBbits.LATB2
#define Led_D  LATBbits.LATB3
#define Led_E  LATBbits.LATB4
#define Led_F  LATBbits.LATB5
#define Led_G  LATBbits.LATB6

int num;

void ConfiguraDisplay(void);

void ConfiguraDisplay(void)
{
	ADCON1 |= 0x0F;
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISAbits.TRISA3 = 0;
}

void main()
{ 
    num = 0;
    ConfiguraDisplay();
    while(1)
    {
        if(PORTAbits.RA3==0)
        {
            Delay10KTCYx(200);
            Led_A = 0;
            Led_B = 1;
            Led_C = 1;
            Led_D = 0;
            Led_E = 0;
            Led_F = 0;
            Led_G = 0;
        }else
        {
            Led_A = 0;
            Led_B = 0;
            Led_C = 0;
            Led_D = 0;
            Led_E = 0;
            Led_F = 0;
            Led_G = 0;
          
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