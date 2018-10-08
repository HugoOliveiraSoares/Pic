/******************************************************************************
 *
 *           		SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F2550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-Duino nano
 * Pr�tica:	 	Teste Portas
 *
 * Autor:               Bruno A. Dayrell
 * Vers�o:		v1.0
 * 
 * Descri��o:           Inicializa��o do display LCD alfanum�rico no kit
 *                      PICDuino nano. O Firmware escreve uma �nica vez no
 *                      Display uma mensagem inicial e dentro de um loop fica
 *                      rotacionando a mensagem no Display.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
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
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *		pois esta � a primeira a ser chamada ap�s o	reset do 
 *		microcontrolador.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/



void main (void){
	// Configura as portas e perif�ricos do PIC.
	ConfiguraSistema();
	
	
	PosicaoCursorLCD(2,1);
	EscreveFraseRomLCD ("   SEMPRA TEC  ");
	PosicaoCursorLCD(1,1);
        EscreveFraseRomLCD ("  PICDuino NANO   PIC18F2250 ");

	// La�o infinito que executa a opera��o principal do projeto.
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
	Delay10KTCYx(250);          // Tempo necess�rio para que o usu�rio
	Delay10KTCYx(150);          // Perceba a mudan�a
	
	i++;
	Inverte_Leds();
	}
	
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);

	
        i=0;
        // desloca a mensagem para a posi��o inicial
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
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	ConfiguraSistema � a rotina de configura��o principal do projeto.
 *		Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *		do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{

        // Configura��o dos pinos como digitais
	ADCON1 |= 0x0F;

        // Configura como sa�da os pinos conectados aos Leds
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 = 0;
		
        // Inicializa��o do LCD
	ConfiguraLCD();

        // Inicializa��o dos LEDs
        LATCbits.LATC0 = 0;
	LATCbits.LATC1 = 1;
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