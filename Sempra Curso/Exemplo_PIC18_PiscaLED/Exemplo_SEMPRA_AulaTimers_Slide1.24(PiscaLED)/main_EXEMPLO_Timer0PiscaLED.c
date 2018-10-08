/******************************************************************************
 *
 *           SEMPRA PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main_EXEMPLO_Timer0PiscaLED.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo)	
 * Compilador:        	C18 v3.20 ou superior
 * Descrição:        	EXEMPLO Pisca LED Timer0
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>            // Necessário para que o compilador adicione a biblioteca
                                // com as definições do PIC selecionado no projeto, neste
                                // caso, o modelo 18F4550.
#include <timers.h>		// Biblioteca C18 com funções de Timer

// Saidas Digitais
#define	LED_AMARELO     LATCbits.LATC2
#define	LED_VERMELHO    LATCbits.LATC1

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

void main(void)
{
    ConfiguraSistema();		// Configura as portas e periféricos do PIC.

    while(1)	// Laço infinito que executa o funcionamento principal do projeto.
   {		
		
   }//end while(1)
}//end main

void ConfiguraSistema(void)
{

	ADCON1 |= 0x0F; 		// Configura todas as portas como digitais

        // Configura saidas digitais
	TRISCbits.TRISC2 = 0;	//RC2 (LED_AMARELO)
	TRISCbits.TRISC1 = 0;	//RC1 (LED_VERMELHO)

        // Escolhe estado inicial das saidas digitais
        LED_AMARELO = 0;
        LED_VERMELHO = 0;

	//Configuração Global das Interrupções
	RCONbits.IPEN = 1;	// Habilita prioridades de interrupcao
	INTCONbits.GIEH = 0;	// Desabilita vetor de alta prioridade
	INTCONbits.GIEL = 0;	// Desabilita vetor de baixa prioridade

	//Configurações da Interrupção do Timer0
	INTCONbits.TMR0IE = 1;	// Habilita interrupcao de Timer0
	INTCONbits.TMR0IF = 0;	// Limpa a sinalizaÁ?o da interrupcao,
							//para garantir que nao entra na interrupcao por sujeira na memoria
        INTCON2bits.TMR0IP = 1;	// Tratamento de interrupcao no vetor de Alta prioridade

        OpenTimer0(TIMER_INT_ON  &	// Habilita Interrupção do Timer0
                   T0_16BIT	 &	// Contagem do Timer0 com 16bits
                   T0_SOURCE_INT &	// Fonte de clock interno
                   T0_PS_1_64);         // Prescaler 1:64

        // Carrega valor inicial do Timer0
	WriteTimer0(9286);

        // Habilita vetores de Alta e Baixa Prioridade
        INTCONbits.GIEH = 1;
        INTCONbits.GIEL = 1;
}//end ConfiguraSistema

#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	// Verifica se o motivo da chamada da interrupção foi o estouro do Timer0
	if(INTCONbits.TMR0IF)
	{
            WriteTimer0(9286); // Re-escreve o valor inicial da contagem do Timer0
            LED_VERMELHO = !LED_VERMELHO;
            INTCONbits.TMR0IF = 0; //Limpa flag da interrupção
	}// end tratamento da interrupÁ?o do Timer0 (INTCONbits.TMR0IF)
}// end Tratamento_High_Interrupt

#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{	
}//end Tratamento_Low_Interrupt

extern void _startup (void);        // See c018i.c in your C18 compiler dir
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
#pragma code	// Diretiva que retorna a alocação dos endereços
		// da memÛria de programa para seus valores padr?o

/** F I M  D A  S E « ? O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/