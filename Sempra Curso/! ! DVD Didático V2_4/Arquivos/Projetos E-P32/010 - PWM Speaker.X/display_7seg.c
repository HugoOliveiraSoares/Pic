/******************************************************************************
 *
 * 		Biblioteca SEMPRA (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     display_7seg.C
 * Dependencias:
 * Processador:       	PIC32MX775F512L
 * Op��o de Clock:	HS 10MHz (externo) - CPU: 80MHz
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Placa de desenvolvimento E-P32 v1.0
 *
 * Autor:		Bruno Silveira Avelar
 *
 * Revis�o:             Bruno Alipio Dayrell
 *
 * Data:		v1 - 21/Fev/2010
 *                      Revis�o 1 - 29/Fev/2012
 *
 * Descri��o:        	Biblioteca de fun��es para escrever no display multiplexado
 *			de 7 segmentos da placa de desenvolvimento E-P32.
 *			Os  4 displays s�o do tipo CATODO COMUM e seus segmentos
 *			s�o LIGADOS com nivel l�gico 1.
 *			O display apresenta 4 digitos e seus respectivos
 *			pontos decimais.
 *			Nesta biblioteca usa-se os r�tulos:
 *			D - digito
 *			p - ponto decimal do digito
 *
 *			Nomes usados para os segmentos do displays presentes
 *			na placa de desenvolvimento PICMINAS32:
 *
 *			Display 4		Display 3		Display 2		Display 1
 *			(B3)			   (B2) 		   (B1)			   (B0)

 *			  ---a---  	 	 ---a--- 		 ---a--- 		 ---a---
 *			 |       |		|       |		|       |		|       |
 *			 f       b		f       b		f       b		f       b
 *			 |       |		|       |		|       |		|       |
 *			  ---g---		 ---g--- 		 ---g--- 		 ---g---
 *			 |       |		|       |		|       |		|       |
 *			 e       c		e       c		e       c		e       c
 *			 |       |		|       |		|       |		|       |
 *			  ---d--- .p             ---d--- .p		 ---d--- .p		 ---d--- .p
 *
 *			 A multiplexa��o � feita pela fun��o uptate() que coloca cada
 *			 valor em seu respectivo d�gito enquanto os outros est�o apagados.
 *			 Os displays sao numerados da esquerda para direita.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include	"display_7seg.h"


/** V A R I A V E I S   G L O B A I S******************************************/
	unsigned char Digitvalue[5]; 
								 
	unsigned char pto;
	
	unsigned char contUpdate = 1;


/** F U N C O E S ************************************************************/


/******************************************************************************
 * Funcao:        	void ConfigDisplay7Seg (void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Configura portas do PIC 18F4550 que est�o conectadas ao 
 *					display duplo de 7 segmentos como saida. 
 *					Desliga todos os segmentos do display apos a configura��o
 *
 *****************************************************************************/
void ConfigDisplay7Seg (void)
{
	//Configura as portas como digitais.
	
	//PORTSetPinsDigitalOut(IOPORT_B, BIT_8 | BIT_9| BIT_10| BIT_11);	
	

	// Configura as portas conectadas aos Leds que formam os d�gitos como portas de Sa�da
	ConfigDisplay_a();
	ConfigDisplay_b();
	ConfigDisplay_c();
	ConfigDisplay_d();
	ConfigDisplay_e();
	ConfigDisplay_f();
	ConfigDisplay_g();
	ConfigDisplay_p();

	// Configura as portas conectadas aos seletores dos diplays como portas de sa�da

	ConfigDisplay1();
	ConfigDisplay2();
	ConfigDisplay3();
	ConfigDisplay4();

	// desliga o digito(display � do tipo ANODO COMUM, logo "1" desliga o segmento)
	ClearDisplay_a; //Display_a=0;
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

/******************************************************************************
 * Funcao:        	void W_display_7S_2D(unsigned int caracter, unsigned char ponto)
 * 
 * Entrada:         char caracter: valor decimal de 0 a 9999 a ser apresentado no display
 *					char ponto: se deseja ligar o ponto decimal e a posi��o do ponto
 *							0b00000000  	:desliga ponto decimal
 *							0b00000001		:liga ponto decimal do diplay 1
 *							0b00000010  	:liga ponto decimal do diplay 2
 *							0b00000100		:liga ponto decimal do diplay 3
 *							0b00001000		:liga ponto decimal do diplay 4
 * 
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Escreve valor decimal de 0000 a 9999 nos display's de 7 segmentos.
 *					Este valor fica armazenado e � preciso chamar periodicamente a fun��o
 *					update para manter o n�mero vis�vel.
 *					Liga/desliga o ponto decimal.
 *
 *****************************************************************************/
void EscreveDisplay7Seg(unsigned int numero, unsigned char ponto)
{
	
	Digitvalue[1] = numero/1000;				//calcula o digito mais significativo
												// atrav�s da fun��o que retorna o quociente
												// da divis�o inteira por 1000.
	Digitvalue[2] = (numero/100)%10;	//calcula o segundo digito mais significativo

	Digitvalue[3] = ((numero/10)%100)%10;	//calcula o terceiro digito mais significativo	

	Digitvalue[4] = (((numero%1000)%100)%10);	//calcula digito menos significativo	
		 
	pto = ponto;
}

 /******************************************************************************
 * Funcao:        	void EstadoEspera7Seg(void)
 *
 * Entrada:             Nenhuma (void)
 *
 * Sa�da:          	Nenhuma (void)
 * Descri��o:           EscreveEspera7Seg escreve s�mbolo(s) no Display de 7 segmentos.
 *                      Por exemplo, quando n�o se escreve nada no Display,
 *                      Chamamos de EstadoEspera o estado em que ele fica com
 *                      "tracinhos" (tra�os horizontais) no Display, esperando
 *                      que seja mandado  escrever algum n�mero nele,
 *                      Assim como nas fun��es de escrever valores no Display,
 *			ele salva o valor de cada d�gito nas variaveis globais correspondentes.
 *			Este valor fica armazenado e � preciso chamar periodicamente a fun��o
 *			update para manter o n�mero vis�vel.
 *			Liga/desliga o ponto decimal.
 *
 *****************************************************************************/
void EstadoEspera7Seg()
{
       Digitvalue[1] = WaitState;

	Digitvalue[2] = WaitState;

	Digitvalue[3] = WaitState;

	Digitvalue[4] = WaitState;

}

/******************************************************************************
 * Funcao:        	void UpdateDisplay7Seg()
 * 
 * Entrada:         Nenhuma (void)
 *					
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Deve chamada a cada xx ms durante a execu��o do programa.
 *					� recomendado que esta fun��o seja chamada em uma interrup��o
 *				    ativada pelo timer.
 *
 *****************************************************************************/
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
/******************************************************************************
 * Funcao:        	void SetSements_7S(char numero)
 * 
 * Entrada:         numero que deve ser colocado nas portas de sa�da do PIC
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       A fun��o organiza a porta D com o n�mero recebido.
 *					Fun��o interna para selecionar o n�mero que deve
 *					ser colocado em um display. N�o disponibilizada para o
 *					usu�rio.
 *****************************************************************************/
 void SetSements_7S(char numero)
 {
	// liga segmentos correspondentes 
	// display � do tipo ANODO COMUM, logo "1" desliga o segmento
	switch(numero)
	{ 
		case 0: 
			SetDisplay_a;//Display_a=1;
		    SetDisplay_b;//Display_b=1;
		    SetDisplay_c;//Display_c=1;
		    SetDisplay_d;//Display_d=1;
		    SetDisplay_e;//Display_e=1;
		    SetDisplay_f;//Display_f=1;
		    ClearDisplay_g;//Display_g=0;
		break; 
		
		case 1: 
			ClearDisplay_a;  //			Display_a=0;
			SetDisplay_b; //    Display_b=1;
		    SetDisplay_c; //Display_c=1;
		    ClearDisplay_d; //Display_d=0;
		    ClearDisplay_e; //Display_e=0;
		    ClearDisplay_f; //Display_f=0;
		    ClearDisplay_g; //Display_g=0;
		break; 

		case 2: 
			SetDisplay_a;//Display_a=1;
		    SetDisplay_b;//Display_b=1;
		    ClearDisplay_c;//Display_c=0;
		    SetDisplay_d;//Display_d=1;
		    SetDisplay_e;//Display_e=1;
		    ClearDisplay_f;//Display_f=0;
		    SetDisplay_g;//Display_g=1;
		break; 

		case 3: 
			SetDisplay_a;//Display_a=1;
		    SetDisplay_b;//Display_b=1;
		    SetDisplay_c;//Display_c=1;
		    SetDisplay_d;//Display_d=1;
		    ClearDisplay_e;//Display_e=0;
		    ClearDisplay_f;//Display_f=0;
		    SetDisplay_g;//Display_g=1;
		break; 
		
		case 4: 
			ClearDisplay_a; //Display_a=0;
		    SetDisplay_b; //Display_b=1;
		    SetDisplay_c; //Display_c=1;
		    ClearDisplay_d; //Display_d=0;
		    ClearDisplay_e; //Display_e=0;
		    SetDisplay_f; //Display_f=1;
		    SetDisplay_g; //Display_g=1;
		break; 

		case 5: 
			SetDisplay_a; //Display_a=1;
		    ClearDisplay_b; //Display_b=0;
		    SetDisplay_c; //Display_c=1;
		    SetDisplay_d; //Display_d=1;
		    ClearDisplay_e; //Display_e=0;
		    SetDisplay_f; //Display_f=1;
		    SetDisplay_g; //Display_g=1;
		break; 

		case 6: 
			SetDisplay_a; //Display_a=1;
		    ClearDisplay_b; //Display_b=0;
		    SetDisplay_c; //Display_c=1;
		    SetDisplay_d; //Display_d=1;
		    SetDisplay_e; //Display_e=1;
		    SetDisplay_f; //Display_f=1;
		    SetDisplay_g; //Display_g=1;
		break; 

		case 7: 
			SetDisplay_a; //Display_a=1;
		    SetDisplay_b; //Display_b=1;
		    SetDisplay_c; //Display_c=1;
		    ClearDisplay_d; //Display_d=0;
		    ClearDisplay_e; //Display_e=0;
		    ClearDisplay_f; //Display_f=0;
		    ClearDisplay_g; //Display_g=0;
		break; 
		
		case 8: 
			SetDisplay_a;//Display_a=1;
		    SetDisplay_b; //Display_b=1;
		    SetDisplay_c; //Display_c=1;
		    SetDisplay_d; //Display_d=1;
		    SetDisplay_e; //Display_e=1;
		    SetDisplay_f; //Display_f=1;
		    SetDisplay_g; //Display_g=1;
		break; 

		case 9: 
			SetDisplay_a; //Display_a=1;
		    SetDisplay_b; //Display_b=1;
		    SetDisplay_c; //Display_c=1;
		    ClearDisplay_d; //Display_d=0;
		    ClearDisplay_e; //Display_e=0;
		    SetDisplay_f; //Display_f=1;
		    SetDisplay_g; //Display_g=1;
		break;

            case WaitState:
                    ClearDisplay_a; // Display a=0;
                    ClearDisplay_b; // Display b=0;
                    ClearDisplay_c; // Display c=0;
                    ClearDisplay_d; // Display d=0;
                    ClearDisplay_e; // Display e=0;
                    ClearDisplay_f; // Display f=0;
                    SetDisplay_g;   // Display g=1;
                break;

		default: 
//			SetDisplay_a;//Display_a=1;
//		    SetDisplay_b;//Display_b=1;
//		    SetDisplay_c;//Display_c=1;
//		    SetDisplay_d; //Display_d=1;
//		    SetDisplay_e; //Display_e=1;
//		    SetDisplay_f; //Display_f=1;
//		    SetDisplay_g; //Display_g=1;
		break; 
 	}
}
/******************************************************************************
 * Funcao:        	void SetDisplay7Seg(char numero,char display)
 * 
 * Entrada:         N�mero que deve aparecer no diplay, display em que o n�mero
 *					deve aparecer
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       A fun��o escreve um n�mero em um display.
 *
 *****************************************************************************/
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
