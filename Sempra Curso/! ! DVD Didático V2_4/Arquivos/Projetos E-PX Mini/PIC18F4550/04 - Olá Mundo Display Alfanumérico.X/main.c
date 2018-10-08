/******************************************************************************
 *
 *            		SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-P18mini
 * Prática:	 	OLA MUNDO
 *
 * Autor:               Bruno A. Dayrell
 * Versão:		v1.0	
 *						
 * Descrição:       	Inicialização do Display alfanumérico LCD, escrevendo
 *			nele o "OLA MUNDO". Exemplificação sobre o uso de 
 *			bibliotecas proprietárias. Comunicação com um
 *			dispositivo inteligente externo ao PIC.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.


#include "displayLCD_mini.h"						 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
//atribuição:	0 = LED desligado
//		1 = LED ligado
#define LED_AMARELO	LATCbits.LATC1
#define LED_VERMELHO    LATCbits.LATC2


/** V A R I A V E I S   G L O B A I S ****************************************/

// armazena variavel na memória de dados (SDRAM)
// outro tipo sintaxe C para inicializar a variável na DECLARAÇÃO
rom unsigned char linha2[20]="Curso SEMPRA";

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa principal,
 *		pois esta é a primeira a ser chamada após o	reset do 
 *		microcontrolador.
 *		Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/

void main(void)
{
	// Configura as portas e periféricos usados no projeto
	ConfiguraSistema();
			
	
	// Configura e inicializa o display LCD
	ConfiguraLCD();
	
	LimpaDisplay();
	
	// Posiciona o cursro na linha 1 e na primeira coluna do display
	PosicaoCursorLCD (1,1);
	
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD ("OLA MUNDO");

	// Posiciona o cursor na linha 2 e primeira coluna do display
	PosicaoCursorLCD(2,1);
	
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD (linha2);

	// Laço infinito
	while(1)
   	{ 
		
	}//end while
	
}//end main

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:  	ConfiguraSistema é a rotina de configuração principal do projeto.
 *		Seu objetivo é configurar as portas de I/O e os demais periféricos
 *		do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	
	// Desabilita todas as 13 portas analógicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Configura LED do Kit PICMINAS: saida digital	
	TRISCbits.TRISC1=0;	// RC1: saida digital - LED_AMARELO
	TRISCbits.TRISC2=0; 	// RC2: saida digital - LED_VERDE

	// Configura Botão do Kit PICMINAS: entradas digital
	TRISBbits.TRISB4=1;	// RB4: entrada digital - BOTAO BOOT
	
	
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