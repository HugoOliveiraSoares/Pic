/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L) - PWM SPEAKER
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
 * Plataforma:		Placa SEMPRA E-P32 V1.0
 *
 * Autor:		SEMPRA
 * Versão:		v1.0
 * Descrição:   	Emite som no Speaker através de uma saida PWM. a saída
 *                      possui maior precisão, associada ao Timer3, garantindo
 *                      o período da onda. O firmware gera a onda com periodo
 *                      fixo e varia o período, sendo possível observar assim o
 *                      efeito audível que possui.
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

#include "HardwareProfile.h" // Biblioteca da SEMPRA que contém
                                           // informações e defines de alguns
                                           // dispositivos e periféricos ligados
                                           // às portas do PIC32, presentes no
                                           // kit de desenvolvimento E-P32

#include "Delays.h"     // Biblioteca da SEMPRA que contém as funções capazes
                        // de gerar o atraso desejado através de espera ocupada.
                        // Desenvolvida especialmente para o PIC32MX com clock
                        // interno de 80MHz.
                        // Para mais informações, abra o header "Delays.h".

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


/** D E F I N E S ***********************************************************/


/** VARIÁVEIS GLOBAIS *******************************************************/


/** P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.

/** F U N C O E S ***********************************************************/


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
    int i = 326;

    // Configuração do sistema e otimização do desempenho
    SystemConfig();

    // Configuração do periférico Timer 3
    OpenTimer3( T3_ON|
                T3_PS_1_256,
                652);

    // Configuração do periférico Output Compare 2
    OpenOC2(    OC_ON |
                OC_TIMER_MODE16 |
                OC_TIMER3_SRC |
                OC_PWM_FAULT_PIN_DISABLE ,
                326,
                326 );


    while (1)   // Laço principal do programa
            {

                if (PORTDbits.RD5)
                {
                    PORTGbits.RG15 = 1;
                    DelayMsx(10);
                    i++;
                    SetDCOC2PWM(i);
                        if (i == 650)
                        {
                                i = 0;
                        }
                }
                PORTGbits.RG15 = 0;


                if (PORTDbits.RD7)
                {
                    PORTCbits.RC1 = 1;
                    DelayMsx(10);
                    i--;
                    SetDCOC2PWM(i);
                        if (i == 1)
                        {
                            i = 650;
                        }
                }
                PORTCbits.RC1 = 0;

                // while responsável por variar o Duty Cicle
                while (PORTDbits.RD7 & PORTDbits.RD5)
                {
                    DelayMsx(5);
                    i++;
                    SetDCOC2PWM(i);
                    if (i == 650)
                    {
                        i = 0;
                    }
                }

    } // end while(1)
    return 0;
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

	mOSCSetPBDIV (OSC_PB_DIV_1);    // Barramento de Periféricos = 80MHz
	
	AD1PCFG = 0xffffffff; // Todos os pinos como digital
	
	TRISDbits.TRISD5  = 1;
	TRISDbits.TRISD7  = 1;
	TRISGbits.TRISG15  = 0;
	TRISCbits.TRISC1   = 0;

} // end SystemConfig
