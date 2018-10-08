/******************************************************************************
 *
 *              SEMPRA PROJETOS (PIC32MX775F512L) - Sensores Display 7 Segmentos
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Op��o de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 *                      Barramento de Perif�ricos - 80MHz(interno)
 *
 * Compilador:        	C32 v 1.01
 * Empresa:         	SEMPRA
 * Pr�tica: 			
 * Plataforma:		Placa SEMPRA E-P32 V1.0
 *
 * Autor:		Bruno Avelar
 * Vers�o:		v1.0
 * Descri��o:   	De acordo com o bot�o pressionado, Faz a medida da tens�o
 *                      do potenciometro, da temperatura ou do do LDR, mostrando
 *			o valor correspondente no display de 7 segmentos da placa
 *                      de desenvolvimento.
 * *****************************************************************************
 *
 * *****************************************************************************
 * Log de modifica��es:							       *
 * Rev   Data         Descri��o						       *
 * 1.0   02/01/2012 	Vers�o inicial - Bruno S. Avelar		       *
 * 1.1   15/02/2012     Revis�o        - Bruno A. Dayrell
 ******************************************************************************/
//******* I N C L U D E S ****************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.

#include "HardwareProfile.h"
#include "Delays.h"


/******* C O N F I G U R A � � O ********************************************/

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


/******* D E F I N E S ******************************************************/

// Resolu��o da Convers�o A/D
#define RESOLUCAO (3.3/1023.0)

/**  P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.


/** F U N C O E S ************************************************************/

/******************************************************************************
 *
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Inteiro (int): a fun��o main pode retornar algum par�metro para
 *              a mem�ria interna de 12K reservada do PIC32 para boot
 *              (boot flash memory).
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *		pois esta � a primeira a ser chamada ap�s o	reset do
 *		microcontrolador.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *
 *****************************************************************************/
int main(void)
{
        // vari�veis que ser�o utilizadas para leitura dos bot�es e
        // escrita no display 7 segmentos
	unsigned int result;		
	char option = 0;
	
        SystemConfig();     // Configura as portas e otimiza o desempenho do PIC
	
        // Configura��o e habilita��o do conversor AD 
        EnableADC10();
	SetChanADC10(ADC_CH0_POS_SAMPLEA_AN2|ADC_CH0_NEG_SAMPLEA_NVREF);

    while(1)   // La�o infinito que executa o principal funcionamento do projeto
                 
    {
                // Fun��o necess�ria para atualiza��o do valor no display 7segmentos
                UpdateDisplay7Seg();

                // Se pressionado o bot�o 1
                if(BUTTON_1)
                {
                        option = 0;
                }
                // Se pressionado o bot�o 2
                if(BUTTON_2)
                {
                        option = 1;
                }
                // Se pressionado o bot�o 3
                if(BUTTON_3)
                {
                        option = 2;
                }
                // Se pressionado o bot�o 4
                if(BUTTON_4)
                {
                    option = 3;
                }

                // Ser� convertido a entrada anal�gica correspondente ao bot�o pressionado
                // O switch � respons�vel por escolher a a��o de acordo com o �ltimo bot�o pressionado
                switch(option)
                {
                        case 0: //POTENCIOMETRO -> BOTAO1

                                        // Configura o ADC para o canal do Potenci�metro
                                        // AN2 � a amostra A | Terra � a refer�ncia negativa
                                        SetChanADC10(ADC_CH0_POS_SAMPLEA_AN2|ADC_CH0_NEG_SAMPLEA_NVREF);
                                        AcquireADC10();
                                        ConvertADC10();
                                        while(BusyADC10())
                                        {
                                                DelayMsx(1);
                                                UpdateDisplay7Seg();
                                        }
                                        result = ReadADC10(0);//Leitura do bufferi
                                        result = result * (RESOLUCAO * 100);
                                        EscreveDisplay7Seg(result,0b00000010);
                        break;

                        case 1: //TEMPERATURA -> BOTAO2

                                        // Configura o ADC para o canal do Sensor
                                        // AN4 � a amostra A | Terra � a refer�ncia negativa
                                        SetChanADC10(ADC_CH0_POS_SAMPLEA_AN4|ADC_CH0_NEG_SAMPLEA_NVREF);
                                        AcquireADC10();
                                        ConvertADC10();
                                        while(BusyADC10())
                                        {
                                                DelayMsx(1);
                                                UpdateDisplay7Seg();
                                        }
                                        result = ReadADC10(0);//Leitura do bufferi
                                        result = ((result * RESOLUCAO/ 0.010) - 50) * 10 ;
                                        EscreveDisplay7Seg(result,0b00000100);
                        break;

                        case 2: //LUMINOSIDADE -> BOTAO3

                                        // Configura o ADC para o canal do LDR
                                        // AN3 � a amostra A | Terra � a refer�ncia negativa
                                        SetChanADC10(ADC_CH0_POS_SAMPLEA_AN3|ADC_CH0_NEG_SAMPLEA_NVREF);
                                        AcquireADC10();
                                        ConvertADC10();
                                        while(BusyADC10())
                                        {
                                                DelayMsx(1);
                                                UpdateDisplay7Seg();
                                        }
                                        result = ReadADC10(0);//Leitura do bufferi
                                        result = result * (RESOLUCAO * 100);
                                        EscreveDisplay7Seg(result,0b0000010);
                        break;

                        case 3: //BINARIO do atual -> BOTAO4

                                        // Manda Converter, independente do canal configurado anteriormente
                                        AcquireADC10();
                                        ConvertADC10();
                                        while(BusyADC10())
                                        {
                                                DelayMsx(1);
                                                UpdateDisplay7Seg();
                                        }
                                        result = ReadADC10(0);//Leitura do bufferi
                                        EscreveDisplay7Seg(result,0b00000000);
                        break;

                } // end switch

                DelayMsx(1);
                UpdateDisplay7Seg();

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


	// Desabilita a porta de JTAG
        DDPCONbits.JTAGEN = 0;

        // Configura o Display de 7 segmentos
        ConfigDisplay7Seg();

        // Configura o Conversor A/D
	CloseADC10();

        OpenADC10(ADC_MODULE_ON     	| // M�dulo AD energizado.
    		  ADC_IDLE_CONTINUE 	| // Continua funcionando caso a CPU esteja em IDLE
    		  ADC_FORMAT_INTG16 	| // Formata��o do resultado em inteiro com sinal
    		  ADC_CLK_MANUAL	| // Clock manual
    		  ADC_AUTO_SAMPLING_OFF | // Desabilita o Auto Sapling
    		  ADC_SAMP_ON		, // Habilita o sample
    		  ADC_VREF_AVDD_AVSS	| // Tensoes de referencia AVDD e AVSS
    		  ADC_OFFSET_CAL_DISABLE| // Sem offset para calibra��o
    		  ADC_SCAN_OFF		| // N�o usar auto select para portas analogicas
    		  ADC_SAMPLES_PER_INT_1 | // Interrup��o a cada uma amostra
    		  ADC_ALT_BUF_OFF	| // Desabilita o auto-buffer
    		  ADC_ALT_INPUT_OFF	, // Desabilita o Alternate Input Sample mode
    		  ADC_SAMPLE_TIME_31    | // Auto Sample Time bits
    		  ADC_CONV_CLK_SYSTEM	| // Clock do conversor como o mesmo da CPU
    		  ADC_CONV_CLK_32Tcy    , // Conversao clock em 32 TCY
    		  ENABLE_AN4_ANA 	| // Habilita o canal do sensor de temperatura
    		  ENABLE_AN3_ANA	| // Habilita o canal do potenciometro
    		  ENABLE_AN2_ANA	, // Habilita o canal do LDR
    		  SKIP_SCAN_ALL);	  // Nenhum canal selecionado para auto scan.

}		
