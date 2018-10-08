/******************************************************************************
 *
 * 		Biblioteca SEMPRA (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     display_7seg.h
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
#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.

/** D E F I N E S ************************************************************/

//Configura��es:

#define ConfigDisplay_a() 	PORTSetPinsDigitalOut(IOPORT_A, BIT_2) //TRISAbits.TRISA2
#define ConfigDisplay_b() 	PORTSetPinsDigitalOut(IOPORT_G, BIT_8) //TRISDbits.TRISD4
#define ConfigDisplay_c() 	PORTSetPinsDigitalOut(IOPORT_D, BIT_13)//TRISDbits.TRISD13
#define ConfigDisplay_d() 	PORTSetPinsDigitalOut(IOPORT_C, BIT_3) //TRISCbits.TRISC3
#define ConfigDisplay_e() 	PORTSetPinsDigitalOut(IOPORT_C, BIT_2) //TRISCbits.TRISC2
#define ConfigDisplay_f() 	PORTSetPinsDigitalOut(IOPORT_C, BIT_1) //TRISCbits.TRISC1
#define ConfigDisplay_g() 	PORTSetPinsDigitalOut(IOPORT_G, BIT_15) //TRISGbits.TRISG15
#define ConfigDisplay_p() 	PORTSetPinsDigitalOut(IOPORT_A, BIT_3) //TRISAbits.TRISA3

// Controle
#define ConfigDisplay1() 	PORTSetPinsDigitalOut(IOPORT_B, BIT_8) //TRISBbits.TRISB8
#define ConfigDisplay2() 	PORTSetPinsDigitalOut(IOPORT_A, BIT_7) //TRISBbits.TRISB9
#define ConfigDisplay3() 	PORTSetPinsDigitalOut(IOPORT_B, BIT_10) //TRISBbits.TRISB10
#define ConfigDisplay4() 	PORTSetPinsDigitalOut(IOPORT_B, BIT_11) //TRISBbits.TRISB11



// Define os pinos do display de 7 seg que est�o ligados nas portas do microcontrolador
// O DISPLAY � DO TIPO CATODO COMUM e para cada segmento:
//			1: LIGADO
//			0: desligado
//Clear
// Dados
#define ClearDisplay_a 	PORTClearBits(IOPORT_A, BIT_2)	//PORTAbits.RA2
#define ClearDisplay_b 	PORTClearBits(IOPORT_G, BIT_8)  //PORTDbits.RD4
#define ClearDisplay_c  PORTClearBits(IOPORT_D, BIT_13) //PORTDbits.RD13
#define ClearDisplay_d  PORTClearBits(IOPORT_C, BIT_3) //PORTCbits.RC3
#define ClearDisplay_e	PORTClearBits(IOPORT_C, BIT_2) //PORTCbits.RC2
#define ClearDisplay_f	PORTClearBits(IOPORT_C, BIT_1) //PORTCbits.RC1   ====> MOD
#define ClearDisplay_g	PORTClearBits(IOPORT_G, BIT_15) //PORTGbits.RG15
#define ClearDisplay_p	PORTClearBits(IOPORT_A, BIT_3) //PORTAbits.RA3
// Controle
#define ClearDisplay1	PORTClearBits(IOPORT_B, BIT_8) //PORTBbits.RB8
#define ClearDisplay2	PORTClearBits(IOPORT_A, BIT_7) //PORTBbits.RB9
#define ClearDisplay3 	PORTClearBits(IOPORT_B, BIT_10) //PORTBbits.RB10
#define ClearDisplay4 	PORTClearBits(IOPORT_B, BIT_11) //PORTBbits.RB11

//Set
// Dados
#define SetDisplay_a 	PORTSetBits(IOPORT_A, BIT_2)	//PORTAbits.RA2
#define SetDisplay_b 	PORTSetBits(IOPORT_G, BIT_8)  //PORTDbits.RD4
#define SetDisplay_c  	PORTSetBits(IOPORT_D, BIT_13) //PORTDbits.RD13
#define SetDisplay_d  	PORTSetBits(IOPORT_C, BIT_3) //PORTCbits.RC3
#define SetDisplay_e	PORTSetBits(IOPORT_C, BIT_2) //PORTCbits.RC2
#define SetDisplay_f	PORTSetBits(IOPORT_C, BIT_1) //PORTCbits.RC1
#define SetDisplay_g	PORTSetBits(IOPORT_G, BIT_15) //PORTGbits.RG15
#define SetDisplay_p	PORTSetBits(IOPORT_A, BIT_3) //PORTAbits.RA3
// Controle
#define SetDisplay1	PORTSetBits(IOPORT_B, BIT_8) //PORTBbits.RB8
#define SetDisplay2	PORTSetBits(IOPORT_A, BIT_7) //PORTBbits.RB9
#define SetDisplay3 	PORTSetBits(IOPORT_B, BIT_10) //PORTBbits.RB10
#define SetDisplay4 	PORTSetBits(IOPORT_B, BIT_11) //PORTBbits.RB11

// C�digos
// foram aproveitados c�digos de 8bits fora do BCD (de A a F)
// para envio de caracteres especiais.
#define WaitState        0x0F
/** P R O T O T I P O S *******************************************************/

/******************************************************************************
 * Funcao:        void ConfigDisplay7Seg (void)
 * Entrada:       Nenhuma (void)
 * Sa�da:         Nenhuma (void)
 * Descri��o:     Configura portas do que est�o conectadas ao 
 *                displays de 7 segmentos como saida.
 *                Desliga todos os segmentos do display apos a configura��o
 *
 *****************************************************************************/
 extern void ConfigDisplay7Seg(void);

/******************************************************************************
 * Funcao:        	void EscreveDisplay7Seg(unsigned int numero, unsigned char ponto)
 * 
 * Entrada:         int caracter: valor decimal de 0 a 9999 a ser apresentado no display
 *					char ponto: liga o ponto decimal e a posi��o do ponto
 *							0b00000000  	:desliga ponto decimal
 *							0b00000001		:liga ponto decimal do diplay 1
 *							0b00000010  	:liga ponto decimal do diplay 2
 *							0b00000100		:liga ponto decimal do diplay 3
 *							0b00001000		:liga ponto decimal do diplay 4
 * 
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Escreve valor decimal de 0000 a 9999 nos display's de 7 segmentos.
 *					e salva o valor de cada d�gito nas variaveis globais correspondentes.
 *					Este valor fica armazenado e � preciso chamar periodicamente a fun��o
 *					update para manter o n�mero vis�vel.
 *					Liga/desliga o ponto decimal.
 *
 *****************************************************************************/
 extern void EscreveDisplay7Seg(unsigned int numero, unsigned char ponto);

 /******************************************************************************
 * Funcao:        	void EstadoEspera7Seg(void)
 * 
 * Entrada:             Nenhuma (void) 
 * 
 * Sa�da:          	Nenhuma (void)
 * Descri��o:           EscreveEspera7Seg escreve s�mbolo(s) no Display de 7 segmentos.
 *                      Por exemplo, quando n�o se escreve nada no Display,
 *                      Chamamos de EstadoEspera o estado em que ele � exibido
 *                      "tracejado" (tra�os horizontais no Display), esperando
 *                      que seja mandado  escrever algum n�mero nele,
 *                      Assim como nas fun��es de escrever valores no Display,
 *			ele salva o valor de cada d�gito nas variaveis globais correspondentes.
 *			Este valor fica armazenado e � preciso chamar periodicamente a fun��o
 *			update para manter o n�mero vis�vel.
 *			Liga/desliga o ponto decimal.
 *
 *****************************************************************************/
 extern void EstadoEspera7Seg(void);
 
/******************************************************************************
 * Funcao:        void UpdateDisplay7Seg()
 * 
 * Entrada:       Nenhuma (void)
 *					
 * Sa�da:         Nenhuma (void)
 * Descri��o:     Deve chamada a cada 20 ms durante a execu��o do programa.
 *                � recomendado que esta fun��o seja chamada em uma interrup��o
 *		  ativada pelo timer.
 *
 *****************************************************************************/
 extern void UpdateDisplay7Seg();


/******************************************************************************
 * Funcao:        	void SetDisplay7Seg(char numero,char display)
 * 
 * Entrada:         N�mero que deve aparecer no diplay, display em que o n�mero
 *					deve aparecer
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       A fun��o escreve um n�mero em um display.
 *
 *****************************************************************************/
 extern void SetDisplay7Seg(char numero, char display);
