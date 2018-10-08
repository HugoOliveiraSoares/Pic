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
 * Plataforma:			Placa SEMPRA E-P32 V1.0
 *
 * Autor:				SEMPRA
 * Versão:				v1.0
 * Descrição:   	Firmware que toca no buzzer a música "Jingle Bells",
 *                      tema de natal. Consta no acionamento e desligamento de
 *                      uma porta digital chaveando o speaker (alto-falante).
 *                      Ligando e desligando no tempo certo, corresponde à
 *                      frequencia da nota musical desejada.
 *
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   03/01/2012 	 Versão inicial - Bruno S. Avelar                      *
 * 1.1   16/02/2012      Revisão        - Bruno A. Dayrell		       *
 ******************************************************************************/



//******* I N C L U D E S ****************************************************/

//#define NOT_BOOTLOADER
#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.

#include "HardwareProfile.h"
#include "Delays.h"

//******* C O N F I G U R A Ç Ã O ********************************************/

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



#define x 25
#define TEMPO_EXECUCAO  300


/**  P R O T O T I P O S   P R I V A D O S ***********************************/

void SystemConfig(); // Configura o estado inicial do sistema.
void Nota (char nota);



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
        // Variáveis contadoras do programa
	char i;
	long j;

        // Vetores que guardam a nota e o tempo de execução dela, respectivamente
	char song[x] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'G', 'C', 'D', 'E',\
      'F', 'F', 'F', 'F', 'F', 'E', 'E', 'E', 'E', 'D', 'D', 'E', 'D', 'G'};
	char length[x] = {1 , 1 , 2  , 1  ,  1 ,  2 ,  1 ,  1 ,  1 ,  1 ,  4 ,\
       1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  2 ,  2};

        // Função de Configuração do sistema
	SystemConfig();
	
	AD1PCFG = 0xffffffff; // Todos pinos como digital

	while (1)
	{
                // loop para cada nota a ser tocada
		for (i=0;i<=25;i++)
		{
                    
                        // loop para a duração da nota tocada
                        // TEMPO_EXECUCAO diz respeito a quantos períodos da
                        // nota que serão tocados.
			for (j=0;j<=(length[i]*TEMPO_EXECUCAO);j++)
			{
                                // chama a função que toca durante 1 período
                                // a nota desejada
				Nota(song[i]);
			}
		}	
	} // end while(1)
}// end main

/******************************************************************************
 *
 * Funcao:    	void nota(char)
 * Entrada:     nota (char) : valor musical da nota a ser tocada.
 * Saída:      	Nenhuma (void)
 * Descrição:   Função do programa que toca a nota passada como parâmetro.
 *              É tocado o equivalente a um período da nota.
 *
 *              As notas podem ser:
 *              'A' - Lá
 *              'B' - Si
 *              'C' - Dó
 *              'D' - Ré
 *              'E' - Mi
 *              'F' - Fá
 *              'G' - Sol
 *
 ***************************************************************************/
void Nota (char nota)
{
	int i;
	switch (nota)
	{
                // Nota 'dó'
		case 'C':
				SPEAKER = 1;
				DelayUsx(409);
				SPEAKER = 0;
				DelayUsx(409);	
		break;

                // Nota 'ré'
		case 'D':
				SPEAKER = 1;
				DelayUsx(364);
				SPEAKER = 0;
				DelayUsx(364);	
		break;

                // Nota 'mi'
		case 'E':
				SPEAKER = 1;
				DelayUsx(328);
				SPEAKER = 0;
				DelayUsx(328);	
		break;

                // Nota 'fá'
		case 'F':
				SPEAKER = 1;
				DelayUsx(307);
				SPEAKER = 0;
				DelayUsx(307);	
		break;

                // Nota 'sol'
		case 'G':
				SPEAKER = 1;
				DelayUsx(273);
				SPEAKER = 0;
				DelayUsx(273);	
		break;

                // Nota 'lá'
		case 'A':
				SPEAKER = 1;
				DelayUsx(409);
				SPEAKER = 0;
				DelayUsx(409);	
		break;

                // Nota 'si'
		case 'B':
				SPEAKER = 1;
				DelayUsx(246);
				SPEAKER = 0;
				DelayUsx(246);	
		break;

                // Nota 'dó' (segunda oitava)
		case 'C2':
				SPEAKER = 1;
				DelayUsx(204);
				SPEAKER = 0;
				DelayUsx(204);	
		break;
	}
}


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

        // Clock do barramento de Periféricos
	mOSCSetPBDIV (OSC_PB_DIV_1);


	// Desabilita a porta de JTAG
        DDPCONbits.JTAGEN = 0;

        // Configuração das portas respectivas.
        // Para mais detalher, ver o arquivo "HardwareProfile.h"
	ConfigAllButtons();     // Configura as portas digitais dos botoes
	ConfigSpeaker();        // Configura a porta digital do buzzer

} // end SystemConfig	
