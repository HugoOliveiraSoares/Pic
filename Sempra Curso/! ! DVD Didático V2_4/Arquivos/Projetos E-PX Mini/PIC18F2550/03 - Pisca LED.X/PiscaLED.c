/******************************************************************************
 *
 *            		SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-P18mini
 * Pr�tica:	 	Pisca Leds
 *
 * Autor:               Bruno A. Dayrell
 * Vers�o:		v1.0
 *						
 * Descri��o:     	Exemplificar como deve ser utilizado um arquivo 
 *			biblioteca (.h) do compilador. Demonstrar como adicionar
 *			e utilizar fun��es da biblioteca no projeto do MPLAB.
 *			Pisca dois LEDs n�o-alternadamente no loop principal
 *			do firmware
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, os modelos 18F4550 e 18F2550
					
#include <delays.h>	// Biblioteca padr�o de rotinas de atraso do C18 Microchip
			// mais informa��es nos arquivos de ajuda da biblioteca C18
			// presentes na propria pasta de instala��o, por exemplo,
			// C:\MCC18\doc\hlpC18Lib.chm
			// Procure pelo item: "Delay Functions"

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *		pois esta � a primeira a ser chamada ap�s o	reset do 
 *		microcontrolador.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/



void main (void){
	// Configura as portas e perif�ricos do PIC.
	ConfiguraSistema();
	
	// Inicializa para que o sentido de altern�ncia seja sempre o mesmo
	LATCbits.LATC1 = 1;
	LATCbits.LATC2 = 0;
	
	// La�o infinito que executa a opera��o principal do projeto.
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
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	ConfiguraSistema � a rotina de configura��o principal do projeto.
 *		Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *		do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	// Desabilita todas as 13 entradas anal�gicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Configura o pino RC2 como saida digital
	TRISCbits.TRISC1 = 0;	// RD0: ligado ao led Amarelo
	TRISCbits.TRISC2 = 0;
	
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x800 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
		// da mem�ria de programa para seus valores padr�o
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/