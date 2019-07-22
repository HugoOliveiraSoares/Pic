#include "TimeDelay.h" 

void Delay10us( unsigned long tenMicroSecondCounter )
{
    volatile unsigned long cyclesRequiredForEntireDelay;
        
    if (GetInstructionClock() <= 2500000) //Para todos FCY menor que 2 MHz (FOSC <= 10MHz)
    {
        //26 ciclos foram gastos at� este ponto (incluindo retornar a fun��o que chamou.
        //Para FOSC == 1MHZ, leva 104us.
        //Para FOSC == 4MHZ, leva 26us
        //Para FOSC == 8MHZ, leva 13us.
        //Para FOSC == 10MHZ, leva 10.5us.
    }
    else
    {
        //14 ciclos foram gastos at� este ponto.
        //Calcula o numero de instru��es que deve ser o atraso
        cyclesRequiredForEntireDelay = (long)(GetInstructionClock()/100000) * tenMicroSecondCounter;

        //Subitraimos todos os ciclos usados at� chegar no loop abaixo
        //Tamb�m subtraimos 22 ciclos do return da fun��o
        cyclesRequiredForEntireDelay -= (153 + 22);

        if (cyclesRequiredForEntireDelay <= 45)
        {
            // Se ja estiver ecedido o numero de ciclos retornamos
        }
        else
        {
            while (cyclesRequiredForEntireDelay>0) //153 ciclos usados at� este ponto.
            {
                Nop(); //Delay 1 instru��o
                cyclesRequiredForEntireDelay -= 42; //Subtrai ciclos gastos no while a cada intera��o, 42 neste caso.
            }
        }
    }        
}

void DelayMs( unsigned short int ms )
{
        long cyclesRequiredForEntireDelay;

        //Calcula o numero de instru��es que deve ser o atraso
        cyclesRequiredForEntireDelay = (signed long)(GetInstructionClock()/1000) * ms;
        
        //Subitraimos todos os ciclos usados at� chegar no loop abaixo
        //Tamb�m subtraimos 22 ciclos do return da fun��o
        cyclesRequiredForEntireDelay -= (148 + 22);

        if (cyclesRequiredForEntireDelay <= (170+25)) 
        {
            return;    // Se ja estiver ecedido o numero de ciclos retornamos
        }    
        else
        {
            while (cyclesRequiredForEntireDelay > 0) //148 ciclos foram usados at� este ponto
            {
                Nop();                              // Delay 
                cyclesRequiredForEntireDelay -= 39;//Subtrai ciclos gastos no while a cada intera��o, 39 neste.
            }
        }       
}

