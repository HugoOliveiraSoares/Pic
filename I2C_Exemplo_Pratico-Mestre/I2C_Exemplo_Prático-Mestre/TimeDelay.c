#include "TimeDelay.h" 

void Delay10us( unsigned long uS )
{
    // Variavel que armazena o numero de ciclos necessarios para o delay inteiro
    long CiclosNecessarios;

    // 14 ciclos foram gastos até este ponto.
    // Calcula o numero de instruções que deve ser o atraso
    CiclosNecessarios = (signed long)(GetInstructionClock()/100000) * uS;

    // Subitrai-se todos os ciclos usados até chegar no loop abaixo
    // Também subtrai-se 22 ciclos do return da função
    CiclosNecessarios -= (153 + 22);

    if (CiclosNecessarios <= 45)
    {
        // Se ja estiver excedido o numero de ciclos retornamos
        return;
    }// Fim if
    else
    {
        while (CiclosNecessarios > 0) //153 ciclos usados até este ponto.
        {
            Nop(); //Delay 1 instrução
            //Subtrai ciclos gastos no while a cada interação, 42 neste caso.
            CiclosNecessarios -= 42;
        }// Fim while
    }// Fim else
}// Fim void Delay10us

void DelayMs( unsigned short int ms )
{
    // Variavel que armazena o numero de ciclos necessarios para o delay inteiro
    long CiclosNecessarios;

    //Calcula o numero de instruções que deve ser o atraso
    CiclosNecessarios = (signed long)(GetInstructionClock()/1000) * ms;

    // Subitrai-se todos os ciclos usados até chegar no loop abaixo
    // Também subtrai-se 22 ciclos do return da função
    CiclosNecessarios -= (148 + 22);

    if (CiclosNecessarios <= (170+25))
    {
        return;    // Se ja estiver excedido o numero de ciclos retornamos
    }// Fim if
    else
    {
        while (CiclosNecessarios > 0) //148 ciclos foram usados até este ponto
        {
            Nop();// Delay de 1 instrucao
            //Subtrai ciclos gastos no while a cada interação, 39 neste caso
            CiclosNecessarios -= 39;
        }// Fim while
    }// Fim else
}// Fim void DelayMs
