/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L)-DisplayLCD
 *
 ******************************************************************************
 * Nome do Arquivo:     main_DisplayLCD.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Opção de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 *                      Barramento de Periféricos - 80MHz(interno)
 *
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Prática: 			
 * Plataforma:          Placa SEMPRA E-P32 V1.0
 *
 * Autor:		SEMPRA
 * Versão:		v1.0
 * Descrição:   	Firmware que Inicializa o display LCD alfanumérico,
 *                      exibe uma mensagem de inicialização e em seguida
 *                      fira exibindo na tela variáveis contadoras.
 *                      Exibe um número inteiro com incremento de 1, e um
 *                      número float com incremento de 1.2.
 *
 * Observação:          Foi descoberto um bug na soma de número float, por
 *                      exemplo, 1.200 + 1.200 = 2.3999 , então foi criado um
 *                      método que torna compatível essa soma em float
 *  
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   19/12/2011 	 Versão inicial - Bruno S. Avelar                      *
 * 2.0   16/02/2012      Revisão        - Bruno A. Dayrell		       *
 ******************************************************************************/



/** I N C L U D E S ****************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>    // Biblioteca do compilador que contém algumas 
                        // funções destinadas aos PICS da famílias 32

#include <plib.h>       // Biblioteca do compilador para uso dos periféricos 
                        // do PIC32.

#include "HardwareProfile.h"  // Biblioteca da SEMPRA que contém
                                           // informações e defines de alguns
                                           // dispositivos e periféricos ligados
                                           // às portas do PIC32, presentes no
                                           // kit de desenvolvimento E-P32
#include "Delays.h"
#include "displayLCDconfig.h"
#include "displayLCD.h"


/** C O N F I G U R A Ç Ã O ********************************************/

// Diretiva utilizada para configuração do sistema caso o usuário deseje gravar
// com gravadora própria, sem necessidade do bootloader.
// #define NOT_BOOTLOADER

#ifdef NOT_BOOTLOADER

// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto
// Configuration Bit settings

// Clock da CPU:
// SYSCLK = 80 MHz (8MHz Cristal * FPLLIDIV * FPLLMUL * FPLLODIV)
// SYSCLK = 80 MHz (8MHz * 1/2 * 20 * 1/1)

// Clock do barramento de periféricos:
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


/** D E F I N E S ******************************************************/


/** P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.

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
int main(void)
{	
    // Declaração de variáveis
    char string[16] = "Bruno S. Avelar";
    int contador = 0;
    float num = 0.0;

    SystemConfig();     // Configura as portas e otimiza o desempenho do PIC
   

    // Escrita inicial no Display
    EscreveComandoLCD(DESLIGA_CURSOR);
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(string);
    PosicaoCursorLCD(2,1);
    EscreveFraseConstLCD("Sempra");         // tela inicial

    // Inicialização aguarda 1 segundo (1000ms)
    DelayMsx(1000);

    while(1)   // Laço infinito que executa o principal funcionamento do projeto
    {
        // Sempre que reiniciado o contador.
        LimpaDisplay();

        // Variável incrementadora,
        for(contador = 0; contador<1000;contador++)
        {
                PosicaoCursorLCD(1,1);
                EscreveInteiroLCD(contador);    // Escreve o contador inteiro
                num = (float)contador*1.2;      // atribuição do float
                                
                // Posiciona fixamente as casas decimais do número float
                if (num>1000){
                    PosicaoCursorLCD(1,7);  // posição unidade de milhar
                }
                else if (num>100){
                    PosicaoCursorLCD(1,8);          // posição centena
                    }
                    else if (num>10){
                        PosicaoCursorLCD(1,9);      // posição dezena
                        }
                        else  {
                            PosicaoCursorLCD(1,10); // posição unidade
                        }

                EscreveFloatLCD(num,4); // Função proprietária que escreve
                                        // diretamente um número float no LCD
                                        // para mais informações procure o 
                                        // arquivo displayLCD.h

               // incrementação a cada 500ms
                DelayMsx(500);
        }
        
    } // end while(1)
} // end main

/******************************************************************************
 * Funcao:    	void SystemConfig(void)
 * Entrada:     Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:   Configuração do sistema. Configuração necessária para que o
 *              microcontrolador funcione de acordo com as aplicações
 *              desejadas. Configura os pinos digitais de entrada e saída
 *              e os demais periféricos utilizados no projeto.
 *****************************************************************************/
void SystemConfig()
{
	/* ********************************************************************
        *
        *  Quando o PIC32 é iniciado ele é configurado para:
	* - NO Caching turned on
	* - NO Prefetch buffer enabled
	* - 7 FLASH wait states
	* - 1 SRAM wait states.
	*
	* Todas estas configurações afetam a perfomasse do microcontrolador
	* fazendo que ele funcione significamente mais lento do que o esperado.
	* Para configurar corretamente, utilizamos a função
        * SYSTEMConfigPerformance(80000000);
	* passando o valor do clock da CPU como parametro. Esta função
        * configurará as propriedades de performasse como numero correto de
        * esperas (wait state) da memória Flash e memória RAM e o uso da
        * memória cache.
        *
	**********************************************************************/

        SYSTEMConfigPerformance(80000000);

	mOSCSetPBDIV (OSC_PB_DIV_1);    // Clock do barramento de periféricos


        DDPCONbits.JTAGEN = 0;  // Desabilita a porta de JTAG
        DDPCONbits.TROEN  = 0;  // Desabilita a porta Trace (debug da microchip)
        DDPCONbits.TDOEN  = 0;  // Modo de operação do JTAG (desabilitado)
        ConfiguraLCD();     // Configura e inicializa o Display de LCD alfanumérico
        
} // end SystemConfig()
