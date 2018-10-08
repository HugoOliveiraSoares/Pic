/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <timers.h>
#include <pwm.h>

int brilho = 0;

void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);



void main(void)
{
    ADCON1 = ADCON1 | 0x0f;
    
    TRISCbits.TRISC2 = 0;
    TRISEbits.TRISE1 = 1;
    TRISEbits.TRISE2 = 1;
    
    OpenTimer2( TIMER_INT_OFF & T0_PS_1_16 );
    
    OpenPWM1(255);
    
    SetDCPWM1(0) ;
    
    while(1)
	{
        
        if(PORTEbits.RE1 == 1)
            {
                brilho += 1;   
                SetDCPWM1(brilho);
            }
        
        if(PORTEbits.RE2 == 1)
            {
                brilho -= 1;   
                SetDCPWM1(brilho);
            }
        
      
	}//end while(1)

}//end main

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * SaÃda:		Nenhuma (void)
 * Descri¡?o:	Fun¡?o de tratamento das interrup¡?es de ALTA prioridade
 *		Nessa fun¡?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup¡?o, comparando
 *		os flags de cada tipo de interrup¡?o.
 *			2- tratar a interrup¡?o selecionada.
 *			3- limpar o flag que causou a interrup¡?o!!! Importante
 *		para garantir que n?o ocorrer∑ uma chamada indesejada ao sair
 *		do tratamento da interrup¡?o.
 *****************************************************************************/
// ATEN´?O NA SINTAXE de declara¡?o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
       
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * SaÃda:		Nenhuma (void)
 * Descri¡?o:	Fun¡?o de tratamento das interrup¡?es de BAIXA prioridade
 *		Nessa fun¡?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup¡?o, comparando
 *		os flags de cada tipo de interrup¡?o.
 *			2- tratar a interrup¡?o selecionada.
 *			3- limpar o flag que causou a interrup¡?o!!! Importante
 *		para garantir que n?o ocorrer∑ uma chamada indesejada ao sair
 *		do tratamento da interrup¡?o.
 *
 *		Ao sair dessa fun¡?o » usado o retorno do tipo "retfie",
 *		pois esta fun¡?o » declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATEN´?O NA SINTAXE de declara¡?o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
    
}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Se¡?o necess∑ria para informar ao compilador C18 onde s?o os novos endere¡os
//da mem€ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup¡?o.

//
// ATEN´?O: Copiar esta parte do c€digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para grava¡?o in-circuit.

// prot€tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca¡?o da fun¡?o de tratamento do "reset" da aplica¡?o principal
// no endere¡o 0x1000 da mem€ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca¡?o da fun¡?o de tratamento das interrup¡?es de ALTA prioridade
// no endere¡o 0x1008 da mem€ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca¡?o da fun¡?o de tratamento das interrup¡?es de BAIXA prioridade
// no endere¡o 0x1018 da mem€ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a aloca¡?o dos endere¡os
				// da mem€ria de programa para seus valores padr?o

/** F I M  D A  S E ´ ? O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/