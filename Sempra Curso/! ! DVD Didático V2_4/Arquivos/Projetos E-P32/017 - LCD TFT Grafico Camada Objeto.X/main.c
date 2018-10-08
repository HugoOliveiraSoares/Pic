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
 * Descrição:        	Este programa utiliza a camada objeto da biblioteca    *
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
#include "Graphics/Graphics.h"
//#include "TouchScreen.h"
#include "HardwareProfile.h"


/////////////////////////////////////////////////////////////////////////////
//                              DEFINES
/////////////////////////////////////////////////////////////////////////////

#define ID_BUTTON_TEST 1
#define ID_WINDOW1 2



#define WAIT_UNTIL_FINISH(x) while(!x)

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////

WORD MsgStartScreen(WORD objMsg, OBJ_HEADER* pObj,GOL_MSG* pMsg);
WORD GOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
WORD GOLDrawCallback();
void StartScreen();
void CreateStartScreen();
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

typedef enum {
    CREATE_START_SCREEN = 0,
    DISPLAY_START_SCREEN
}screenState;

screenState state;
GOL_MSG msg;        			// GOL message structure

GOL_SCHEME *altScheme;                  // Style scheme alternativo
static GOL_SCHEME *pSempraScheme;

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
	
    //Inicializa a biblioteca gráfica para camada objeto
    GOLInit();
    //Inicializa o touchscreen
    LED_0_On();
    TouchInit();
    LED_1_On();
    // Liga o LED do LCD TFT - RG12
    TRISGbits.TRISG12 = 0;
    LATGbits.LATG12 = 1;
    /*TODO:
     lala
     */ 
   state = CREATE_START_SCREEN;
    while(1)
    {
        if(GOLDraw())// Draw GOL objects
	{
           
            // O desenho da tela está pronto.
            //Processando o clique e a mensagem.
            TouchGetMsg(&msg);     // Get message from touch screen
            GOLMsg(&msg);          // Process message
        }

    }

}


/////////////////////////////////////////////////////////////////////////////
// Function: WORD GOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns non-zero the message will be processed by default
// Overview: this function must be implemented by user. GOLMsg() function calls it each
//           time the valid message for the object received
/////////////////////////////////////////////////////////////////////////////
WORD GOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
    //Processar as mensagens pela categoria
    //Para ficar mais organizado, criamos uma função para cada tela (screen)
    switch(state)
    {
        case CREATE_START_SCREEN:
        return 1;

        case DISPLAY_START_SCREEN:
            return MsgStartScreen(objMsg, pObj, pMsg);
        break;
    }
}
WORD GOLDrawCallback()
{ 
    switch(state)
    {
        case CREATE_START_SCREEN:
            CreateStartScreen();
            state = DISPLAY_START_SCREEN; //Muda para o proximo estado
            return 1;

        case DISPLAY_START_SCREEN:
        return 1; 
        
    }
    return 1;    										// release drawing control to GOL
}


WORD MsgStartScreen(WORD objMsg, OBJ_HEADER* pObj,GOL_MSG* pMsg)
{
   return 1;

}


void CreateStartScreen()
{
     GOLFree();   // Libera memória de objetos, começando uma nova lista

     //Criando um scheme para a pagina.
    pSempraScheme = GOLCreateScheme();
    pSempraScheme->Color0 = WHITE;
   
   WndCreate(ID_WINDOW1,                // ID
             0,0,GetMaxX(),GetMaxY(), 	// dimension
             WND_DRAW,                	// will be dislayed after creation
             NULL,                      // icon
             "    www.sempratec.com.br",	   					// set text
             pSempraScheme);            // sempra GOL schem

     BtnCreate(ID_BUTTON_TEST,      // ID do botão
              75,50,225,200,        // dimenções
              3,                    // Raio das bordas do botão
              BTN_DRAW,             // Desenhar o botão
              NULL,                 // Nenhuma bitmap
              "Aperte", 	    // Texto do botão
             NULL);           // use alternate scheme

}