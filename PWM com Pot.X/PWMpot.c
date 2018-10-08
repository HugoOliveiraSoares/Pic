/* 
 * File:   PWMpot.c
 * Author: Hugo
 *
 * Created on 11 de Mar�o de 2017, 20:58
 */

#include <p18f4550.h>
#include "TimeDelay.h"
#include <adc.h>
#include <timers.h>              // Necess�rio para utilizar as fun��es do timer
#include <pwm.h>                // Necess�rio para utilizar as fun��es do PWM

#define RESOLUCAO (5.0/1023.0) // Resolu��o do CAD de 10bits = 5V/(2^10-1)


void ConfiguraSistema(void) ;
void ConfiguraInterrupcao(void) ;
void Tratamento_High_Interrupt(void) ;
void Tratamento_Low_Interrupt(void) ;

int DC = 0 ;    // variavel que recebe o valor do duty cycle


void main()
{
    int resultadoBin = 0;            // Guarda o valor da convers�o AD em BIN�RIO.
	float resolucao = RESOLUCAO;    // Guarda o valor da resolu��o do conversor AD.
    
    ConfiguraInterrupcao();
    ConfiguraSistema();
    
    SelChanConvADC(ADC_CH1);        // Inicia a primeira medida
	
    while(1)
    {
        if( !BusyADC() )
            {  
                    resultadoBin = ReadADC();
 
                    DC = resultadoBin / 4;
                    
                    if(DC >= 1023)  // verifica se DC � menor ou igual a 1023
                    {
                        DC = 1023 ;
                    }

                    if(DC <= 0)     // verifica se DC � menor ou igual a 0
                    {
                        DC = 0 ;
                    }
  
                    SetDCPWM1(DC);  // usa a varial DC para determinar o duty cycle
                    
                    DelayMs(100);   // tempo dado para que a varia��o do brilho do led n�o seja mto rapida         
                    ConvertADC();   //Inicia a nova medida
                    
                }
            }
        
        
}

void ConfiguraSistema(void)
{
    ADCON1 = ADCON1 | 0x0f;                 // Desabilita pinos anal�gicos

    TRISCbits.TRISC2 = 0; 
	
    OpenTimer2(TIMER_INT_OFF & T0_PS_1_16); // abre o timer2
    
    OpenPWM1(255) ;                         // inicia o pwm com frequencia de 2,44 KHz
    
     SetDCPWM1(0) ;                         // seta o valor inicial do duty cycle

    // Configura o Conversor Analogico Digital (CAD)
	OpenADC(
		  //Par�metro Config
		  ADC_FOSC_64		&       //Clock do AD como FOSC/64
		  ADC_RIGHT_JUST	&       //Justificando a direita
		  ADC_2_TAD,                //Tempo de aquisi��o de 2 TAD
		  //Par�metro Config2
		  ADC_CH1		&           //Canal 1
		  ADC_INT_OFF   	&       //N�o utiliza interrup��o
		  ADC_REF_VDD_VSS,          //Tensoes de referencia
		  //Par�metro PortConfig
		  ADC_5ANA );               //Habilita 5 Portas anal�gicas (AN0 - AN4)
}


void ConfiguraInterrupcao(void)
{
	//Configura��o Global das Interrup��es
    INTCONbits.GIE = 0 ;    // Desabilita todos as interrupcoes
	RCONbits.IPEN = 1 ;     // Habilita prioridades de interrupcao
	INTCONbits.GIEH = 0 ;	// Desabilita vetor de alta prioridade
	INTCONbits.GIEL = 0 ;	// Desabilita vetor de baixa prioridade

}

// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	// Escreva a fun��o de tratamento de interrup��o de Alta prioridade aqui
	
}

// ATEN��O NA SINTAXE de declara��o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrup��o de Baixa prioridade aqui
}



/** V E C T O R   R E M A P P I N G ******************************************/
// Se��o necess�ria para informar ao compilador C18 onde s�o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup��o.
// ATEN��O: Copiar esta parte do c�digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para grava��o in-circuit.
// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x1000 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}



/** V E C T O R   R E M A P P I N G \ INTERRUP��ES ***********************/
// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x1008 da mem�ria de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de BAIXA prioridade 
// no endere�o 0x1018 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o

/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/