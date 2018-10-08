/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L)-DisplayLCD
 *
 ******************************************************************************
 * Nome do Arquivo:     main_DisplayLCD.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Op��o de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 *                      Barramento de Perif�ricos - 80MHz(interno)
 *
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 * Pr�tica: 			
 * Plataforma:          Placa SEMPRA E-P32 V1.0
 *
 * Autor:		SEMPRA
 * Vers�o:		v1.0
 * Descri��o:   	Firmware que Inicializa o display LCD alfanum�rico,
 *                      exibe uma mensagem de inicializa��o e em seguida
 *                      fira exibindo na tela vari�veis contadoras.
 *                      Exibe um n�mero inteiro com incremento de 1, e um
 *                      n�mero float com incremento de 1.2.
 *
 * Observa��o:          Foi descoberto um bug na soma de n�mero float, por
 *                      exemplo, 1.200 + 1.200 = 2.3999 , ent�o foi criado um
 *                      m�todo que torna compat�vel essa soma em float
 *  
 *******************************************************************************
 * *****************************************************************************
 * Log de modifica��es:							       *
 * Rev   Data         Descri��o						       *
 * 1.0   19/12/2011 	 Vers�o inicial - Bruno S. Avelar                      *
 * 2.0   16/02/2012      Revis�o        - Bruno A. Dayrell		       *
 ******************************************************************************/



/** I N C L U D E S ****************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>    // Biblioteca do compilador que cont�m algumas 
                        // fun��es destinadas aos PICS da fam�lias 32

#include <plib.h>       // Biblioteca do compilador para uso dos perif�ricos 
                        // do PIC32.

#include "HardwareProfile.h"  // Biblioteca da SEMPRA que cont�m
                                           // informa��es e defines de alguns
                                           // dispositivos e perif�ricos ligados
                                           // �s portas do PIC32, presentes no
                                           // kit de desenvolvimento E-P32
#include "Delays.h"
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


/** D E F I N E S ******************************************************/


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

    // Inicializa��o aguarda 1 segundo (1000ms)
    DelayMsx(1000);

    while(1)   // La�o infinito que executa o principal funcionamento do projeto
    {
        // Sempre que reiniciado o contador.
        LimpaDisplay();

        // Vari�vel incrementadora,
        for(contador = 0; contador<1000;contador++)
        {
                PosicaoCursorLCD(1,1);
                EscreveInteiroLCD(contador);    // Escreve o contador inteiro
                num = (float)contador*1.2;      // atribui��o do float
                                
                // Posiciona fixamente as casas decimais do n�mero float
                if (num>1000){
                    PosicaoCursorLCD(1,7);  // posi��o unidade de milhar
                }
                else if (num>100){
                    PosicaoCursorLCD(1,8);          // posi��o centena
                    }
                    else if (num>10){
                        PosicaoCursorLCD(1,9);      // posi��o dezena
                        }
                        else  {
                            PosicaoCursorLCD(1,10); // posi��o unidade
                        }

                EscreveFloatLCD(num,4); // Fun��o propriet�ria que escreve
                                        // diretamente um n�mero float no LCD
                                        // para mais informa��es procure o 
                                        // arquivo displayLCD.h

               // incrementa��o a cada 500ms
                DelayMsx(500);
        }
        
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

	mOSCSetPBDIV (OSC_PB_DIV_1);    // Clock do barramento de perif�ricos


        DDPCONbits.JTAGEN = 0;  // Desabilita a porta de JTAG
        DDPCONbits.TROEN  = 0;  // Desabilita a porta Trace (debug da microchip)
        DDPCONbits.TDOEN  = 0;  // Modo de opera��o do JTAG (desabilitado)
        ConfiguraLCD();     // Configura e inicializa o Display de LCD alfanum�rico
        
} // end SystemConfig()
