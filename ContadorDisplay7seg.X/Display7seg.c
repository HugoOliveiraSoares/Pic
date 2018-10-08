
// INCLUDE DO ARQUIVO HEADER
#include "Display7seg.h"

// DECLARAÇÃO DAS FUNÇÕES

void ConfiguraDisplay(void)
{
	ADCON1 = 0x0F;
    Led_A = 0;
    Led_B = 0;
    Led_C = 0;
    Led_D = 0;
    Led_E = 0;
    Led_F = 0;
    Led_G = 0;
}

void numero(int num){ 
    
    switch(num)
    {
        case 0: Led_A = 1;
                Led_B = 1;
                Led_C = 1;
                Led_D = 1;
                Led_E = 1;
                Led_F = 1;
                Led_G = 0; break;// end num0
        
        case 1: Led_A = 0;
                Led_B = 1;
                Led_C = 1;
                Led_D = 0;
                Led_E = 0;
                Led_F = 0;
                Led_G = 0; break;// end num1
           
        case 2: Led_A = 1;
                Led_B = 1;
                Led_C = 0;
                Led_D = 1;
                Led_E = 1;
                Led_F = 0;
                Led_G = 1; break;// end num2
                        
        case 3: Led_A = 1;
                Led_B = 1;
                Led_C = 1;
                Led_D = 1;
                Led_E = 0;
                Led_F = 0;
                Led_G = 1; break; // end num3
                
        case 4: Led_A = 0;
                Led_B = 1;
                Led_C = 1;
                Led_D = 0;
                Led_E = 0;
                Led_F = 1;
                Led_G = 1; break; // end num4
                
        case 5: Led_A = 1;
                Led_B = 0;
                Led_C = 1;
                Led_D = 1;
                Led_E = 0;
                Led_F = 1;
                Led_G = 1; break; // end num5
                
        case 6: Led_A = 1;
                Led_B = 0;
                Led_C = 1;
                Led_D = 1;
                Led_E = 1;
                Led_F = 1;
                Led_G = 1; break; // end num6
                
        case 7: Led_A = 1;
                Led_B = 1;
                Led_C = 1;
                Led_D = 0;
                Led_E = 0;
                Led_F = 0;
                Led_G = 0; break; // end num7
                
        case 8: Led_A = 1;
                Led_B = 1;
                Led_C = 1;
                Led_D = 1;
                Led_E = 1;
                Led_F = 1;
                Led_G = 1; break; // end num8
                
        case 9: Led_A = 1;
                Led_B = 1;
                Led_C = 1;
                Led_D = 1;
                Led_E = 0;
                Led_F = 1;
                Led_G = 1; break; // end num9
       
       default: Led_A = 0;
                Led_B = 0;
                Led_C = 0;
                Led_D = 0;
                Led_E = 0;
                Led_F = 0;
                Led_G = 0;           
    } // end switch

}