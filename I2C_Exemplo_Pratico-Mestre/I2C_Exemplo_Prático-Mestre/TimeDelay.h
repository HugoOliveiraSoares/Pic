/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:	TimeDelay.h
 * Dependencias:	Veja se��o INCLUDES
 * Processador:		PIC18F4550
 * Op��o de Clock:	Definir no define GetInstructionClock()
 * Compilador:		C18 v3.20 ou superior
 * Empresa:		SEMPRA
 *
 * Plataforma:		Placa E-P18 v3.0, v3.5 e v3.6
 *                      Placa E-PX Mini
 *                      Placa E-PDuino Nano
 *
 * Autor:		Bruno Silveira Avelar
 *
 * Data:		v1 - 04/Dez/2014 - Bruno Silveira Avelar
 *
 * Descri��o:   Biblioteca para contagem de tempo atrav�s de espera ocupada
 *              da CPU.
 *	Notas:
 *              Para que esta biblioteca fa�a a contagem correta do tempo,
 *              deve-se definir o ciclo de instru��o no #define
 *              GetInstructionClock()
 *****************************************************************************/


#include <p18cxxx.h>

#define GetInstructionClock() 12000000

/****************************************************************************
  Fun��o:
    void Delay10us( unsigned long tenMicroSecondCounter )

  Descri��o:
    Faz delays de m�ltiplos de 10 micro segundos.

  Par�metros:
    unsigned long tenMicroSecondCounter - N�mero de dezenas de micro segundos
 que deve ser atrasado.

  Returns:
 Nenhum

  Remarks:
 Configurar o GetInstructionClock() para seu microcontrolador

  ***************************************************************************/
void Delay10us( unsigned long tenMicroSecondCounter );

/****************************************************************************
    Fun��o:
    void DelayMs( unsigned short int ms )

  Description:
 Esta fun��o faz delays de multiplos de mili segundos

 Par�metros:
    unsigned short int  ms - numero de mili segundos que ser� feito o delay

  Returns:
    None

  Remarks:
 Configurar o GetInstructionClock() para seu microcontrolador
  ***************************************************************************/
void DelayMs( unsigned short int ms );
