/******************************************************************************
 *
 *           		SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F2550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-Duino nano
 * Prática:	 	Teste Portas
 *
 * Autor:               Bruno A. Dayrell
 * Versão:		v1.0
 * 
 * Descrição:           Inicialização do display LCD alfanumérico no kit
 *                      PICDuino nano. O Firmware escreve uma única vez no
 *                      Display uma mensagem inicial e dentro de um loop fica
 *                      rotacionando a mensagem no Display.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, os modelos 18F4550 e 18F2550
			
			
#include "displayLCD_nano.h"    // Biblioteca desenvolvida pela SEMPRA, que se
                                // Baseia na biblioteca de displays para o kit
                                // de desenvolvimento, adaptada para os pinos
                                // utilizados no kit PICDuino

/************* D E F I N E S ***********************/					

#define Delay_Default()		Delay10KTCYx (250);  \
				Delay10KTCYx (250)
							
#define Inverte_Leds()		LATCbits.LATC0 = !LATCbits.LATC0; \
				LATCbits.LATC1 = !LATCbits.LATC1;

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
	
	
	PosicaoCursorLCD(2,1);
	EscreveFraseRomLCD ("   SEMPRA TEC  ");
	PosicaoCursorLCD(1,1);
        EscreveFraseRomLCD ("  PICDuino NANO   PIC18F2250 ");

	// Laço infinito que executa a operação principal do projeto.
	while (1)	
	{char i=0;  // iniciada como 0 a cada loop
		
	
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);

        // Rotina que rotaciona, inverte o led e aguarda um tempo breve
	while (i<15){
	EscreveComandoLCD(0x18);    // Comando que desloca o testo para a esquerda
	PosicaoCursorLCD(2,1);
	Delay10KTCYx(250);          // Tempo necessário para que o usuário
	Delay10KTCYx(150);          // Perceba a mudança
	
	i++;
	Inverte_Leds();
	}
	
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);

	
        i=0;
        // desloca a mensagem para a posição inicial
	while(i<15){

            // Comando que desloda o texto para a direita.
            EscreveComandoLCD(0x1C);
            i++;

        }
				
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

        // Configuração dos pinos como digitais
	ADCON1 |= 0x0F;

        // Configura como saída os pinos conectados aos Leds
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 = 0;
		
        // Inicialização do LCD
	ConfiguraLCD();

        // Inicialização dos LEDs
        LATCbits.LATC0 = 0;
	LATCbits.LATC1 = 1;
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