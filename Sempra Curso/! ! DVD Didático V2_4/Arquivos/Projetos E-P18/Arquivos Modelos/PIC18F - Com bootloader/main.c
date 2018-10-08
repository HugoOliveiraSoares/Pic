/******************************************************************************
 *
 *            PICMINAS PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo)	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	PICMINAS
 * Prática: 			
 * Descrição:     
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
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
 * Saída:          	Nenhuma (void)
 * Descrição:       Função principal do programa. 
 *****************************************************************************/
void main(void)
{
	
	ConfiguraSistema();		// Configura as portas e periféricos do PIC.

    while(1)				// Laço infinito que executa o funcionamento principal do projeto.
   { 

	
	}//end while(1)
}//end main

/******************************************************************************
 * Funcao:        	void ConfiguraSistema(void)
 * Entrada:         Nenhuma (void)
 * Saída:          	Nenhuma (void)
 * Descrição:       InicializaSistema é a rotina de configuração principal do PIC.
 *					Seu objetivo é configurar as portas de I/O e os periféricos
 *					do microcontrolador para que os mesmos trabalhem da maneira
 *					desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema(void)
{
	// Configurando Pinos de I/O: Todas as portas digitais do PIC podem ser configuradas
	// como entrada ou como saída. Esta escolha é feita dentro do registrador TRIS.
	//
	// Quando acessamos o registrador TRISD ou TRISC estamos configurando o funcio-
	// namento de todas suas portas digitais, ou seja, todo PORTD e PORTC.
	// Mas quando escrevemos TRISDbits ou TRISCbits, estamos configurando apenas
	// uma das portas do conjunto de portas PORTD e PORTC.
	//
	// Para configurar uma porta como entrada atriui-se o valor "1" a seu registrador 
	// e para configura-la com saída basta atribuir o valor "0"(zero). Para memorizar 
	// facilmente lembre-se que o digito "1" parece com a letra "i" que lembra de 
	// Input(Entrada), já o digito "0"(zero) parece a letra "o" que lembra Output(saída).

// Configura LED's do KitPICMinas: saida digital
	ADCON1 |= 0x0F; 		// configura todas as portas como digitais

//	TRISCbits.TRISC2=0; 	// RC0: saida digital - LED_VERDE	
//	TRISDbits.TRISD0=0; 	// RD1: saida digital - LED_AMARELO

// Configura Botões do KitPICMinas: entradas digitais
//	TRISEbits.TRISE1=1; 	// RC1: entrada digital - BOTAO_1
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necessária para o compilador C18 saber onde é o início do vetor de
// "reset".
// Copiar na íntegra esta parte do código dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
/** EOF main.c ***************************************************************/
