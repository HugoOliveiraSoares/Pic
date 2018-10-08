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
 * Autor:                                                                      *
 * Versão:                                                                     *
 * Descrição:                                                                  *
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   xx/xx/20xx                                     		       *
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
                while(1)
                {
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


