/*******************************************************************************
 *                  SEMPRA  E-P32 Acende LED    			       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     main.c                                                 *
 * Dependencias:    	Veja a seção INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Opção de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.0                                                   *
 * Descrição:        	Este firmware faz uso da porta USB Host presente no    *
 *                      KIT E-P32 e do sistema de arquivos FAT 32. O programa  *
 *                      aguarda o usuário inserir um pendrive no KIT. Ao       *
 *                      detectar a mídia ele criará um diretório de nome "Te", *
 *                      dentro deste um diretório de nome "Tep" e dentro deste *
 *                      um arquivo de nome "tempt.txt". O programa fará 20     *
 *                      aquisições de temperatura e salvará neste arquivo.     *
 *                      As temperaturas podem ser visualizadas em um computador*
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   31/01/2012 	 Versão inicial - Bruno S. Avelar		       *
 ******************************************************************************/

//#define NOT_BOOTLOADER

 
#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include <string.h>

#include "USB Stack/usb.h"
#include "USB Stack/usb_host_msd.h"
#include "USB Stack/usb_host_msd_scsi.h"
#include "MDD File System/FSIO.h"
#include "Delays.h"
#include "HardwareProfile.h"

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

void SystemConfig();
char *itoaS(int value);

/***************************************************************************/
/**  V A R I A V E I S    G L O B A I S ************************************/


FSFILE * myFile;
BYTE myData[512];
size_t numBytes;
volatile BOOL deviceAttached;

char *sendBuffer;
char send2[] = "2";
char receiveBuffer[50];



/***************************************************************************/
/**  D E F I N E S *********************************************************/
#define RESOLUCAO (3.3/1023.0)




int main(void)
{
   FSFILE * pointer;
   unsigned char size = 0, i;
   float result;
  
    TRISGbits.TRISG15 = 0;
    LATGbits.LATG15 = 1;

   SystemConfig();
   

    while(1)
    {
        
        //Função da máquina de estados da USB
        USBTasks();
        //Verifica se o pendrive esta plugado no KIT.
        if(USBHostMSDSCSIMediaDetect())
        {
            deviceAttached = TRUE;
            //Inicializa o sistema de arquivos da FAT.
            //Caso o pendrive não esteja em FAT esta função retornará falso.
            if(FSInit())
            {
                // Criar diretório Temperatura
                if (FSmkdir(".\\Te\\Tep"))
                {

                }
                //Muda o diretório para o diretório anteriormente criado.
                FSchdir(".\\Te\\Tep");
                // Abre ou cria o arquivo tempt.txt no diretório corrente.
                pointer = FSfopen ("tempt.txt", "w");
                //Verifica se o arquivo foi criado corretamente.
                if (pointer == NULL)
                {

                }
                int cont;
	        //Faz 20 conversoes AD e grava no arquivo Temperatura.txt
                //no diretorio temperatura log.
                for(cont = 0; cont < 20; cont++)
                {
                    SetChanADC10(ADC_CH0_POS_SAMPLEA_AN4|ADC_CH0_NEG_SAMPLEA_NVREF);
                    AcquireADC10();
                    ConvertADC10();

                    while(BusyADC10())
                    {
                    }
                    result = ReadADC10(0);//Leitura do buffer i
                    result = ((result * RESOLUCAO/ 0.010) - 50) ;
                    LED_0_Toggle();
                    sendBuffer = itoaS(result);
                    //Grava no arquivo.
                    if (FSfwrite (sendBuffer, 1, (int) strlen(sendBuffer), pointer) != (int) strlen(sendBuffer))
                    {
                    }

                    sendBuffer[0] = ';';
                    sendBuffer[1] = 0;

                    if (FSfwrite (sendBuffer, 1, (int) strlen(sendBuffer), pointer) != (int) strlen(sendBuffer))
                    {

                    }
                    DelayMsx(900);
                }
	   
               // fecha o arquivo.
                if (FSfclose (pointer))
                {
                }
                char m;
                //Pisca Leds 6 e 7 indicando que a gravacao ocorreu com sucesso.
                for(m=0;m<10;m++)
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
	
                //Aguarda o pendrive ser removido.
                while(deviceAttached == TRUE)
                {
                    USBTasks();
                }
            }
        }
    }
    return 0;
}


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                void *data, DWORD size )

  Summary:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.

  Description:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.  If the application is able to handle the event, it
    returns TRUE.  Otherwise, it returns FALSE.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    DWORD size      - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    The application may also implement an event handling routine if it
    requires knowledge of events.  To do so, it must implement a routine that
    matches this function signature and define the USB_HOST_APP_EVENT_HANDLER
    macro as the name of that function.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.

            //This means that the device was removed
            deviceAttached = FALSE;
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
            return TRUE;
            break;

        case EVENT_UNSUPPORTED_DEVICE:
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            //UART2PrintString( "\r\n***** USB Error - cannot enumerate device *****\r\n" );
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
            //UART2PrintString( "\r\n***** USB Error - client driver initialization error *****\r\n" );
            return TRUE;
            break;

        case EVENT_OUT_OF_MEMORY:
            //UART2PrintString( "\r\n***** USB Error - out of heap memory *****\r\n" );
            return TRUE;
            break;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            //UART2PrintString( "\r\n***** USB Error - unspecified *****\r\n" );
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}


void SystemConfig()
{
  	int  value;
  	SYSTEMConfigWaitStatesAndPB( GetSystemClock() );

	// Enable the cache for the best performance
	CheKseg0CacheOn();
	INTEnableSystemMultiVectoredInt();
	
	value = OSCCON;
	while (!(value & 0x00000020))
	{
	    value = OSCCON;    // Wait for PLL lock to stabilize
	}

	mOSCSetPBDIV (OSC_PB_DIV_1);	


	// Desabilita a porta de JTAG
        DDPCONbits.JTAGEN = 0;
        AD1PCFG = 0xffffffff; // Todos pinos como digital
	


        ConfigAllLEDs();
        AllLedsOff();
        deviceAttached = FALSE;

        //Initialize the stack
        USBInitialize(0);


    	CloseADC10();	
        OpenADC10(ADC_MODULE_ON                 | //Módulo AD energizado.
                      ADC_IDLE_CONTINUE 	| //Continua funcionando caso a CPU esteja em IDLE
                      ADC_FORMAT_INTG16 	| //Formatação do resultado em inteiro com sinal
                      ADC_CLK_MANUAL		| //Clock manual
                      ADC_AUTO_SAMPLING_OFF     | //Desabilita o Auto Sapling
                      ADC_SAMP_ON               , //Habilita o sample
                      ADC_VREF_AVDD_AVSS	| //Tensoes de referencia AVDD e AVSS
                      ADC_OFFSET_CAL_DISABLE    | //Sem offset para calibração
                      ADC_SCAN_OFF		| //Não usar auto select para portas analogicas
                      ADC_SAMPLES_PER_INT_1     | //Interrupção a cada uma amostra
                      ADC_ALT_BUF_OFF		| //Desabilita o auto-buffer
                      ADC_ALT_INPUT_OFF         , //Desabilita o Alternate Input Sample mode
                      ADC_SAMPLE_TIME_31        | // Auto Sample Time bits
                      ADC_CONV_CLK_SYSTEM	| // Clock do conversor como o mesmo da CPU
                      ADC_CONV_CLK_32Tcy        , // Conversao clock em 32 TCY
                      ENABLE_AN4_ANA 		| // Habilita o canal do sensor de temperatura
                      ENABLE_AN3_ANA		| // Habilita o canal do potenciometro
                      ENABLE_AN2_ANA		, // Habilita o canal do LDR
                      SKIP_SCAN_ALL);		  // Nenhum canal selecionado para auto scan.

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


