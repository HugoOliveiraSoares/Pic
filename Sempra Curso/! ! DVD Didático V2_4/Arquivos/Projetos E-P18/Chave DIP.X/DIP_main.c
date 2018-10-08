/******************************************************************************
 *
 *                              SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P18 v3.6
 * Prática:	 	Uso da chave DIP e da bilbioteca do display de 
 *			Duplo de 7 Segmentos.
 *						
 * Descrição:       	Ler a chave DIP como se fosse um número binário e mostrar
 *			seu valor no display duplo de 7 segmentos.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.
						
#include "display7seg.h" // Biblioteca de usuário com funções para utilização
			//com o display de 7 segmentos do KIT E-P18 v3.6


/*** DEFINES  ****************************************************************/
	#define CH_1 			PORTAbits.RA1
	#define CH_2 			PORTAbits.RA2
	#define CH_3 			PORTAbits.RA3
	#define CH_4 			PORTAbits.RA4

	#define CONFIG_CH1		TRISAbits.TRISA1 = 1
	#define CONFIG_CH2		TRISAbits.TRISA2 = 1
	#define CONFIG_CH3		TRISAbits.TRISA3 = 1
	#define CONFIG_CH4		TRISAbits.TRISA4 = 1

	#define CONFIG_DIPS()	CONFIG_CH1; CONFIG_CH2; CONFIG_CH3; CONFIG_CH4;

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);
char Ler_Chaves(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa principal,
 *		pois esta é a primeira a ser chamada após o reset do microcontrolador.
 *		Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{ 
	char valorDip;
	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();
	
	// Laço infinito que executa a operação principal do projeto.
	while (1)
	{
            valorDip = Ler_Chaves();
            EscreveDisplay7seg(valorDip,PONTO_NENHUM);
		
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
	ADCON1 |= 0x0F;  //Todos os pinos como I/O digitais.
        
        // Configura os pinos do Kit E-P18 que estão ligados ao display duplo
	// de 7 segmentos chamando a função da biblioteca de usuário.
	ConfiguraDisplay7seg();
	// Configura chave Dip do KIT E-P18
        CONFIG_DIPS();

}//end ConfiguraSistema
char Ler_Chaves(void)
{  	
	char codigo_chaves=0;
// Testa as Chaves
	if(CH_1){codigo_chaves|=0b00001000;}
	if(CH_2){codigo_chaves|=0b00000100;}
	if(CH_3){codigo_chaves|=0b00000010;}
	if(CH_4){codigo_chaves|=0b00000001;}
	return codigo_chaves;
	 
}//end Ler_Chaves


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
