/******************************************************************************
 *
 *              SEMPRA PROJETOS (PIC32MX775F512L) - Sensores Display 7 Segmentos
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC32MX775F512L
 * Opção de Clock:	HS 8MHz (externo) - CPU:80MHz (interno)
 *                      Barramento de Periféricos - 80MHz(interno)
 *
 * Compilador:        	C32 v 1.01
 * Empresa:         	SEMPRA
 * Prática: 			
 * Plataforma:		Placa SEMPRA E-P32 V1.0
 *
 * Autor:		Bruno Avelar
 * Versão:		v1.0
 * Descrição:   	De acordo com o botão pressionado, Faz a medida da tensão
 *                      do potenciometro, da temperatura ou do do LDR, mostrando
 *			o valor correspondente no display de 7 segmentos da placa
 *                      de desenvolvimento.
 * *****************************************************************************
 *
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   02/01/2012 	Versão inicial - Bruno S. Avelar		       *
 * 1.1   15/02/2012     Revisão        - Bruno A. Dayrell
 ******************************************************************************/
//******* I N C L U D E S ****************************************************/

//#define NOT_BOOTLOADER

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.

#include "HardwareProfile.h"
#include "Delays.h"


/******* C O N F I G U R A Ç Ã O ********************************************/

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


/******* D E F I N E S ******************************************************/

// Resolução da Conversão A/D
#define RESOLUCAO (3.3/1023.0)

/**  P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.


/** F U N C O E S ************************************************************/

/******************************************************************************
 *
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:      	Inteiro (int): a função main pode retornar algum parâmetro para
 *              a memória interna de 12K reservada do PIC32 para boot
 *              (boot flash memory).
 * Descrição:   Função principal do programa. O termo "main" significa principal,
 *		pois esta é a primeira a ser chamada após o	reset do
 *		microcontrolador.
 *		Todas as outras funções sao chamadas a partir da "main".
 *
 *****************************************************************************/
int main(void)
{
        // variáveis que serão utilizadas para leitura dos botões e
        // escrita no display 7 segmentos
	unsigned int result;		
	char option = 0;
	
        SystemConfig();     // Configura as portas e otimiza o desempenho do PIC
	
        // Configuração e habilitação do conversor AD 
        EnableADC10();
	SetChanADC10(ADC_CH0_POS_SAMPLEA_AN2|ADC_CH0_NEG_SAMPLEA_NVREF);

    while(1)   // Laço infinito que executa o principal funcionamento do projeto
                 
    {
                // Função necessária para atualização do valor no display 7segmentos
                UpdateDisplay7Seg();

                // Se pressionado o botão 1
                if(BUTTON_1)
                {
                        option = 0;
                }
                // Se pressionado o botão 2
                if(BUTTON_2)
                {
                        option = 1;
                }
                // Se pressionado o botão 3
                if(BUTTON_3)
                {
                        option = 2;
                }
                // Se pressionado o botão 4
                if(BUTTON_4)
                {
                    option = 3;
                }

                // Será convertido a entrada analógica correspondente ao botão pressionado
                // O switch é responsável por escolher a ação de acordo com o último botão pressionado
                switch(option)
                {
                        case 0: //POTENCIOMETRO -> BOTAO1

                                        // Configura o ADC para o canal do Potenciômetro
                                        // AN2 é a amostra A | Terra é a referência negativa
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
                                        // AN4 é a amostra A | Terra é a referência negativa
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
                                        // AN3 é a amostra A | Terra é a referência negativa
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


	// Desabilita a porta de JTAG
        DDPCONbits.JTAGEN = 0;

        // Configura o Display de 7 segmentos
        ConfigDisplay7Seg();

        // Configura o Conversor A/D
	CloseADC10();

        OpenADC10(ADC_MODULE_ON     	| // Módulo AD energizado.
    		  ADC_IDLE_CONTINUE 	| // Continua funcionando caso a CPU esteja em IDLE
    		  ADC_FORMAT_INTG16 	| // Formatação do resultado em inteiro com sinal
    		  ADC_CLK_MANUAL	| // Clock manual
    		  ADC_AUTO_SAMPLING_OFF | // Desabilita o Auto Sapling
    		  ADC_SAMP_ON		, // Habilita o sample
    		  ADC_VREF_AVDD_AVSS	| // Tensoes de referencia AVDD e AVSS
    		  ADC_OFFSET_CAL_DISABLE| // Sem offset para calibração
    		  ADC_SCAN_OFF		| // Não usar auto select para portas analogicas
    		  ADC_SAMPLES_PER_INT_1 | // Interrupção a cada uma amostra
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
