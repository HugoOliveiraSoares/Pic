/** I N C L U D E S **********************************************************/
#include	"display_7seg.h"


/** V A R I A V E I S   G L O B A I S******************************************/
	unsigned char Digitvalue[5];
								 
	unsigned char pto;
	
	unsigned char contUpdate = 1;

/** F U N C O E S    P R I V A D A S ******************************************/
/******************************************************************************
 * Funcao:          void SetDisplay7Seg(char numero,char display)
 * 
 * Entrada:         Número que deve aparecer no diplay, display em que o número
 *                  deve aparecer
 * Saída:           Nenhuma (void)
 * Descrição:       A função escreve um número em um display.
 *
 *****************************************************************************/
 extern void SetDisplay7Seg(char numero, char display);



/** F U N C O E S   P U B L I C A S ******************************************/

void ConfigDisplay7Seg (void)
{
	//Configura as portas como digitais.

	// Configura as portas conectadas aos Leds que formam os dígitos como portas de Saída
	ConfigDisplay_a();
	ConfigDisplay_b();
	ConfigDisplay_c();
	ConfigDisplay_d();
	ConfigDisplay_e();
	ConfigDisplay_f();
	ConfigDisplay_g();
	ConfigDisplay_p();

	// Configura as portas conectadas aos seletores dos diplays como portas de saída

	ConfigDisplay1();
	ConfigDisplay2();
	ConfigDisplay3();
	ConfigDisplay4();

	// desliga o digito(display é do tipo ANODO COMUM, logo "1" desliga o segmento)
	ClearDisplay_a; 
        ClearDisplay_b;
        ClearDisplay_c;
        ClearDisplay_d;
        ClearDisplay_e;
        ClearDisplay_f;
        ClearDisplay_g;
        ClearDisplay_p;
    
	// Desliga todos os displays:
	ClearDisplay1;
	ClearDisplay2;
	ClearDisplay3;
	ClearDisplay4;
}

void EscreveDisplay7Seg(unsigned int numero, unsigned char ponto)
{
	
	Digitvalue[1] = numero/1000;        //calcula o digito mais significativo
                                            // através da função que retorna o quociente
                                            // da divisão inteira por 1000.
	Digitvalue[2] = (numero/100)%10;    //calcula o segundo digito mais significativo

	Digitvalue[3] = ((numero/10)%100)%10;//calcula o terceiro digito mais significativo	

	Digitvalue[4] = (((numero%1000)%100)%10);//calcula digito menos significativo	
		 
	pto = ponto;
}

 void UpdateDisplay7Seg()
 {
	if(contUpdate < 5)
	{
            SetDisplay7Seg(Digitvalue[contUpdate],contUpdate);
            contUpdate++;
	}
	else
	{
		contUpdate = 1;
	}
}

 void SetSements_7S(char numero)
 {
	// liga segmentos correspondentes 
	// display é do tipo ANODO COMUM, logo "1" desliga o segmento
	switch(numero)
	{ 
		case 0: 
                    SetDisplay_a;
		    SetDisplay_b;
		    SetDisplay_c;
		    SetDisplay_d;
		    SetDisplay_e;
		    SetDisplay_f;
		    ClearDisplay_g;
		break; 
		
		case 1: 
                    ClearDisplay_a;
                    SetDisplay_b;
		    SetDisplay_c; 
		    ClearDisplay_d;
		    ClearDisplay_e;
		    ClearDisplay_f;
		    ClearDisplay_g;
		break; 

		case 2: 
                    SetDisplay_a;
		    SetDisplay_b;
		    ClearDisplay_c;
		    SetDisplay_d;
		    SetDisplay_e;
		    ClearDisplay_f;
		    SetDisplay_g;
		break; 

		case 3: 
                    SetDisplay_a;
		    SetDisplay_b;
		    SetDisplay_c;
		    SetDisplay_d;
		    ClearDisplay_e;
		    ClearDisplay_f;
		    SetDisplay_g;
		break; 
		
		case 4: 
                    ClearDisplay_a;
		    SetDisplay_b; 
		    SetDisplay_c; 
		    ClearDisplay_d; 
		    ClearDisplay_e; 
		    SetDisplay_f; 
		    SetDisplay_g; 
		break; 

		case 5: 
                    SetDisplay_a;
		    ClearDisplay_b;
		    SetDisplay_c;
		    SetDisplay_d;
		    ClearDisplay_e;
		    SetDisplay_f;
		    SetDisplay_g;
		break; 

		case 6: 
                    SetDisplay_a;
		    ClearDisplay_b;
		    SetDisplay_c;
		    SetDisplay_d;
		    SetDisplay_e;
		    SetDisplay_f;
		    SetDisplay_g;
		break; 

		case 7: 
                    SetDisplay_a;
		    SetDisplay_b;
		    SetDisplay_c;
		    ClearDisplay_d;
		    ClearDisplay_e;
		    ClearDisplay_f;
		    ClearDisplay_g;
		break; 
		
		case 8: 
                    SetDisplay_a;
		    SetDisplay_b;
		    SetDisplay_c;
		    SetDisplay_d;
		    SetDisplay_e;
		    SetDisplay_f;
		    SetDisplay_g;
		break; 

		case 9: 
                    SetDisplay_a;
		    SetDisplay_b;
		    SetDisplay_c;
		    ClearDisplay_d;
		    ClearDisplay_e;
		    SetDisplay_f;
		    SetDisplay_g;
		break;
		
		default: 
                    SetDisplay_a;
                    SetDisplay_b;
		    SetDisplay_c;
		    SetDisplay_d;
		    SetDisplay_e;
		    SetDisplay_f;
		    SetDisplay_g;
		break; 
 	}
}
void SetDisplay7Seg(char numero, char display)
{
	switch(display)
	{
	case 1:
            SetDisplay1;
            ClearDisplay2;
            ClearDisplay3;
            ClearDisplay4;
            if(pto == 0b000001)
            {
                SetDisplay_p;
            }
            else
            {
                ClearDisplay_p;
            }
	break;
	case 2:
            SetDisplay2;
            ClearDisplay1;
            ClearDisplay3;
            ClearDisplay4;
            if(pto == 0b000010)
            {
                SetDisplay_p;
            }
            else
            {
                ClearDisplay_p;
            }

	break;
	case 3:
            SetDisplay3;
            ClearDisplay2;
            ClearDisplay1;
            ClearDisplay4;
            if(pto == 0b000100)
            {
                SetDisplay_p;
            }
            else
            {
                ClearDisplay_p;
            }
	break;
	case 4:
            SetDisplay4;
            ClearDisplay2;
            ClearDisplay3;
            ClearDisplay1;
            if(pto == 0b001000)
            {
                SetDisplay_p;
            }
            else
            {
                ClearDisplay_p;
            }
	break;
	}

	SetSements_7S(numero);
}



