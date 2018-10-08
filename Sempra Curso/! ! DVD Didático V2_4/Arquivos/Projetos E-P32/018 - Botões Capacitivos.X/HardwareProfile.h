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
 * Plataforma:		Placa E-P32 Periféricos V1.01                          *
 *                      Placa E-P32 Núcleo V1.01                               *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.1                                                   *
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
#define ADC_B3		ADC_CH0_POS_SAMPLEA_AN14|ADC_CH0_NEG_SAMPLEA_NVREF
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
#define LED_3			LATFbits.LATF3
#define LED_4			LATCbits.LATC3
#define LED_5			LATCbits.LATC2
#define LED_6			LATCbits.LATC1
#define LED_7			LATGbits.LATG15


#define ConfgLED_0()		TRISAbits.TRISA2    = 0
#define ConfgLED_1()		TRISAbits.TRISA3    = 0
#define ConfgLED_2()		TRISDbits.TRISD13   = 0
#define ConfgLED_3()		TRISFbits.TRISF3    = 0
#define ConfgLED_4()		TRISCbits.TRISC3    = 0
#define ConfgLED_5()		TRISCbits.TRISC2    = 0
#define ConfgLED_6()		TRISCbits.TRISC1    = 0
#define ConfgLED_7()		TRISGbits.TRISG15   = 0

#define ConfigAllLEDs()		ConfgLED_0();ConfgLED_1();ConfgLED_2();\
                                ConfgLED_3();ConfgLED_4();ConfgLED_5();\
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
#define AllLedsOff()		LED_0_Off();LED_1_Off();LED_2_Off();\
                                LED_3_Off();LED_4_Off();LED_5_Off();\
                                LED_6_Off();LED_7_Off();

// Toggle (mudar o estado para o inverso)
#define LED_0_Toggle()     	LATAINV = 0x04     //LATA2
#define LED_1_Toggle()     	LATAINV = 0x08     //LATA3
#define LED_2_Toggle()     	LATDINV = 0x2000   //LATD13
#define LED_3_Toggle()     	LATFINV = 0x08    //LATF3
#define LED_4_Toggle()     	LATCINV = 0x08     //LATC3
#define LED_5_Toggle()     	LATCINV = 0x04     //TRISC2
#define LED_6_Toggle()     	LATCINV = 0x02     //LATC1
#define LED_7_Toggle()     	LATGINV = 0x8000   //LATG15


/*******************************************************************************
* 									       *
*                               B O T Õ E S				       *
*									       *
*******************************************************************************/

#define BUTTON_1		PORTEbits.RE9
#define BUTTON_2		PORTAbits.RA14
#define BUTTON_3		PORTEbits.RE8
#define BUTTON_4		!PORTBbits.RB7
//Configuração - Entrada digital
#define ConfgButton_1()		TRISEbits.TRISE9   = 1
#define ConfgButton_2()		TRISAbits.TRISA14  = 1
#define ConfgButton_3()		TRISEbits.TRISE8   = 1
#define ConfgButton_4()		TRISBbits.TRISB7   = 1

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
*      D I S P L A Y   D E   L C D   A L F A N U M É R I C O   16 X 2          *
*									       *
*******************************************************************************/


#define OPEN_COLECTOR_A ODCA   |= 0x00000033 //0b0000000000110011;
#define OPEN_COLECTOR_G ODCG   |= 0x00006100 //0b0110000100000000;

// Define dos pinos de DADOS do LCD
#define D4       LATAbits.LATA0
#define D5       LATAbits.LATA1
#define D6	 LATAbits.LATA4
#define D7       LATAbits.LATA5

// Define do TRIS dos pinos de DADOS do LCD
#define TRIS_D4  TRISAbits.TRISA0
#define TRIS_D5  TRISAbits.TRISA1
#define TRIS_D6  TRISAbits.TRISA4
#define TRIS_D7  TRISAbits.TRISA5

// Define dos pinos de CONTROLE do LCD
#define RS_PIN   LATGbits.LATG13
#define E_PIN    LATGbits.LATG14
//#define RW_PIN

// Define os TRIS dos pinos de CONTROLE do LCD
#define TRIS_RS  TRISGbits.TRISG13
#define TRIS_E   TRISGbits.TRISG14
//#define TRIS_RW

// Define o valor dos delays baseado no clock da CPU de 80 MHz
#define DELAY_SINC()	DelayMsx(1)	 // Delay de 1ms
					// Geralmente 1ms é suficiente, mas
					// depende do controlador do display
					// Aumente conforme a necessidade!

#define DELAY_5ms()	DelayMsx(5)	// Delay de 5ms

/*******************************************************************************
* 									       *
*                   T E C L A D O   M A T R I C I A L   4 X 3                  *
*									       *
*******************************************************************************/
/*                                       C       C       C       C
 *                                       O       O       O       O
 *                                       L       L       L       L
 *                                       U       U       U       U
 *                                       N       N       N       N
 *                                       A       A       A       A
 *                                       :       :       :       :
 *                                     __:     __:     __:     __:
 *                                    |00|    |01|    |02|    |03|
 *                  LINHA_0   --------|__|----|__|----|__|----|__|
 *                                       :       :       :       :
 *                                     __:     __:     __:     __:
 *                                    |10|    |11|    |12|    |13|
 *                  LINHA_1   --------|__|----|__|----|__|----|__|
 *                                       :       :       :       :
 *                                     __:     __:     __:     __:
 *                                    |20|    |21|    |22|    |23|
 *                  LINHA_2   --------|__|----|__|----|__|----|__|
 *                                       :       :       :       :
 *                                     __:     __:     __:     __:
 *                                    |30|    |31|    |32|    |33|
 *                  LINHA_3   --------|__|----|__|----|__|----|__|
 *
 */


#define LINHA_0      PORTDbits.RD7
#define LINHA_1      PORTDbits.RD6
#define LINHA_2      PORTGbits.RG8

#define COLUNA_0     LATDbits.LATD3
#define COLUNA_1     LATDbits.LATD12
#define COLUNA_2     LATAbits.LATA9
#define COLUNA_3   	 LATDbits.LATD8

#define CONFIG_LINHA_0 TRISDbits.TRISD7
#define CONFIG_LINHA_1 TRISDbits.TRISD6
#define CONFIG_LINHA_2 TRISGbits.TRISG8

#define CONFIG_COLUNA_0 TRISDbits.TRISD3
#define CONFIG_COLUNA_1 TRISDbits.TRISD12
#define CONFIG_COLUNA_2 TRISAbits.TRISA9
#define CONFIG_COLUNA_3 TRISDbits.TRISD8


/*******************************************************************************
* 									       *
*			T E C L A D O   P S / 2 			       *
*									       *
*******************************************************************************/
 /*  			Conector Femea:		Pinos | Porta | Função
 *                                        1      RA15    Teclado Data
 *      	6 [] 5			  2      RA15	 MOUSE Data
 *             4      3                   3       - 	 GND
 *                                        4       -	 VCC
 *            	 2  1                     5      RA10	 Telcado Clock
 *                                        6      RA10	 MOUSE Clock
 */
#define	PS2_DATAPIN         PORTAbits.RA15
#define PS2_CLOCKPIN        PORTAbits.RA10

#define DATAPIN_CONFIG      TRISAbits.TRISA15
#define CLOCKPIN_CONFIG     TRISAbits.TRISA10

#define Delay5Micro()       DelayUsx(5)   // delay de 5 microsegundos
#define Delay25Micro()      DelayUsx(25) // delay de 25 microsegundos



/*******************************************************************************
* 									       *
*     D I S P L A Y   D E   7   S E G M E N T O S   M U L T I P L E X A D O    *
*									       *
*******************************************************************************/
 /*	Display 4	Display 3	Display 2	Display 1
 *        (B3)		   (B2) 	  (B1)		   (B0)
 *	---a---  	 ---a--- 	---a--- 	 ---a---
 *	|       |	|       |       |       |	|       |
 *	f       b	f       b	f       b	f       b
 *	|       |	|       |	|       |	|       |
 *	 ---g---	 ---g--- 	 ---g--- 	 ---g---
 *	|       |	|       |	|       |	|       |
 *	e       c	e       c	e       c	e       c
 *	|       |	|       |	|       |	|       |
 *	 ---d--- .p      ---d--- .p	 ---d--- .p	 ---d--- .p
 */


//Configurações:

#define ConfigDisplay_a() 	TRISAbits.TRISA2  =  0; ODCACLR = 0x00000002
#define ConfigDisplay_b() 	TRISGbits.TRISG8  =  0; ODCGCLR = 0x00000100
#define ConfigDisplay_c() 	TRISDbits.TRISD13 =  0; ODCDCLR = 0x00002000
#define ConfigDisplay_d() 	TRISCbits.TRISC3  =  0; ODCCCLR = 0x00000008
#define ConfigDisplay_e() 	TRISCbits.TRISC2  =  0; ODCCCLR = 0x00000002
#define ConfigDisplay_f() 	TRISCbits.TRISC1  =  0; ODCCCLR = 0x00000001
#define ConfigDisplay_g() 	TRISGbits.TRISG15 =  0; ODCGCLR = 0x00008000
#define ConfigDisplay_p() 	TRISAbits.TRISA3  =  0; ODCACLR = 0x00000004

// Controle
#define ConfigDisplay1() 	TRISBbits.TRISB8  =  0; ODCBCLR = 0x00000100; AD1PCFGSET = 0x00000100
#define ConfigDisplay2() 	TRISAbits.TRISA7  =  0; ODCACLR = 0x00000080
#define ConfigDisplay3() 	TRISBbits.TRISB10 =  0; ODCBCLR = 0x00000400; AD1PCFGSET = 0x00000400
#define ConfigDisplay4() 	TRISBbits.TRISB11 =  0; ODCBCLR = 0x00000800; AD1PCFGSET = 0x00000800



// Define os pinos do display de 7 seg que estão ligados nas portas do microcontrolador
// O DISPLAY É DO TIPO CATODO COMUM e para cada segmento:
//			1: LIGADO
//			0: desligado
//Clear
// Dados
#define ClearDisplay_a 	LATAbits.LATA2  = 0
#define ClearDisplay_b 	LATGbits.LATG8  = 0
#define ClearDisplay_c  LATDbits.LATD13 = 0
#define ClearDisplay_d  LATCbits.LATC3  = 0
#define ClearDisplay_e	LATCbits.LATC2  = 0
#define ClearDisplay_f	LATCbits.LATC1  = 0
#define ClearDisplay_g	LATGbits.LATG15 = 0
#define ClearDisplay_p	LATAbits.LATA3  = 0
// Controle
#define ClearDisplay1	LATBCLR = 0x00000100
#define ClearDisplay2	LATACLR = 0x00000080
#define ClearDisplay3 	LATBCLR = 0x00000400
#define ClearDisplay4 	LATBCLR = 0x00000800

//Set
// Dados
#define SetDisplay_a 	LATAbits.LATA2  = 1
#define SetDisplay_b 	LATGbits.LATG8  = 1
#define SetDisplay_c  	LATDbits.LATD13 = 1
#define SetDisplay_d  	LATCbits.LATC3  = 1
#define SetDisplay_e	LATCbits.LATC2  = 1
#define SetDisplay_f	LATCbits.LATC1  = 1
#define SetDisplay_g	LATGbits.LATG15 = 1
#define SetDisplay_p	LATAbits.LATA3  = 1
// Controle
#define SetDisplay1	LATBSET = 0x00000100
#define SetDisplay2	LATASET = 0x00000080
#define SetDisplay3 	LATBSET = 0x00000400
#define SetDisplay4 	LATBSET = 0x00000800


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

#define USE_SD_INTERFACE_WITH_SPI

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
