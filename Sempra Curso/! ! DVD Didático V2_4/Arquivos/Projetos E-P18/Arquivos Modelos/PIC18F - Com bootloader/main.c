/******************************************************************************
 *
 *            PICMINAS PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo)	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	PICMINAS
 * Pr�tica: 			
 * Descri��o:     
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.
						 			
/** V A R I A V E I S   G L O B A I S ****************************************/

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);
void HighPriorityISRCode();
void LowPriorityISRCode();
/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:        	void main(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Fun��o principal do programa. 
 *****************************************************************************/
void main(void)
{
	
	ConfiguraSistema();		// Configura as portas e perif�ricos do PIC.

    while(1)				// La�o infinito que executa o funcionamento principal do projeto.
   { 

	
	}//end while(1)
}//end main

/******************************************************************************
 * Funcao:        	void ConfiguraSistema(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       InicializaSistema � a rotina de configura��o principal do PIC.
 *					Seu objetivo � configurar as portas de I/O e os perif�ricos
 *					do microcontrolador para que os mesmos trabalhem da maneira
 *					desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema(void)
{
	// Configurando Pinos de I/O: Todas as portas digitais do PIC podem ser configuradas
	// como entrada ou como sa�da. Esta escolha � feita dentro do registrador TRIS.
	//
	// Quando acessamos o registrador TRISD ou TRISC estamos configurando o funcio-
	// namento de todas suas portas digitais, ou seja, todo PORTD e PORTC.
	// Mas quando escrevemos TRISDbits ou TRISCbits, estamos configurando apenas
	// uma das portas do conjunto de portas PORTD e PORTC.
	//
	// Para configurar uma porta como entrada atriui-se o valor "1" a seu registrador 
	// e para configura-la com sa�da basta atribuir o valor "0"(zero). Para memorizar 
	// facilmente lembre-se que o digito "1" parece com a letra "i" que lembra de 
	// Input(Entrada), j� o digito "0"(zero) parece a letra "o" que lembra Output(sa�da).

// Configura LED's do KitPICMinas: saida digital
	ADCON1 |= 0x0F; 		// configura todas as portas como digitais

//	TRISCbits.TRISC2=0; 	// RC0: saida digital - LED_VERDE	
//	TRISDbits.TRISD0=0; 	// RD1: saida digital - LED_AMARELO

// Configura Bot�es do KitPICMinas: entradas digitais
//	TRISEbits.TRISE1=1; 	// RC1: entrada digital - BOTAO_1
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necess�ria para o compilador C18 saber onde � o in�cio do vetor de
// "reset".
// Copiar na �ntegra esta parte do c�digo dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
/** EOF main.c ***************************************************************/
