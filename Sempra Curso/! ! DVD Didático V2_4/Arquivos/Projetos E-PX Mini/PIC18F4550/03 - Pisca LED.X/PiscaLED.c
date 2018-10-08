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
 * Prática:	 	Pisca Leds
 *
 * Autor:               Bruno A. Dayrell
 * Versão:		v1.0
 *						
 * Descrição:     	Exemplificar como deve ser utilizado um arquivo 
 *			biblioteca (.h) do compilador. Demonstrar como adicionar
 *			e utilizar funções da biblioteca no projeto do MPLAB.
 *			Pisca dois LEDs não-alternadamente no loop principal
 *			do firmware
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, os modelos 18F4550 e 18F2550
					
#include <delays.h>	// Biblioteca padrão de rotinas de atraso do C18 Microchip
			// mais informações nos arquivos de ajuda da biblioteca C18
			// presentes na propria pasta de instalação, por exemplo,
			// C:\MCC18\doc\hlpC18Lib.chm
			// Procure pelo item: "Delay Functions"

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



void main (void){
	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();
	
	// Inicializa para que o sentido de alternância seja sempre o mesmo
	LATCbits.LATC1 = 1;
	LATCbits.LATC2 = 0;
	
	// Laço infinito que executa a operação principal do projeto.
	while (1)	
	{
		// Pisca LED Vermelho
		LATCbits.LATC2 = !LATCbits.LATC2;
		Delay10KTCYx(240);
		
		// Pisca LED Amarelo
		LATCbits.LATC1 = !LATCbits.LATC1;
		Delay10KTCYx(240);
		
	}//end while(1)

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
	// Desabilita todas as 13 entradas analógicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Configura o pino RC2 como saida digital
	TRISCbits.TRISC1 = 0;	// RD0: ligado ao led Amarelo
	TRISCbits.TRISC2 = 0;
	
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