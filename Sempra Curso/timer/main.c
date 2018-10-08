
#include <p18cxxx.h>
#include <timers.h>
#include <delays.h>

void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

void main(void)
{
    ADCON1  |=  0x0F;

    TRISAbits.TRISA4 = 0;
    
    
    //Configuração Global das Interrupções
    RCONbits.IPEN = 1; // Habilita prioridades de interrupcao
    INTCONbits.GIEH = 0; // Desabilita vetor de alta prioridade
    INTCONbits.GIEL = 0; // Desabilita vetor de baixa prioridade

    //Configurações da Interrupção do Timer0
    INTCONbits.TMR0IE = 1;	// Habilita interrupcao de Timer0
    INTCONbits.TMR0IF = 0;	// Limpa a sinalizaÁ?o da interrupcao,
							//para garantir que nao entra na interrupcao por sujeira na memoria							
    INTCON2bits.TMR0IP = 1; // Tratamento de interrupcao no vetor de Alta prioridade

    OpenTimer0(TIMER_INT_ON  &	// Habilita Interrupção do Timer0
                   T0_16BIT	 &	// Contagem do Timer0 com 16bits
                   T0_SOURCE_INT &	// Fonte de clock interno
                   T0_PS_1_64);     // Prescaler 1:64

    WriteTimer0(9500);

    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    while(1)	
   {		
		
   }//end while(1)
}//end main

#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if(INTCONbits.TMR0IF)
	{
            WriteTimer0(9500);
            LATAbits.LATA4 = !LATAbits.LATA4;
            INTCONbits.TMR0IF = 0; 
	}
}

#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	
}

extern void _startup (void);        
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}
#pragma code
