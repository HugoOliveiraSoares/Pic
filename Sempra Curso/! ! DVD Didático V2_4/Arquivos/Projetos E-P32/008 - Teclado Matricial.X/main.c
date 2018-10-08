/******************************************************************************
 *
 *               SEMPRA PROJETOS (PIC32MX775F512L) - Teclado Matricial
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
 * Plataforma:			Placa SEMPRA E-P32 V1.0
 *
 * Autor:				Bruno Avelar
 * Vers�o:				v1.0
 * Descri��o:   	Firmware que faz a varredura da matriz de teclados e
 *                      mostra no display de 7segmentos o bot�o correspondente
 *                      que foi pressionado. Caso nenhum bot�o esteja
 *                      pressionado, n�o � exibido nenhum valor na tela.
 *
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

// Bibliotecas da Sempra
#include "HardwareProfile.h"
#include "display_7seg.h"
#include "Delays.h"
#include "teclado.h"

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
    int cont = 99;

    SystemConfig();     // Configura as portas e otimiza o desempenho do PIC

    // Define o TRISTATE das portas (linhas e colunas)

   CONFIG_LINHA_0 = 1;
   CONFIG_LINHA_1 = 1;
   CONFIG_LINHA_2 = 1;

   CONFIG_COLUNA_0 = 0;
   CONFIG_COLUNA_1 = 0;
   CONFIG_COLUNA_2 = 0;
   CONFIG_COLUNA_3 = 0;

    while(1)   // La�o infinito que executa o principal funcionamento do projeto            
    {
            Limpa_Matriz_Teclado();     // Limpa o vetor com a informa��o
            Interrupcao_Teclado ();     // Executa a leitura da matriz
            UpdateDisplay7Seg();        // Atualiza o display 7 seg
            DelayMsx(1);                // Delay 1ms
            
            cont = Numero_Teclado();    // vari�vel que recebe qual n�mero
                                        //                 foi pressionado
            // se h� alguma tecla pressionada
            if(cont != 99)              // 99 � o valor default enviado
            {
                // A��es a serem executadas caso seja apertado um n�mero
                EscreveDisplay7Seg(cont,0); // escreve no display o n�mero
            }

            // Caso nenhuma tecla pressionada, essa ser� a mensagem de "erro"
            // EstadoEspera significa que � o modo como o display fica enquanto
            // n�o est� mandando nenhum n�mero ser escrito nele. Esta deve ser
            // uma tarefa do programador.
            else
            {
                EstadoEspera7Seg();     // Escreve " - - - - " no Display
            }
            

            UpdateDisplay7Seg();        // Atualiza display de 7 segmentos
            DelayMsx(1);


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

	// Desabilita a porta de JTAG
        DDPCONbits.JTAGEN = 0;

        // Configura o Display de 7 segmentos
        ConfigDisplay7Seg();

         //Configura o teclado matricial.
        Inicializa_Teclado();


} // end SystemConfig()
