/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
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
 * Descrição:   	
 * 
 * 
 * 
 *****************************************************************************/

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

#define RESOLUCAO (3.3/1023.0)
#define num 380
#define CONTMAX 90
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
    char value = 0;
    int result;
    unsigned char cont;


    SystemConfig();  // Configura as portas e otimiza o desempenho do PIC

    AD1PCFG = 0xffffffff; // Todos pinos como digital


    while(1)   // Laço infinito que executa o principal funcionamento do projeto
    {
    	//--------------------------------------------------------------------//		
        //                      Conversão do botao 1                          //
        //--------------------------------------------------------------------//

        result = 0;
	SetChanADC10(ADC_CH0_POS_SAMPLEA_AN5|ADC_CH0_NEG_SAMPLEA_NVREF);
	for(cont = 0; cont < CONTMAX ; cont++)
        {
            AcquireADC10();
            DelayMsx(1);
            ConvertADC10();
            while(BusyADC10()){}
            result += ReadADC10(0);
        }
        result /= CONTMAX;

        if(result > num)
        {
            LED_0 = 1;
        }
        else
        {
            LED_0 = 0;
        }
        //--------------------------------------------------------------------//
        //                      Conversão do botao 2                          //
        //--------------------------------------------------------------------//
        result = 0;
        SetChanADC10(ADC_CH0_POS_SAMPLEA_AN9|ADC_CH0_NEG_SAMPLEA_NVREF);
        for(cont = 0; cont <CONTMAX; cont++)
        {
            AcquireADC10();
            DelayMsx(1);
            ConvertADC10();
            while(BusyADC10())
            {}
            result += ReadADC10(0);
        }
        result /= CONTMAX;
        if(result > num)
        {
            LED_1 = 1;
        }
        else
        {
            LED_1 = 0;
        }
        //--------------------------------------------------------------------//
        //                      Conversão do botao 3                          //
        //--------------------------------------------------------------------//
        result = 0;
        SetChanADC10(ADC_CH0_POS_SAMPLEA_AN14|ADC_CH0_NEG_SAMPLEA_NVREF);
        for(cont = 0; cont <CONTMAX; cont++)
        {
            AcquireADC10();
            DelayMsx(1);
            ConvertADC10();
            while(BusyADC10())
            {}
            result += ReadADC10(0);//Leitura do bufferi
        }
        result /= CONTMAX;

        if(result > num)//Botao 3 foi pressionado
        {
                LED_2 = 1;

        }
        else
        {
                LED_2 = 0;
        }
        //--------------------------------------------------------------------//
        //                      Conversão do botao 4                          //
        //--------------------------------------------------------------------//
        result = 0;
        SetChanADC10(ADC_CH0_POS_SAMPLEA_AN13|ADC_CH0_NEG_SAMPLEA_NVREF);
        for(cont = 0; cont <CONTMAX; cont++)
        {
            AcquireADC10();
            DelayMsx(1);
            ConvertADC10();
            while(BusyADC10())
            {}
            result += ReadADC10(0);
        }
        result /= CONTMAX;

        if(result > num+97)
        {
                LED_3 = 1;

        }
        else
        {
                LED_3 = 0;
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
  
	mOSCSetPBDIV (OSC_PB_DIV_1);

            
        DDPCONbits.JTAGEN = 0;  // Desabilita a porta de JTAG
        ConfigAllLEDs();
        AllLedsOff();

        CloseADC10();
        OpenADC10(ADC_MODULE_ON     	| //Módulo AD energizado.
    		  ADC_IDLE_CONTINUE 	| //Continua funcionando caso a CPU esteja em IDLE
    		  ADC_FORMAT_INTG16 	| //Formatação do resultado em inteiro com sinal
    		  ADC_CLK_MANUAL	| //Clock manual
    		  ADC_AUTO_SAMPLING_OFF | //Desabilita o Auto Sapling
    		  ADC_SAMP_ON		, //Habilita o sample
    		  ADC_VREF_AVDD_AVSS	| //Tensoes de referencia AVDD e AVSS
    		  ADC_OFFSET_CAL_DISABLE| //Sem offset para calibração
    		  ADC_SCAN_OFF		| //Não usar auto select para portas analogicas
    		  ADC_SAMPLES_PER_INT_1 | //Interrupção a cada uma amostra
    		  ADC_ALT_BUF_OFF	| //Desabilita o auto-buffer
    		  ADC_ALT_INPUT_OFF     , //Desabilita o Alternate Input Sample mode
    		  ADC_SAMPLE_TIME_31    | // Auto Sample Time bits
    		  ADC_CONV_CLK_SYSTEM	| // Clock do conversor como o mesmo da CPU
    		  ADC_CONV_CLK_32Tcy    , // Conversao clock em 32 TCY
    		  ENABLE_AN0_ANA 	| // Habilita o canal do terra (leitura de terra descarrega cap)
    		  ENABLE_AN5_ANA	| // Habilita o canal do Botao 2
    		  ENABLE_AN9_ANA	| // Habilita o canal do Botao 3
    		  ENABLE_AN13_ANA       | // Habilita o canal do Botao 4
    		  ENABLE_AN15_ANA	,
    		  SKIP_SCAN_ALL);        // Nenhum canal selecionado para auto scan.


} // end SystemConfig()
