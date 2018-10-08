/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:	TimeDelay.h
 * Dependencias:	Veja seção INCLUDES
 * Processador:		PIC18F4550
 * Opção de Clock:	Definir no define GetInstructionClock()
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
 * Descrição:   Biblioteca para contagem de tempo através de espera ocupada
 *              da CPU.
 *	Notas:
 *              Para que esta biblioteca faça a contagem correta do tempo,
 *              deve-se definir o ciclo de instrução no #define
 *              GetInstructionClock()
 *****************************************************************************/


#include <p18cxxx.h>

#define GetInstructionClock() 12000000

/****************************************************************************
  Função:
    void Delay10us( unsigned long tenMicroSecondCounter )

  Descrição:
    Faz delays de múltiplos de 10 micro segundos.

  Parâmetros:
    unsigned long tenMicroSecondCounter - Número de dezenas de micro segundos
 que deve ser atrasado.

  Returns:
 Nenhum

  Remarks:
 Configurar o GetInstructionClock() para seu microcontrolador

  ***************************************************************************/
void Delay10us( unsigned long tenMicroSecondCounter );

/****************************************************************************
    Função:
    void DelayMs( unsigned short int ms )

  Description:
 Esta função faz delays de multiplos de mili segundos

 Parâmetros:
    unsigned short int  ms - numero de mili segundos que será feito o delay

  Returns:
    None

  Remarks:
 Configurar o GetInstructionClock() para seu microcontrolador
  ***************************************************************************/
void DelayMs( unsigned short int ms );
