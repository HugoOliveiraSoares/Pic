/******************************************************************************
 *
 *            SEMPRA PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo)	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 * Prática: 		Semáforo
 * Descrição:        	Este projeto implementa um semáforo utilizando o KIT didático E-P18
 *			com dois funcionamentos distintos: dia e noite. 
 *			Este estado é definido através da leitura do LDR(AN3). 
 *			O tempo é implementado com o uso das funções delays do compilador
 *				Dia:  
 *                                  Alternar os LEDs verde, amarelo, vermelho na respectiva ordem nos tempos abaixo:
 *                                  Verde - 10 segundos.
 *                                  Amarelo - 4 segundos.
 *                                  Vermelho - 15 segundos.
 *				Noite:
 *                                  O LED amarelo deve piscar intermitentemente.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
						// com as definições do PIC selecionado no projeto, neste
						// caso, o modelo 18F4550.

#include <delays.h>		// Biblioteca padrão de rotinas de atraso do C18 Microchip
						// mais informações nos arquivos de ajuda da biblioteca C18
						// presentes na propria pasta de instalação, por exemplo,
						// C:\MCC18\doc\hlpC18Lib.chm
						// Procure pelo item: "Delay Functions"		
	
#include <adc.h>			// Biblioteca padrão de rotinas para conversão A/D do C18 
							// mais informações nos arquivos de ajuda da biblioteca C18
							// presentes na propria pasta de instalação, por exemplo,
							// C:/MCC18/doc/periph-lib/AD Converter.htm	

#include "display7seg.h"	// Biblioteca de usuário com funções para o display duplo
				// de 7-segmentos duplo do KIT E-P18

/** D E F I N E S ************************************************************/
#define VDD 5			// Define um valor para VDD do CAD para ser utilizado 
						// nos calculos de conversão para decimal, nessa 
						// prática é 5V

// LED's do KIT E-P18:	saida digital
//atribuição:	0 = LED desligado
//		1 = LED ligado

#define LED_VERDE 	PORTCbits.RC2
#define LED_VERMELHO 	PORTDbits.RD1
#define LED_AMARELO 	PORTDbits.RD0

// O Botão de BOOT tem lógica invertida
//atribuição:	0 = botao pressionado
//				1 = botao não pressionado
#define BOTAO_BOOT		PORTBbits.RB4

// Buzina (buzzer): saida digital
//atribuição:	0 = buzzer desligado
//				1 = buzzer ligado  
#define BUZZER 			PORTCbits.RC1



/** V A R I A V E I S   G L O B A I S ****************************************/

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);
void atraso1seg (void);
void write_CL (void);   //escreve CL no display, de "closed"

/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:        	void main(void)
 * Entrada:         Nenhuma (void)
 * Saída:          	Nenhuma (void)
 * Descrição:       Função principal do programa. 
 *****************************************************************************/
void main(void)
{
	// Variável que guarda o valor da conversão A/D em BINÁRIO.
	unsigned int Num_CAD_bin = 0;
	
	// Variável que guarda o valor da conversão A/D em VOLTS.
	unsigned int Num_CAD_volts = 0;
	
	// resolução do CAD de 10bits (2^10-1)
	unsigned float resolucao = VDD/1023.0; 
	
	//variavel para loops
	int i;
	char dia;
	
	ConfiguraSistema();		// Configura as portas e periféricos do PIC.

	//Desliga todos os LED's
	LED_VERDE=0;
	LED_AMARELO=0;
	LED_VERMELHO=0;
	
	//Desliga Buzzer
	BUZZER=0;

    while(1)				// Laço infinito que executa o funcionamento principal do projeto.
   { 
		//Verifica se esta de dia ou de noite

		if(!BusyADC())
		{ 
			// Lê o valor convertido e armazena na variável
			Num_CAD_bin=ReadADC();		
			// Inicia a nova Conversão
			ConvertADC();
		}
		// Conversão do valor em binário fornecido pelo CAD para o valor equivalente 
		// em volts referente a tensão elétrica na entrada analógica.
		Num_CAD_volts =(Num_CAD_bin*resolucao)*10;
	
		if(Num_CAD_volts<35) //se estiver "de dia"
	   		dia=1;
		else  ////se estiver "de noite"
			dia=0;
		
		if(dia) //Estado Dia
		{
			
			LED_VERDE=0;
			LED_AMARELO=0;
			for(i=10;i>0;i--)  // sinal fechado
			{	
				LED_VERMELHO=1;
				EscreveDisplay7seg(i,PONTO_NENHUM);
				atraso1seg();
			}
			LED_VERMELHO=0;
			LED_VERDE=0;
			for(i=4;i>0;i--) // sinal amarelo
			{
				LED_AMARELO=1;
				EscreveDisplay7seg(i,PONTO_NENHUM);
				atraso1seg();
			}
			LED_VERMELHO=0;
			LED_AMARELO=0;
			for(i=15;i>0;i--) // sinal verde
			{
				LED_VERDE=1;
				EscreveDisplay7seg(i,PONTO_NENHUM);
				atraso1seg();
			}
			
		}
		else    //Estado Noite
		{
			LED_VERMELHO=0;
			LED_VERDE=0;
			write_CL();
			atraso1seg();
			LED_AMARELO = !LED_AMARELO;
		}
		

	
	}//end while(1)
}//end main

/******************************************************************************
 * Funcao:        	void ConfiguraSistema(void)
 * Entrada:         Nenhuma (void)
 * Saída:          	Nenhuma (void)
 * Descrição:       InicializaSistema é a rotina de configuração principal do PIC.
 *					Seu objetivo é configurar as portas de I/O e os periféricos
 *					do microcontrolador para que os mesmos trabalhem da maneira
 *					desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema(void)
{
// Configura LED's do KitPIC: saida digital
	ADCON1 |= 0x0F; 		// configura todas as portas como digitais

 	// Configura LED's do Kit PICMINAS: saida digital
	TRISCbits.TRISC2=0; 	// RC2: saida digital - LED_VERDE
	TRISDbits.TRISD1=0; 	// RD1: saida digital - LED_VERMELHO
	TRISDbits.TRISD0=0; 	// RD0: saida digital - LED_AMARELO

	// Configura o Conversor Analogico Digital (CAD)
	OpenADC(
			//Parâmetro Config
			ADC_FOSC_64 &		// ADC_FOSC_64:		Clock de conversão do A/D igual a 
								//					FAD = FOSC/64 = 48MHz/64 = 750kHz
								//					Desta Forma, TAD=1/FAD = 1,33us.
			ADC_RIGHT_JUST & 	// ADC_RIGHT_JUST: 	Resultado da conversão ocupará os 
								//					bits menos significativos dos regis-
								//					tradores ADRESH e ADRESL.
			ADC_2_TAD, 			// ADC_2_TAD:		Determina o tempo de aquisição do CAD,
								//					o tempo para carregar o Chold, onde
								//					Taqc_min=2,45us. Deve-se escolher um
								//					multiplo de TAD que atenda esse valor,
								//					no nosso caso será igual a 2*TAD 
								//					2*TAD = 2*1,33us = 2,66us.
			//Parâmetro Config2
			ADC_CH5 & 			// ADC_CH5:			Seleciona o canal AN5 como entrada
								//					do conversor A/D.
			ADC_INT_OFF & 		// ADC_INT_OFF:		Desabilita a interrupção de términio de 
								//					conversão.
			ADC_REF_VDD_VSS,	// ADC_REF_VDD_VSS: Determina as tensões de refe-
								//  				rência do CAD:
								//					VREF+ = VDD (+5V)
								//					VREF- = VSS (0V)
			//Parâmetro PortConfig
			ADC_6ANA );			// ADC_6ANA:		Configura os pinos de AN0 a AN5
								//					como entradas analógicas
								//					AN5(RE0), AN4(RA5), AN3(RA3),
								//					AN2(RA2), AN1(RA1), AN0(RA0)
	
	// Seleciona o canal com o qual se deseja realizar uma conversão.
	SetChanADC(ADC_CH5);

	// Configura os pinos do Kit PICMINAS que estão ligados ao display duplo 
	// de 7 segmentos chamando a função da biblioteca de usuário.
	ConfiguraDisplay7seg();
	

}//end ConfiguraSistema


void atraso1seg (void)
{
	Delay10KTCYx(0);
	Delay10KTCYx(0);
	Delay10KTCYx(0);
	Delay10KTCYx(0);
	Delay10KTCYx(176);
	
}//end atraso1seg

void write_CL (void)
{
	Display_a1=0; Display_a2=1;		    
	Display_b1=1; Display_b2=1;
	Display_c1=1; Display_c2=1;
	Display_d1=0; Display_d2=0;
	Display_e1=0; Display_e2=0;
	Display_f1=0; Display_f2=0;
	Display_g1=1; Display_g2=1;  //escreve CL no display, de "closed"
}	

/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necessária para o compilador C18 saber onde é o início do vetor de
// "reset".
// Copiar na íntegra esta parte do código dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
/** EOF main.c ***************************************************************/
