#include <p18cxxx.h>
#include "displayLCD.h"


void main()
{
    int seg = 0;
    int min = 0;
    int hor = 0;
    
    int seg_set = 0;
    int min_set = 0;
    int hor_set = 0;
    
    char escolhaHora = 0;
    char escolhaMin = 0;
    char escolhaSeg = 0;

    
    ConfiguraLCD();
    TRISEbits.TRISE1 = 1; // configura o botao como entrada digital
    TRISEbits.TRISE2 = 1; // configura o botao como entrada digital
    TRISCbits.TRISC0 = 0; // configura o rele como saida digital
    LATCbits.LATC0 = 0; //desliga o rele
    
    DesligaCursor();    
    
    //Escolha do horario de funcionamento da máquina
    
    EscreveFraseRomLCD("Escolha tempo:");
    
    while(escolhaHora == 0)
    {
        PosicaoCursorLCD(2,1);
        if(hor_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(hor_set);
        if(PORTEbits.RE1 == 1)
        {
            hor_set++;
            while(PORTEbits.RE1 == 1)
            {
                
            }
        }
        if(PORTEbits.RE2 == 1)
        {
            if(hor_set > 0)
            {
                hor_set--;
            }
            while(PORTEbits.RE2 == 1)
            {
                
            }
        }
        if(PORTBbits.RB4 == 0)
        {
            escolhaHora = 1;
            while(PORTBbits.RB4 == 0)
            {
                
            }
        }  
    }
    EscreveFraseRomLCD(":");
    while(escolhaMin == 0)
    {
        PosicaoCursorLCD(2,1);
        
        if(hor_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(hor_set);
        EscreveFraseRomLCD(":");
        if(min_set < 10)
        {
            EscreveInteiroLCD(0); 
        }
        EscreveInteiroLCD(min_set);
        
        if(PORTEbits.RE1 == 1)
        {
            if(min_set <59)
            {
                min_set++;
            }
            while(PORTEbits.RE1 == 1)
            {
                
            }
        }
        if(PORTEbits.RE2 == 1)
        {
            if(min_set > 0)
            {
                min_set--;
            }
            
            while(PORTEbits.RE2 == 1)
            {
                
            }
        }
        if(PORTBbits.RB4 == 0)
        {
            escolhaMin = 1;
            while(PORTBbits.RB4 == 0)
            {
                
            }
        }  
    }
    EscreveFraseRomLCD(":");
    while(escolhaSeg == 0)
    {
        PosicaoCursorLCD(2,1);
        
        if(hor_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(hor_set);
        EscreveFraseRomLCD(":");        
        if(min_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(min_set);
        EscreveFraseRomLCD(":");
        
        
        if(seg_set < 10)
        {
            EscreveInteiroLCD(0); 
        }
        EscreveInteiroLCD(seg_set);
        
        if(PORTEbits.RE1 == 1)
        {
            if(seg_set <59)
            {
                seg_set++;
            }
            while(PORTEbits.RE1 == 1)
            {
                
            }
        }
        if(PORTEbits.RE2 == 1)
        {
            if(seg_set > 0)
            {
                seg_set--;
            }
            
            while(PORTEbits.RE2 == 1)
            {
                
            }
        }
        if(PORTBbits.RB4 == 0)
        {
            escolhaSeg = 1;
            while(PORTBbits.RB4 == 0)
            {
                
            }
        }  
    }
    LimpaDisplay();
    EscreveFraseRomLCD("Configurado");
    PosicaoCursorLCD(2,1);
    EscreveFraseRomLCD("Iniciando  ");
    
    Delay10KTCYx(0);
    Delay10KTCYx(0);
    Delay10KTCYx(0);
    Delay10KTCYx(0);
    Delay10KTCYx(0);
    
    while(1)
    {
        PosicaoCursorLCD(1,1);
        EscreveFraseRomLCD("Set:");
        if(hor_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(hor_set);
        EscreveFraseRomLCD(":");        
        if(min_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(min_set);
        EscreveFraseRomLCD(":");
        if(seg_set < 10)
        {
             EscreveInteiroLCD(0);
        }
        EscreveInteiroLCD(seg_set);
        
        
//Contagem do tempo
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
    
        if(hor == hor_set && min == min_set && seg == seg_set)
        {
            LATCbits.LATC0 = 1;
        }
        if(hor == hor_set && min == (min_set + 0) && seg == (seg_set + 5))
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
        EscreveFraseRomLCD("    ");
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        Delay10KTCYx(200);
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
