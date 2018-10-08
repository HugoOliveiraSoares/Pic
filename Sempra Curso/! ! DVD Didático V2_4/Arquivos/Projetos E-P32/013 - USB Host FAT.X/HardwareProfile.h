/*******************************************************************************
 *                  SEMPRA  E-P32 Hardware Profile			       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     HardwareProfile.h                                      *
 * Dependencias:    	Veja a seção INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Opção de Clock:		HS 8MHz (externo) - CPU 80MHz		       *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.0                                                   *
 * Descrição:   	Esta biblioteca descreve a placa E-P32 criando defines *
 *			e funções para acesso dos periféricos da mesma.	       *
 *			Foi considerado o uso do clock de 80MHz para calcular  *
 *                      valores de tempo. A biblioteca foi desenvolvida com    *
 *                      base no compilador C32 da Microchip.                   *
 *			Esta biblioteca é propriedade intelectual da empresa   *
 *                      SEMPRA e tem seu uso restrito a aplicações didáticas   *
 *                      que envolvam diretamente seu KIT Didático E-P32.       *
 *									       *
 *******************************************************************************
 *******************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   31/01/2012 	 Versão inicial - Bruno S. Avelar		       *
 ******************************************************************************/

#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include <plib.h>

//------------------------------------------------------------------------------
// GetSystemClock() retorna a frequencia system clock.
//------------------------------------------------------------------------------
#define GetSystemClock()      (80000000ul)

//------------------------------------------------------------------------------
// GetPeripheralClock() retorna a frequencia do peripheral clock.
//------------------------------------------------------------------------------
#define GetInstructionClock()  GetSystemClock()

//------------------------------------------------------------------------------
// GetPeripheralClock() Esta macro retorna a frequencia do barramento de
// periféricos utilizando em Hertz.
//------------------------------------------------------------------------------
#define	GetPeripheralClock()    (GetSystemClock()/(1<<OSCCONbits.PBDIV))


/*******************************************************************************
*                                                                              *
*             D i s p l a y   G r á f i c o   L C D   T F T                    *
*                                                                              *
*******************************************************************************/

#define DISPLAY_CONTROLLER	HX8347D
#define DISP_HOR_RESOLUTION	240
#define DISP_VER_RESOLUTION	320
#define COLOR_DEPTH		16   // 1,2,4,8,16 bit por pixel são válidos.
#define USE_8BIT_PMP    
#define DISP_ORIENTATION	90    // 0, 90, 180, 270 graus são válidos

#define BacklightOn()           BL_LAT_BIT = 1
#define BacklightOff()          BL_LAT_BIT = 0

// Pino de reset
#define RST_TRIS_BIT            _TRISG7
#define RST_LAT_BIT             _LATG7

// Pino RS
#define RS_TRIS_BIT             _TRISG6
#define RS_LAT_BIT              _LATG6

// Pino CS
#define CS_TRIS_BIT             _TRISG9
#define CS_LAT_BIT              _LATG9

// Pino de alimentação do Backlight
#define BL_TRIS_BIT             _TRISG12
#define BL_LAT_BIT              _LATG12


/*******************************************************************************
*                                                                              *
*		 E N T R A D A S   A N A L Ó G I C A S			       *
*									       *
*******************************************************************************/


#define ADC_XPOS        ADC_CH0_POS_SAMPLEA_AN1 //(tooch screen)
#define ADC_YPOS        ADC_CH0_POS_SAMPLEA_AN0 //(tooch screen)

#define ADC_POT         ADC_CH0_POS_SAMPLEA_AN2|ADC_CH0_NEG_SAMPLEA_NVREF  
#define ADC_LRD 	ADC_CH0_POS_SAMPLEA_AN3|ADC_CH0_NEG_SAMPLEA_NVREF
#define ADC_TEMP 	ADC_CH0_POS_SAMPLEA_AN4|ADC_CH0_NEG_SAMPLEA_NVREF

#define ADC_B1		ADC_CH0_POS_SAMPLEA_AN5|ADC_CH0_NEG_SAMPLEA_NVREF
#define ADC_B2		ADC_CH0_POS_SAMPLEA_AN9|ADC_CH0_NEG_SAMPLEA_NVREF
#define ADC_B3		ADC_CH0_POS_SAMPLEA_AN15|ADC_CH0_NEG_SAMPLEA_NVREF
#define ADC_B4		ADC_CH0_POS_SAMPLEA_AN13|ADC_CH0_NEG_SAMPLEA_NVREF

// Definições de X port (tooch screen)
#define ADPCFG_XPOS     _PCFG1 
#define LAT_XNEG        _LATB1
#define LAT_XPOS        _LATA6
#define TRIS_XNEG       _TRISB1
#define TRIS_XPOS       _TRISA6

// Definições de Y port(tooch screen)
#define ADPCFG_YPOS     AD1PCFGbits.PCFG12
#define LAT_YNEG        _LATB12 
#define LAT_YPOS        _LATB0 
#define TRIS_YNEG       _TRISB12
#define TRIS_YPOS       _TRISB0 


/*******************************************************************************
*                                                                              *
*				 L E D s                                       *
*                                                                              *
*******************************************************************************/

#define LED_0			LATAbits.LATA2
#define LED_1			LATAbits.LATA3
#define LED_2			LATDbits.LATD13
#define LED_3			LATGbits.LATG8
#define LED_4			LATCbits.LATC3
#define LED_5			LATCbits.LATC2
#define LED_6			LATCbits.LATC1
#define LED_7			LATGbits.LATG15

#define ConfgLED_0()		TRISAbits.TRISA2    = 0
#define ConfgLED_1()		TRISAbits.TRISA3    = 0
#define ConfgLED_2()		TRISDbits.TRISD13   = 0
#define ConfgLED_3()		TRISGbits.TRISG8    = 0
#define ConfgLED_4()		TRISCbits.TRISC3    = 0
#define ConfgLED_5()		TRISCbits.TRISC2    = 0
#define ConfgLED_6()		TRISCbits.TRISC1    = 0
#define ConfgLED_7()		TRISGbits.TRISG15   = 0

#define ConfigAllLEDs()		ConfgLED_0();ConfgLED_1();ConfgLED_2(); \
                                ConfgLED_3();ConfgLED_4();ConfgLED_5(); \
                                ConfgLED_6();ConfgLED_7();

#define GetLED_0() 		LED_0
#define GetLED_1() 		LED_1
#define GetLED_2() 		LED_2
#define GetLED_3() 		LED_3
#define GetLED_4() 		LED_4
#define GetLED_5() 		LED_5
#define GetLED_6() 		LED_6
#define GetLED_7() 		LED_7

#define LED_0_On()        	LED_0 = 1
#define LED_1_On()        	LED_1 = 1
#define LED_2_On()        	LED_2 = 1
#define LED_3_On()         	LED_3 = 1
#define LED_4_On()         	LED_4 = 1
#define LED_5_On()         	LED_5 = 1
#define LED_6_On()         	LED_6 = 1
#define LED_7_On()         	LED_7 = 1
  
#define LED_0_Off()        	LED_0 = 0
#define LED_1_Off()        	LED_1 = 0
#define LED_2_Off()        	LED_2 = 0
#define LED_3_Off()        	LED_3 = 0
#define LED_4_Off()        	LED_4 = 0
#define LED_5_Off()             LED_5 = 0
#define LED_6_Off()             LED_6 = 0
#define LED_7_Off()             LED_7 = 0
#define AllLedsOff()		LED_0_Off();LED_1_Off();LED_2_Off(); \
                                LED_3_Off();LED_4_Off();LED_5_Off(); \
                                LED_6_Off();LED_7_Off();

// Toggle (mudar o estado para o inverso)   
#define LED_0_Toggle()     	LATAINV = 0x04     //LATA2
#define LED_1_Toggle()     	LATAINV = 0x08     //LATA3
#define LED_2_Toggle()     	LATDINV = 0x2000   //LATD13
#define LED_3_Toggle()     	LATGINV = 0x100    //LATG8
#define LED_4_Toggle()     	LATCINV = 0x08     //LATC3
#define LED_5_Toggle()     	LATCINV = 0x04     //TRISC2
#define LED_6_Toggle()     	LATCINV = 0x02     //LATC1
#define LED_7_Toggle()     	LATGINV = 0x8000   //LATG15


/*******************************************************************************
* 									       *
*                               B O T Õ E S				       *
*									       *
*******************************************************************************/

#define BUTTON_1		PORTFbits.RF3
#define BUTTON_2		PORTBbits.RB14
#define BUTTON_3		PORTDbits.RD7
#define BUTTON_4		!PORTDbits.RD6
//Configuração - Entrada digital
#define ConfgButton_1()		TRISFbits.TRISF3  = 1
#define ConfgButton_2()		TRISBbits.TRISB14  = 1;AD1PCFGbits.PCFG14 = 1
#define ConfgButton_3()		TRISDbits.TRISD7  = 1
#define ConfgButton_4()		TRISDbits.TRISD6  = 1

#define ConfigAllButtons()      ConfgButton_1();ConfgButton_2();\
                                ConfgButton_3();ConfgButton_4();

/*******************************************************************************
* 								   	       *
*				 R E L É                                       *
*                                                                              *
*******************************************************************************/

#define RELE			LATDbits.LATD11
#define Rele_On()               RELE = 1
#define Rele_Off()		RELE = 0
#define ConfigRele()            TRISDbits.TRISD11 = 0

/*******************************************************************************
* 									       *
*	 		M O T O R   D E   P A S S O                            *
*                                                                              *
*******************************************************************************/

#define STP1			LATFbits.LATF0
#define STP2			LATFbits.LATF1
#define STP3			LATGbits.LATG0
#define STP4			LATGbits.LATG1

#define ConfigStepMotor()       ODCFSET |= 0x00000003; ODCGSET |= 0x00000003;\
                                TRISFbits.TRISF0 = 0;TRISFbits.TRISF1 = 0; \
                                TRISGbits.TRISG0 = 0; TRISGbits.TRISG1 = 0

/*******************************************************************************
* 									       *
*			        S E P E A K E R     			       *
*									       *
*******************************************************************************/

#define	SPEAKER                 LATDbits.LATD1
#define ConfigSpeaker()         TRISDbits.TRISD1 = 0
#define  Beep()                 //SetDCOC2PWM(300);DelayMs(25);SetDCOC2PWM(0);

/*******************************************************************************
* 									       *
*			T E C L A D O   P S / 2 			       *
*									       *
*******************************************************************************/

#define	PS2_DATA            LATAbits.LATA15
#define PS2_CLOCK           LATAbits.LATA10

#define ConfgPS2Data()      TRISAbits.TRISA15 = 1
#define ConfgPS2Clock()     TRISAbits.TRISA10 = 1

#define ConfigPS2()         ConfgPS2Clock();ConfgPS2Data()

/*******************************************************************************
*                                                     			       *
*                           U S B    H O S T 			               *
*									       *
*******************************************************************************/

//#define USE_USB_INTERFACE  // USB host MSD library


/*******************************************************************************
* 									       *
*                               S D   C A R D                                  *
*									       *
*******************************************************************************/

//#define USE_SD_INTERFACE_WITH_SPI

#ifdef USE_SD_INTERFACE_WITH_SPI

//Detectar a presença do cartão SD por software e nao por hardware.
//#define MEDIA_SOFT_DETECT
		
// Definição do módulo SPI a ser utilizado
#define MDD_USE_SPI_1

//Configuração SPI 
#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | \
                             MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
#define SPI_START_CFG_2     (SPI_ENABLE)

// Frequencia da SPI
#define SPI_FREQUENCY	    (20000000)

 //SD-SPI Chip Select
#define SD_CS               LATDbits.LATD9
#define SD_CS_TRIS          TRISDbits.TRISD9

//Pino de detecção do cartão SD-SPI
#define SD_CD               0 // NAO IMPLEMENTADO
#define SD_CD_TRIS          TRISFbits.TRISF0 // NAO IMPLEMENTADO

// Pino de proteção do cartão SD
// 1 protegido | 0 desprotegido

#define SD_WE               1// NAO IMPLEMENTADO PORTFbits.RF1
#define SD_WE_TRIS          TRISFbits.TRISF1

//SPI control register
#define SPICON1             SPI1CON
#define SPICON1bits         SPI1CONbits
//SPI status register
#define SPISTAT             SPI1STAT
#define SPISTATbits         SPI1STATbits
//SPI Buffer
#define SPIBUF              SPI1BUF
// Bit que indica buffer cheio do SPI status register
#define SPISTAT_RBF         SPI1STATbits.SPIRBF
//SPI Enable
#define SPIENABLE           SPICON1bits.ON
//SPI baud rate generator register - Controla frequencia da SPI
#define SPIBRG              SPI1BRG

//TRIS do pino de clock (SCK)
#define SPICLOCK            TRISDbits.TRISD10
//TRIS do pino SDI
#define SPIIN               TRISDbits.TRISD0
//TRIS do pino SDO
#define SPIOUT              TRISCbits.TRISC4
//Funções da biblioteca SPI
#define putcSPI             putcSPI1
#define getcSPI             getcSPI1
#define OpenSPI(config1, config2)   OpenSPI1(config1, config2)

// Se o clock do microcontrolador nao for adequado para comunicação com o SD
#if (GetSystemClock() < 100000)
   #error O Clock da CPU deve ser maior que 100 KHz
#endif    

#endif

#endif // __HARDWARE_PROFILE_H
