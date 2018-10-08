#include "TimeDelay.h" 

void Delay10us( unsigned long tenMicroSecondCounter )
{
    volatile unsigned long cyclesRequiredForEntireDelay;
        
    if (GetInstructionClock() <= 2500000) //Para todos FCY menor que 2 MHz (FOSC <= 10MHz)
    {
        //26 ciclos foram gastos até este ponto (incluindo retornar a função que chamou.
        //Para FOSC == 1MHZ, leva 104us.
        //Para FOSC == 4MHZ, leva 26us
        //Para FOSC == 8MHZ, leva 13us.
        //Para FOSC == 10MHZ, leva 10.5us.
    }
    else
    {
        //14 ciclos foram gastos até este ponto.
        //Calcula o numero de instruções que deve ser o atraso
        cyclesRequiredForEntireDelay = (long)(GetInstructionClock()/100000) * tenMicroSecondCounter;

        //Subitraimos todos os ciclos usados até chegar no loop abaixo
        //Também subtraimos 22 ciclos do return da função
        cyclesRequiredForEntireDelay -= (153 + 22);

        if (cyclesRequiredForEntireDelay <= 45)
        {
            // Se ja estiver ecedido o numero de ciclos retornamos
        }
        else
        {
            while (cyclesRequiredForEntireDelay>0) //153 ciclos usados até este ponto.
            {
                Nop(); //Delay 1 instrução
                cyclesRequiredForEntireDelay -= 42; //Subtrai ciclos gastos no while a cada interação, 42 neste caso.
            }
        }
    }        
}

void DelayMs( unsigned short int ms )
{
        long cyclesRequiredForEntireDelay;

        //Calcula o numero de instruções que deve ser o atraso
        cyclesRequiredForEntireDelay = (signed long)(GetInstructionClock()/1000) * ms;
        
        //Subitraimos todos os ciclos usados até chegar no loop abaixo
        //Também subtraimos 22 ciclos do return da função
        cyclesRequiredForEntireDelay -= (148 + 22);

        if (cyclesRequiredForEntireDelay <= (170+25)) 
        {
            return;    // Se ja estiver ecedido o numero de ciclos retornamos
        }    
        else
        {
            while (cyclesRequiredForEntireDelay > 0) //148 ciclos foram usados até este ponto
            {
                Nop();                              // Delay 
                cyclesRequiredForEntireDelay -= 39;//Subtrai ciclos gastos no while a cada interação, 39 neste.
            }
        }       
}

