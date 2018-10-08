/******************************************************************************
 *
 *           SEMPRA PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo)	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 * Pr�tica: 		Sensores visualizados no LCD
 * Descri��o:        	Este projeto usa o conversor A/D do PIC18F4550 para ler
 *			os valores do potenciometro, do sensor de temperatura e
 *			do LDR e mostrar no display de LCD
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
						// com as defini��es do PIC selecionado no projeto, neste
						// caso, o modelo 18F4550.
#include <string.h>		// Biblioteca do compilador para uso de strings
#include <adc.h>		// Biblioteca do compilador para trabalhar com o m�dulo de conversor AD.
#include "displayLCD.h"

/** D E F I N E s  ***********************************************************/			
			 
#define VDD 5			

/** V A R I A V E I S   G L O B A I S ****************************************/

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);
void HighPriorityISRCode();
void LowPriorityISRCode();
/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:        	void main(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Fun��o principal do programa. 
 *****************************************************************************/
void main(void)
{
	int Num_CAD_bin = 0;
	float Num_CAD_volts = 0.0;
	unsigned char Num_CAD_graus = 0;
	float resolucao = VDD/1023.0;
	int i;
	ConfiguraSistema();		// Configura as portas e perif�ricos do PIC.

    while(1)				// La�o infinito que executa o funcionamento principal do projeto.
   { 
		// Temperatura
	
		EnderecoCursor(0x00);
		EscreveFraseRomLCD("TEMP:");
                SetChanADC(ADC_CH0);
		for(i = 0; i < 5; i++)
		{
			Delay100TCYx(1);
			if(!BusyADC())
			{ 	
				// L� o valor convertido e armazena na vari�vel
				Num_CAD_bin=ReadADC();
				// Inicia a nova Convers�o
				ConvertADC();
			}
		}				
		Num_CAD_volts = Num_CAD_bin*resolucao;
		Num_CAD_graus = (Num_CAD_volts*100)-50; 
		EnderecoCursor(0x05);
		EscreveInteiroLCD(Num_CAD_graus);
		EnderecoCursor(0x07);
		EscreveFraseRomLCD("C");
		
		// Luminosidade
	
		SetChanADC(ADC_CH5);
		for(i = 0; i < 5; i++)
		{
			Delay100TCYx(1);
			if(!BusyADC())
			{ 	
				// L� o valor convertido e armazena na vari�vel
				Num_CAD_bin=ReadADC();
				// Inicia a nova Convers�o
				ConvertADC();
			}
		}
		Num_CAD_volts = Num_CAD_bin*resolucao;
		EnderecoCursor(0x09);
		EscreveCaractereLCD('L');
		EscreveCaractereLCD('M');
		EscreveCaractereLCD(':');
		EscreveInteiroLCD(Num_CAD_volts);
		EscreveFraseRomLCD(".");
		EscreveInteiroLCD((int)(Num_CAD_volts*10)%10);
		EscreveFraseRomLCD("V");
		// POT
	
		SetChanADC(ADC_CH4);
		for(i = 0; i < 5; i++)
		{
			Delay100TCYx(1);
			if(!BusyADC())
			{ 	
				// L� o valor convertido e armazena na vari�vel
				Num_CAD_bin=ReadADC();						
				// Inicia a nova Convers�o
				ConvertADC();
			}
		}
		Num_CAD_volts = Num_CAD_bin*resolucao;
		EnderecoCursor(0x40);
		EscreveFraseRomLCD("POT:");
		EnderecoCursor(0x44);
		EscreveInteiroLCD(Num_CAD_volts);
		EnderecoCursor(0x45);
		EscreveFraseRomLCD(".");
		EscreveInteiroLCD((int)(Num_CAD_volts*10)%10);
		EscreveFraseRomLCD("V");

	}//end while(1)
}//end main

/******************************************************************************
 * Funcao:        	void ConfiguraSistema(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       InicializaSistema � a rotina de configura��o principal do PIC.
 *					Seu objetivo � configurar as portas de I/O e os perif�ricos
 *					do microcontrolador para que os mesmos trabalhem da maneira
 *					desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema(void)
{

// Configura LED's do KitPIC: saida digital
	ADCON1 |= 0x0F; 		// configura todas as portas como digitais

	//Configura o conversor AD
	OpenADC(
				 //Par�metro Config
				 ADC_FOSC_64 &	
				 ADC_RIGHT_JUST & 
				 ADC_2_TAD, 	
				 ADC_CH0 & 
				 ADC_INT_OFF & 
				 ADC_REF_VDD_VSS,
				 ADC_6ANA );	

	ConfiguraLCD();	 // Inicializa o LCD
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necess�ria para o compilador C18 saber onde � o in�cio do vetor de
// "reset".
// Copiar na �ntegra esta parte do c�digo dentro do arquivo "main.c" de TODO 
// projeto usado com o Bootloader no PIC.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = 0x1000
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
/** EOF main.c ***************************************************************/
