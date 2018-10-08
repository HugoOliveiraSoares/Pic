/*******************************************************************************
 *          SEMPRA  E-P32   Display TFT Gráfico - Camada Primitiva	       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     main.c                                       *
 * Dependencias:    	Veja a seção INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Opção de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.0                                                   *
 * Descrição:        	Este programa utiliza a camada primitiva da biblioteca *
 *                      gráfica da Microchip (www.microchip.com/graphics) para *
 *                      desenhar circulos concentricos no display gráfico LCD  *
 *                      TFT presente no KIT E-P32
 *                                                                             *
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   31/01/2012 	 Versão inicial - Bruno S. Avelar		       *
 ******************************************************************************/


#include <string.h>
#include <plib.h>
#include <string.h>
#include "GenericTypeDefs.h"
#include "Graphics\Graphics.h"
#include "HardwareProfile.h"


/////////////////////////////////////////////////////////////////////////////
//                              DEFINES
/////////////////////////////////////////////////////////////////////////////



#define WAIT_UNTIL_FINISH(x) while(!x)

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
//                            IMAGES USED
/////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////
//                             FONTS USED
/////////////////////////////////////////////////////////////////////////////
extern const FONT_FLASH GOLFontDefault; 	// default GOL font
extern const FONT_FLASH GOLMediumFont; 		// medium font
extern const FONT_FLASH GOLSmallFont; 		// small font
extern const FONT_FLASH Gentium_14; // MINHA FONTE

/////////////////////////////////////////////////////////////////////////////
//                            COLORS USED
/////////////////////////////////////////////////////////////////////////////
#define GRAY20             RGB565CONVERT( 51,  51,  51)
#define GRAY40             RGB565CONVERT(102, 102, 102)
#define GRAY80             RGB565CONVERT(204, 204, 204)
#define GRAY90             RGB565CONVERT(229, 229, 229)
#define GRAY95             RGB565CONVERT(242, 242, 242)

#define RED4 		   RGB565CONVERT(139,   0,   0)
#define FIREBRICK1         RGB565CONVERT(255,  48,  48)
#define DARKGREEN          RGB565CONVERT(  0, 100,   0)
#define PALEGREEN          RGB565CONVERT(152, 251, 152)
#define LIGHTYELLOW        RGB565CONVERT(238, 221, 130)
#define GOLD               RGB565CONVERT(255, 215,   0)
#define DARKORANGE	   RGB565CONVERT(255, 140,   0)


/////////////////////////////////////////////////////////////////////////////
//                       VARIAVEIS GLOBAIS
/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
int main(void)
{
    INTEnableSystemMultiVectoredInt();
    SYSTEMConfigPerformance(GetSystemClock());	

    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    DDPCONbits.JTAGEN = 0;
    DDPCONbits.TROEN  = 0;
    DDPCONbits.TDOEN  = 0;
	
    ConfigAllLEDs();
    AllLedsOff();
    LED_1_On();
  
    //Inicializa a biblioteca gráfica
    InitGraph();

   
    // Liga o LED do LCD TFT - RG12
    TRISGbits.TRISG12 = 0;
    LATGbits.LATG12 = 1;
   
    // draw concentric filled circles in the middle of the screen
    SetColor(BRIGHTBLUE);
    WAIT_UNTIL_FINISH(FillCircle(GetMaxX() >> 1, GetMaxY() >> 1, 60));
    SetColor(BRIGHTGREEN);
    WAIT_UNTIL_FINISH(FillCircle(GetMaxX() >> 1, GetMaxY() >> 1, 40));
    SetColor(BRIGHTRED);
    WAIT_UNTIL_FINISH(FillCircle(GetMaxX() >> 1, GetMaxY() >> 1, 20));

    while(1)
    {
        
    }

}


