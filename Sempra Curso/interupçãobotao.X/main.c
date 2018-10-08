
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
    
    
    RCONbits.IPEN = 1; // Usa interrupções com prioridade
    INTCONbits.GIEH = 0; // Desliga as interrupções de alta prioridade
    INTCONbits.GIEL = 0; // Desliga as interrupções de baixa prioridade
    
    INTCONbits.RBIE = 1; // Habilita interrupções da PORTA B (B4 a B7)
    INTCON2bits.RBIP = 1; // Coloca a interrupção da PORTA B em alta prioridade
    INTCONbits.RBIF = 0; // Incia com o flag limpo.
    INTCON2bits.RBPU = 1; // Desabilita os resistores de pull up da porta B.
    
    INTCONbits.GIEH = 1; // Liga as interrupções de alta prioridade
    INTCONbits.GIEL = 1; // Liga as interrupções de baixa prioridade
    
    
	// Laço de repetição infinito que executa aplicaÁ?o do firmware
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
 * SaÌda:		Nenhuma (void)
 * DescriÁ?o:	FunÁ?o de tratamento das interrupÁ?es de ALTA prioridade
 *		Nessa funÁ?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupÁ?o, comparando
 *		os flags de cada tipo de interrupÁ?o.
 *			2- tratar a interrupÁ?o selecionada.
 *			3- limpar o flag que causou a interrupÁ?o!!! Importante
 *		para garantir que n?o ocorrer· uma chamada indesejada ao sair
 *		do tratamento da interrupÁ?o.
 *****************************************************************************/
// ATEN«?O NA SINTAXE de declaraÁ?o com #pragma interrupt = Alta prioridade
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
 * SaÌda:		Nenhuma (void)
 * DescriÁ?o:	FunÁ?o de tratamento das interrupÁ?es de BAIXA prioridade
 *		Nessa funÁ?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupÁ?o, comparando
 *		os flags de cada tipo de interrupÁ?o.
 *			2- tratar a interrupÁ?o selecionada.
 *			3- limpar o flag que causou a interrupÁ?o!!! Importante
 *		para garantir que n?o ocorrer· uma chamada indesejada ao sair
 *		do tratamento da interrupÁ?o.
 *
 *		Ao sair dessa funÁ?o È usado o retorno do tipo "retfie",
 *		pois esta funÁ?o È declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATEN«?O NA SINTAXE de declaraÁ?o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
    
}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Sera necessario informar ao compilador C18 onde são os novos endereços
//da memôria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupção.

//
// ATENÇÃO: Copiar esta parte do côdigo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para gravação in-circuit.
// protôtipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal
// no endereço 0x1000 da memôria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Alocação da função de tratamento das interrupções de ALTA prioridade
// no endereço 0x1008 da memôria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// AlocaÁ?o da funÁ?o de tratamento das interrupÁ?es de BAIXA prioridade
// no endereÁo 0x1018 da memÛria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a alocaÁ?o dos endereÁos
				// da memÛria de programa para seus valores padr?o

/** F I M  D A  S E « ? O  D E   V E C T O R   R E M A P P I N G *************/