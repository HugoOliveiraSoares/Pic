/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L)-PS/2
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Op��o de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 *                      Barramento de Perif�ricos - 80MHz(interno)
 *
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Pr�tica:
 * Plataforma:			Placa SEMPRA E-P32 V1.0
 *
 * Autor:				SEMPRA
 * Vers�o:				v1.0
 * Descri��o:   Firmware que l� um teclado com entrada PS/2 e escreve na
 *              tela do display LCD alfanum�rico o d�gito correspondente.	
 *
 * 			H A R D W A R E:
 *
 *  			Conector Femea:		Pinos | Porta | Fun��o
 *                                        1      RB1    Teclado Data
 *      	6 [] 5			  2      RB3	MOUSE (NAO UTILIZADO)
 *             4      3                   3       - 	GND
 *                                        4       -	VCC
 *            	 2  1                     5      RB0	Telcado Clock
 *                                        6      RB2	MOUSE (NAO UTILIZADO)
 *
 *                      F I R M W A R E:
 *
 *		Estados do barramentos:
 *
 *		Data 5V, Clock 5V - Idle
 *		Data 5V, Clock 0V - Impede comunica��o
 *		Data 0V, Clock 5V - PIC �requisita envio de dados
 *
 *		Comunica��o Telcado -> PIC
 *
 *		1 start bit.  Sempre 0 (Pode ser usado para ativar interrup��o).
 *		8 data bits, Menos significante primeiro.
 *		1 bit de paridade (paridade �mpar
 *		1 stop bit.  Sempre 1.
 *
 *****************************************************************************/

/** I N C L U D E S ****************************************************/


#include <p32xxxx.h>    // Biblioteca do compilador que cont�m algumas
                        // fun��es destinadas aos PICS da fam�lias 32

#include <plib.h>       // Biblioteca do compilador para uso dos perif�ricos
                        // do PIC32.

#include "HardwareProfile.h"  // Biblioteca da SEMPRA que cont�m
                                           // informa��es e defines de alguns
                                           // dispositivos e perif�ricos ligados
                                           // �s portas do PIC32, presentes no
                                           // kit de desenvolvimento E-P32

#include "tecladoPS2.h"     // Biblioteca da SEMPRA que cont�m configura��es e
                            // fun��es que proporcionam a comunica��o entre o
                            // kit E-P32 e um teclado perif�rico.

#include "displayLCDconfig.h"
#include "displayLCD.h"

/** C O N F I G U R A � � O ********************************************/

// Diretiva utilizada para configura��o do sistema caso o usu�rio deseje gravar
// com gravadora pr�pria, sem necessidade do bootloader.
// #define NOT_BOOTLOADER

#ifdef NOT_BOOTLOADER

// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto
// Configuration Bit settings

// Clock da CPU:
// SYSCLK = 80 MHz (8MHz Cristal * FPLLIDIV * FPLLMUL * FPLLODIV)
// SYSCLK = 80 MHz (8MHz * 1/2 * 20 * 1/1)

// Clock do barramento de perif�ricos:
// PBCLK = 10 MHz (SYSCLK * 1/FPBDIV)
// PBCLK = 10 MHz (80MHz * 1/8)

// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF

#pragma config FPLLMUL    = MUL_20
#pragma config FPLLIDIV   = DIV_2
#pragma config FPLLODIV   = DIV_1
#pragma config FWDTEN     = OFF
#pragma config POSCMOD    = HS
#pragma config FNOSC      = PRIPLL
#pragma config FPBDIV     = DIV_1

#pragma config CP         = OFF    // Code Protect
#pragma config BWP        = OFF    // Boot Flash Write Protect
#pragma config PWP        = OFF    // Program Flash Write Protect

#endif


/** D E F I N E S ***********************************************************/


/** VARI�VEIS GLOBAIS *******************************************************/


/** P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.

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
int main(void)
{
    // Declara��o de vari�veis
    char letra;
    int i;

    SystemConfig();     // Configura as portas e otimiza o desempenho do PIC
    ConfiguraLCD();     // Configura e inicializa o Display de LCD alfanum�rico
    AD1PCFG = 0xffffffff; // Todos pinos como digital

    while(1)   // La�o infinito que executa o principal funcionamento do projeto
    {
        while(PS2_DATAPIN){}

        // Verifica��o da condi��o de permitir leitura do teclado
        if(!PS2_DATAPIN)
                    {
                            letra = LeDadoTeclado();
                    }
        DelayMsx(30);
                    // Tratamento do caractere que verifica se n�o � nenhum
                    // caractere de erro e tamb�m se n�o � alguma tecla especial
                    // como exemplo, backspace ou enter.
		if(letra!= MISSMATCH_ERRO && letra!= TIMEOUT_ERRO && letra!= PARIDADE_ERRO )
		{
			if(letra == 0x0D)//Enter
			{
                                // In�cio da 2� Linha
				PosicaoCursorLCD(2,1);
			}
			else
			{
				if(letra == 0x08) // Backspace
				{
                                        // Backspace = limpa todo o display
					LimpaDisplay();
				}
				else
				{
                                        // Escreve o caractere no display LCD
					EscreveCaractereLCD(letra);
				}
			}
		} // fim do tratamento do caractere

    } // end while(1)
} // end main

/******************************************************************************
 * Funcao:    	void SystemConfig(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Configura��o do sistema. Configura��o necess�ria para que o
 *              microcontrolador funcione de acordo com as aplica��es
 *              desejadas. Configura os pinos digitais de entrada e sa�da
 *              e os demais perif�ricos utilizados no projeto.
 *****************************************************************************/
void SystemConfig()
{
	/* ********************************************************************
        *
        *  Quando o PIC32 � iniciado ele � configurado para:
	* - NO Caching turned on
	* - NO Prefetch buffer enabled
	* - 7 FLASH wait states
	* - 1 SRAM wait states.
	*
	* Todas estas configura��es afetam a perfomasse do microcontrolador
	* fazendo que ele funcione significamente mais lento do que o esperado.
	* Para configurar corretamente, utilizamos a fun��o
        * SYSTEMConfigPerformance(80000000);
	* passando o valor do clock da CPU como parametro. Esta fun��o
        * configurar� as propriedades de performasse como numero correto de
        * esperas (wait state) da mem�ria Flash e mem�ria RAM e o uso da
        * mem�ria cache.
        *
	**********************************************************************/

        SYSTEMConfigPerformance(80000000);

	mOSCSetPBDIV (OSC_PB_DIV_1);

        DDPCONbits.JTAGEN = 0;  // Desabilita a porta de JTAG

        /*
        #define CLOCKPIN_CONFIG TRISAbits.TRISA10
        #define DATAPIN_CONFIG  TRISAbits.TRISA15
        */

} // end SystemConfig()
