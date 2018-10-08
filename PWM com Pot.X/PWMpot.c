/* 
 * File:   PWMpot.c
 * Author: Hugo
 *
 * Created on 11 de Março de 2017, 20:58
 */

#include <p18f4550.h>
#include "TimeDelay.h"
#include <adc.h>
#include <timers.h>              // Necessário para utilizar as funções do timer
#include <pwm.h>                // Necessário para utilizar as funções do PWM

#define RESOLUCAO (5.0/1023.0) // Resolução do CAD de 10bits = 5V/(2^10-1)


void ConfiguraSistema(void) ;
void ConfiguraInterrupcao(void) ;
void Tratamento_High_Interrupt(void) ;
void Tratamento_Low_Interrupt(void) ;

int DC = 0 ;    // variavel que recebe o valor do duty cycle


void main()
{
    int resultadoBin = 0;            // Guarda o valor da conversão AD em BINÁRIO.
	float resolucao = RESOLUCAO;    // Guarda o valor da resolução do conversor AD.
    
    ConfiguraInterrupcao();
    ConfiguraSistema();
    
    SelChanConvADC(ADC_CH1);        // Inicia a primeira medida
	
    while(1)
    {
        if( !BusyADC() )
            {  
                    resultadoBin = ReadADC();
 
                    DC = resultadoBin / 4;
                    
                    if(DC >= 1023)  // verifica se DC é menor ou igual a 1023
                    {
                        DC = 1023 ;
                    }

                    if(DC <= 0)     // verifica se DC é menor ou igual a 0
                    {
                        DC = 0 ;
                    }
  
                    SetDCPWM1(DC);  // usa a varial DC para determinar o duty cycle
                    
                    DelayMs(100);   // tempo dado para que a variação do brilho do led não seja mto rapida         
                    ConvertADC();   //Inicia a nova medida
                    
                }
            }
        
        
}

void ConfiguraSistema(void)
{
    ADCON1 = ADCON1 | 0x0f;                 // Desabilita pinos analógicos

    TRISCbits.TRISC2 = 0; 
	
    OpenTimer2(TIMER_INT_OFF & T0_PS_1_16); // abre o timer2
    
    OpenPWM1(255) ;                         // inicia o pwm com frequencia de 2,44 KHz
    
     SetDCPWM1(0) ;                         // seta o valor inicial do duty cycle

    // Configura o Conversor Analogico Digital (CAD)
	OpenADC(
		  //Parâmetro Config
		  ADC_FOSC_64		&       //Clock do AD como FOSC/64
		  ADC_RIGHT_JUST	&       //Justificando a direita
		  ADC_2_TAD,                //Tempo de aquisição de 2 TAD
		  //Parâmetro Config2
		  ADC_CH1		&           //Canal 1
		  ADC_INT_OFF   	&       //Não utiliza interrupção
		  ADC_REF_VDD_VSS,          //Tensoes de referencia
		  //Parâmetro PortConfig
		  ADC_5ANA );               //Habilita 5 Portas analógicas (AN0 - AN4)
}


void ConfiguraInterrupcao(void)
{
	//Configuração Global das Interrupções
    INTCONbits.GIE = 0 ;    // Desabilita todos as interrupcoes
	RCONbits.IPEN = 1 ;     // Habilita prioridades de interrupcao
	INTCONbits.GIEH = 0 ;	// Desabilita vetor de alta prioridade
	INTCONbits.GIEL = 0 ;	// Desabilita vetor de baixa prioridade

}

// ATENÇÃO NA SINTAXE de declaração com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	// Escreva a função de tratamento de interrupção de Alta prioridade aqui
	
}

// ATENÇÃO NA SINTAXE de declaração com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrupção de Baixa prioridade aqui
}



/** V E C T O R   R E M A P P I N G ******************************************/
// Seção necessária para informar ao compilador C18 onde são os novos endereços
//da memória de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupção.
// ATENÇÃO: Copiar esta parte do código dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para gravação in-circuit.
// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal 
// no endereço 0x1000 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}



/** V E C T O R   R E M A P P I N G \ INTERRUPÇÕES ***********************/
// Alocação da função de tratamento das interrupções de ALTA prioridade
// no endereço 0x1008 da memória de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Alocação da função de tratamento das interrupções de BAIXA prioridade 
// no endereço 0x1018 da memória de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a alocação dos endereços 
				// da memória de programa para seus valores padrão

/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/