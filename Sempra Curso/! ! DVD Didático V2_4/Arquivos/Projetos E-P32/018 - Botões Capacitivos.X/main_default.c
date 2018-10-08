/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L)
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
 * Plataforma:          Placa SEMPRA E-P32 V1.0
 *
 * Autor:		SEMPRA
 * Vers�o:		v1.0
 * Descri��o:   	
 * 
 * 
 * 
 *****************************************************************************/

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

#define RESOLUCAO (3.3/1023.0)
#define num 380
#define CONTMAX 90
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
    char value = 0;
    int result;
    unsigned char cont;


    SystemConfig();  // Configura as portas e otimiza o desempenho do PIC

    AD1PCFG = 0xffffffff; // Todos pinos como digital


    while(1)   // La�o infinito que executa o principal funcionamento do projeto
    {
    	//--------------------------------------------------------------------//		
        //                      Convers�o do botao 1                          //
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
        //                      Convers�o do botao 2                          //
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
        //                      Convers�o do botao 3                          //
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
        //                      Convers�o do botao 4                          //
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
        ConfigAllLEDs();
        AllLedsOff();

        CloseADC10();
        OpenADC10(ADC_MODULE_ON     	| //M�dulo AD energizado.
    		  ADC_IDLE_CONTINUE 	| //Continua funcionando caso a CPU esteja em IDLE
    		  ADC_FORMAT_INTG16 	| //Formata��o do resultado em inteiro com sinal
    		  ADC_CLK_MANUAL	| //Clock manual
    		  ADC_AUTO_SAMPLING_OFF | //Desabilita o Auto Sapling
    		  ADC_SAMP_ON		, //Habilita o sample
    		  ADC_VREF_AVDD_AVSS	| //Tensoes de referencia AVDD e AVSS
    		  ADC_OFFSET_CAL_DISABLE| //Sem offset para calibra��o
    		  ADC_SCAN_OFF		| //N�o usar auto select para portas analogicas
    		  ADC_SAMPLES_PER_INT_1 | //Interrup��o a cada uma amostra
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
