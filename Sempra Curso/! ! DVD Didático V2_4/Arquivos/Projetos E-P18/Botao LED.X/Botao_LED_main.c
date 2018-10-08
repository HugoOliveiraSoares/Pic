/******************************************************************************
 *
 *             SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:		HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P18 - SEMPRA
 * Prática: 		BOTAO LED
 * Descrição:           Usar uma estrutura if-else para ligar os LEDs verde
 *			e amarelo do KIT E-P18.
 *			Se o botão 1 está pressionado:
 *				Desliga verde, liga vermelho
 *			Senão:
 *				Liga verde e desliga vermelho.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.
						 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
//atribuição:	0 = LED desligado
//				1 = LED ligado
#define LED_VERDE	PORTCbits.RC2
#define LED_VERMELHO 	PORTDbits.RD1
#define LED_AMARELO 	PORTDbits.RD0

// Botões do Kit PICMINAS: entradas digitais
//atribuição:	0 = botao não pressionado
//				1 = botao pressionado
#define BOTAO_1			PORTEbits.RE1
#define BOTAO_2			PORTEbits.RE2


/** V A R I A V E I S   G L O B A I S ****************************************/


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa principal,
 *				pois esta é a primeira a ser chamada após o	reset do 
 *				microcontrolador.
 *				Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{
	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();

	// Laço infinito que executa a operação principal do projeto.
	while (1)
	{
		//testa BOTÃO 1 e muda estado dos LED's VERDE e VERMELHO
		if (BOTAO_1)
		{
			LED_VERDE=0;  
			LED_VERMELHO=1;
		}
		else
		{
			LED_VERDE=1;   
			LED_VERMELHO=0;
		}
	
	}//end while(1)
	
}//end main

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:  	ConfiguraSistema é a rotina de configuração principal do projeto.
 *				Seu objetivo é configurar as portas de I/O e os demais periféricos
 *				do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	
	// Desabilita todas as 13 portas analógicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;

	// Configura LED do Kit PICMINAS: saida digital	
	TRISDbits.TRISD1=0; 	// RD0: saida digital - LED_VERMELHO
	TRISCbits.TRISC2=0; 	// RC2: saida digital - LED_VERDE

	// Configura Botão do Kit PICMINAS: entradas digital
	TRISEbits.TRISE1=1;		// RE1: entrada digital - BOTAO_1

}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// ATENÇÃO: COPIAR ESTA SEÇÃO DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVAÇÃO IN-CIRCUIT.

// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal 
// no endereço 0x800 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a alocação dos endereços 
				// da memória de programa para seus valores padrão
/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
