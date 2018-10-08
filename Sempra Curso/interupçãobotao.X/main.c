
/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <timers.h>
#include <delays.h>


void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);


void main(void)
{
    ADCON1 = ADCON1 | 0x0f;
    
    
    TRISEbits.TRISE1 = 1; //botao1
    TRISBbits.TRISB4 = 1; //botao 2
    TRISAbits.TRISA4 = 0; //led vermelho
    TRISAbits.TRISA5 = 0; //led verde 
    TRISDbits.TRISD0 = 0; //led amarelo
    
    
    RCONbits.IPEN = 1; // Usa interrup��es com prioridade
    INTCONbits.GIEH = 0; // Desliga as interrup��es de alta prioridade
    INTCONbits.GIEL = 0; // Desliga as interrup��es de baixa prioridade
    
    INTCONbits.RBIE = 1; // Habilita interrup��es da PORTA B (B4 a B7)
    INTCON2bits.RBIP = 1; // Coloca a interrup��o da PORTA B em alta prioridade
    INTCONbits.RBIF = 0; // Incia com o flag limpo.
    INTCON2bits.RBPU = 1; // Desabilita os resistores de pull up da porta B.
    
    INTCONbits.GIEH = 1; // Liga as interrup��es de alta prioridade
    INTCONbits.GIEL = 1; // Liga as interrup��es de baixa prioridade
    
    
	// La�o de repeti��o infinito que executa aplica�?o do firmware
	while(1)
	{
        LATAbits.LATA5 = 1;//led verde 
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        LATAbits.LATA5 = 0;
        Delay10KTCYx(200);
        Delay10KTCYx(200);
        
        
	}//end while(1)

}//end main

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri�?o:	Fun�?o de tratamento das interrup�?es de ALTA prioridade
 *		Nessa fun�?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup�?o, comparando
 *		os flags de cada tipo de interrup�?o.
 *			2- tratar a interrup�?o selecionada.
 *			3- limpar o flag que causou a interrup�?o!!! Importante
 *		para garantir que n?o ocorrer� uma chamada indesejada ao sair
 *		do tratamento da interrup�?o.
 *****************************************************************************/
// ATEN�?O NA SINTAXE de declara�?o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
        if( INTCONbits.RBIF == 1)
	   {
		// Variavel temporaria, usada para corrigir erro na Note1 p101 do Datasheet
		// do PIC18F4550 revE.
		char temp;
        char i = 0;// Variavel usada para piscar o LED 5 no for
		// Leitura do PORTB para corrigir erro de limpeza do flag RBIF
		temp = PORTB;
 
                for (i = 0; i <5 ; i++)
                {  
                    LATAbits.LATA4 = 1;
                    Delay10KTCYx(200);
                    Delay10KTCYx(200);
                    LATAbits.LATA4 = 0;
                    Delay10KTCYx(200);
                    Delay10KTCYx(200);
                }
        
		 INTCONbits.RBIF = 0;
	}
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri�?o:	Fun�?o de tratamento das interrup�?es de BAIXA prioridade
 *		Nessa fun�?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup�?o, comparando
 *		os flags de cada tipo de interrup�?o.
 *			2- tratar a interrup�?o selecionada.
 *			3- limpar o flag que causou a interrup�?o!!! Importante
 *		para garantir que n?o ocorrer� uma chamada indesejada ao sair
 *		do tratamento da interrup�?o.
 *
 *		Ao sair dessa fun�?o � usado o retorno do tipo "retfie",
 *		pois esta fun�?o � declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATEN�?O NA SINTAXE de declara�?o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
    
}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Sera necessario informar ao compilador C18 onde s�o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup��o.

//
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

// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x1008 da mem�ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca�?o da fun�?o de tratamento das interrup�?es de BAIXA prioridade
// no endere�o 0x1018 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a aloca�?o dos endere�os
				// da mem�ria de programa para seus valores padr?o

/** F I M  D A  S E � ? O  D E   V E C T O R   R E M A P P I N G *************/