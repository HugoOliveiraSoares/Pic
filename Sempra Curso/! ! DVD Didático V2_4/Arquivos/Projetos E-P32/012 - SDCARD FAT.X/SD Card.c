/*******************************************************************************
 *                  SEMPRA  E-P32 Acende LED    			       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     SD Card.c                                              *
 * Dependencias:    	Veja a seção INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Opção de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.0                                                   *
 * Descrição:        	Este firmware cria arquivos e diretórios em um cartao  *
 *                      SD conectado ao KIT. Ao conectar o cartão SD ao        *
 *                      KIT E-P32, será criado um diretório TE e dentro deste  *
 *                      outro com nome Tep (\\Te\\Tep) e após um arquivo       *
 *                      Tempt.txt. O programa fará 20 aquisiçÕes de temperatura*
 *                      e escreverá os valores obtidos no arquivo. Apos este   *
 *                      arquivo será fechado e o usuário poderá ver os dados em*
 *                      seu computador.                                        *
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   31/01/2012 	 Versão inicial - Bruno S. Avelar		       *
 ******************************************************************************/

#define NOT_BOOTLOADER


#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include <string.h>

#include "HardwareProfile.h"
#include "MDD File System/FSIO.h"
#include "Delays.h"




#ifdef NOT_BOOTLOADER
// Desanexe o arquivo app_hid_boot_PIC32MX775F256L do seu projeto
// Configuration Bit settings

// Clock da CPU:
// SYSCLK = 80 MHz (8MHz Cristal * FPLLIDIV * FPLLMUL * FPLLODIV)
// SYSCLK = 80 MHz (8MHz * 1/2 * 20 * 1/1)

// Clock do barramento de periféricos:
// PBCLK = 80 MHz (SYSCLK * 1/FPBDIV)
// PBCLK = 80 MHz (80MHz * 1/1)

// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF


    #pragma config FPLLMUL  = MUL_20        // PLL Multiplier
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = OFF            // Background Debugger Enable

#endif

/**  P R O T O T I P O S   P R I V A D O S *********************************/

void SystemConfig(); // Configura o estado inicial do sistema.

char *itoaS(int value);

/***************************************************************************/
/**  V A R I A V E I S    G L O B A I S ************************************/

char *sendBuffer;
char send2[] = "2";
char receiveBuffer[50];

/***************************************************************************/
/**  D E F I N E S *********************************************************/
#define RESOLUCAO (3.3/1023.0)


/***************************************************************************/

/*
 *
 *
 *
 */
int main (void)
{
   FSFILE * pointer;
   unsigned int result;		

   SystemConfig();
   
   LED_0_Off();
   LED_1_Off();
   LED_2_Off();
   LED_3_Off();
   LED_4_Off();
   LED_5_Off();
   LED_6_Off();
   LED_7_Off();
   
   
   LED_0_On();

   while (1)
   {   

	  
	   
      if (FSmkdir(".\\Te\\Tep")) // Criar diretório Temperatura
      {
	      while(1)
	      {
	  	     	LED_4_Toggle();
		 		long i = 0;
				for(i=0; i< 655360 ; i++)
				{
				}
	
		  }    
	   }
	   FSchdir(".\\Te\\Tep");
	   

	   pointer = FSfopen ("tempt.txt", "w");  // Abrir  o arquivo
	   if (pointer == NULL)
       while(1)
       {
	    	LED_6_Toggle();
			long j = 0;
			 for(j=0; j< 655360 ; j++)
			 {
			 } 		       
	   } 


	   int l;   
	   
	   for(l = 0; l < 20; l++) //Faz 20 conversoes AD e grava no arquivo Temperatura.txt no diretorio temperatura log.
	   {
		  
		   
			SetChanADC10(ADC_CH0_POS_SAMPLEA_AN4|ADC_CH0_NEG_SAMPLEA_NVREF);	
			AcquireADC10();
			ConvertADC10();
			
			LED_4_Toggle();
			
			while(BusyADC10())
			{
			}
			result = ReadADC10(0);//Leitura do bufferi
			result = ((result * RESOLUCAO/ 0.010) - 50) ;
			
			sendBuffer = itoaS(result);
               
			//Grava no arquivo.
			if (FSfwrite (sendBuffer, 1, (int) strlen(sendBuffer), pointer) != (int) strlen(sendBuffer))
 			{   
      			while(1)
      			{
	      	 		LED_1_Toggle();
			 		long i = 0;
			 		for(i=0; i< 655360 ; i++)
			 		{
			 		} 		       
	  			} 
   			}
   			
   			sendBuffer[0] = ';';
   			sendBuffer[1] = 0;
   			
   			if (FSfwrite (sendBuffer, 1, (int) strlen(sendBuffer), pointer) != (int) strlen(sendBuffer))
 			{   
      			while(1)
      			{
	      	 		LED_1_Toggle();
			 		long i = 0;
			 		for(i=0; i< 655360 ; i++)
			 		{
			 		} 		       
	  			} 
   			}
   			
   			DelayMsx(900);
		}
	   
	   // fecha o arquivo.
	   
	  if (FSfclose (pointer))
              while(1)
              {
                     LED_2_On();
              }
	     
	   
	  while(1)
	  {
			LED_6 = !LED_7;
			int j;
			for(j=0; j< 655360 ; j++)
			{
			} 		       
			LED_7 =! LED_7;
			
			for(j=0; j< 655360 ; j++)
			{
			} 	
			
	  } 	   
	  
	}
}


void SystemConfig()
{

   /* Quando o PIC32 é iniciado ele é configurado para:
	* - NO Caching turned on
	* - NO Prefetch buffer enabled
	* - 7 FLASH wait states 
	* - 1 SRAM wait states. 
	*
	* Todas estas configurações afetam a perfomasse do microcontrolador
	* fazendo que ele funcione significamente mais lento do que o esperado.
	* Para configurar corretamente, utilizamos a função SYSTEMConfigPerformance(80000000);
	* passando o valor do clock da CPU como parametro. Esta função configurará
	* as propriedades de performasse como numero correto de esperas (wait state) da
	* memória Flash e memória RAM e o uso da memória cache.
	*/
	SYSTEMConfigPerformance(80000000);
   /*
    *
    */
	mOSCSetPBDIV (OSC_PB_DIV_1);	


	// Desabilita a porta de JTAG
    DDPCONbits.JTAGEN = 0;

    AD1PCFG = 0xffffffff; // Todos pinos como digital
	ODCASET = 0x00000000;
	ODCBSET = 0x00000000;
	ODCCSET = 0x00000000;
	ODCDSET = 0x00000000;
	ODCESET = 0x00000000; 
	ODCFSET = 0x00000000; 


    ConfigAllLEDs();
	ConfgButton_1();
	
    // Turn on the interrupts
  	INTEnableSystemMultiVectoredInt();

	//Porta do CS do SPI
	TRISDbits.TRISD9 = 0;
	PORTDbits.RD9 = 0;
	

   /* // Retornar neste ponto quando o RTCC estiver funcionando.
   
   //Initialize the RTCC
   RtccInit();
   while(RtccGetClkStat()!=RTCC_CLK_ON);// wait for the SOSC to be actually running and RTCC to have its clock source
							            // could wait here at most 32ms
   RtccOpen(0x10073000, 0x07011602, 0);
   */


   //Inicializa o cartao SD
   while (!FSInit())
   {
       LED_7_Toggle();
       DelayMsx(500);
   }


    	CloseADC10();	
    OpenADC10(ADC_MODULE_ON     	| //Módulo AD energizado.
    		  ADC_IDLE_CONTINUE 	| //Continua funcionando caso a CPU esteja em IDLE
    		  ADC_FORMAT_INTG16 	| //Formatação do resultado em inteiro com sinal
    		  ADC_CLK_MANUAL		| //Clock manual
    		  ADC_AUTO_SAMPLING_OFF | //Desabilita o Auto Sapling
    		  ADC_SAMP_ON			, //Habilita o sample
    		  ADC_VREF_AVDD_AVSS	| //Tensoes de referencia AVDD e AVSS
    		  ADC_OFFSET_CAL_DISABLE| //Sem offset para calibração
    		  ADC_SCAN_OFF			| //Não usar auto select para portas analogicas
    		  ADC_SAMPLES_PER_INT_1 | //Interrupção a cada uma amostra
    		  ADC_ALT_BUF_OFF		| //Desabilita o auto-buffer
    		  ADC_ALT_INPUT_OFF	    , //Desabilita o Alternate Input Sample mode
    		  ADC_SAMPLE_TIME_31    | // Auto Sample Time bits
    		  ADC_CONV_CLK_SYSTEM	| // Clock do conversor como o mesmo da CPU
    		  ADC_CONV_CLK_32Tcy    , // Conversao clock em 32 TCY
    		  ENABLE_AN4_ANA 		| // Habilita o canal do sensor de temperatura
    		  ENABLE_AN3_ANA		| // Habilita o canal do potenciometro
    		  ENABLE_AN2_ANA		, // Habilita o canal do LDR
    		  SKIP_SCAN_ALL);		  // Nenhum canal selecionado para auto scan.
    
    
   // Initialize the library
   

}	




/******************************************************************************
 * Funcao:		char * itoa(int value)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767)
 * Saída:		char * ponteiro para um string
 * Descrição: 	Esta função converte numeros inteiros positivos e negativos
 *				para strings.
 *****************************************************************************/
char *itoaS(int value)
{
     static char buffer[12];        // 12 bytes é o suficiente para o int32
     int original = value;          // salva o valor original

     int c = sizeof(buffer)-1;

     buffer[c] = 0;                 // Escreve 0 (null) no ultimo byte de buffer

     if (value < 0)                 // Se for negativo pegar o valor absoluto
         value = -value;

     do                             //Escreve o digito menos significante do valor no buffer
     {
         buffer[--c] = (value % 10) + '0';
         value /= 10;
     } while (value);

     if (original < 0)
         buffer[--c] = '-'; // coloca o sinal de negativo

     return &buffer[c];
 }