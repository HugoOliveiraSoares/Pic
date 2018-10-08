/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:		main_ContLDR.c
 * Dependencias:		Veja a se��o INCLUDES abaixo
 * Microcontrolador:            PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:			C18 v3.37 ou superior
 * Empresa:			SEMPRA
 * Plataforma:			Placa E-P18 v3.6 ou E-PX MINI
 * Autor:			SEMPRA
 * Vers�o:			v1.0
 * Descri��o:	Pr�tica 15: Conversor AD e Potenciometro
 *		Utilizar o display de LCD para mostrar o valor da tens�o medida no 
 *              pino RA5/AN4, onde est� conectado um Potenci�metro.
 *		Utilize a biblioteca <adc.h> para configurar e usar o CAD.
 *		Utilize a biblioteca "displayLCD.h" para configurar e usar o display LCD.
 * desligado = 400r
 * ligado = 60r
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include <adc.h>	// Biblioteca C18 com fun��es para Conversor AD
#include "displayLCD.h"// Biblioteca com fun��es para o Display LCD
#include <delays.h>

#define RESOLUCAO (5.0/1023.0) // Resolu��o do CAD de 10bits = 5V/(2^10-1)

void ConfiguraSistema(void);

void main(void)
{
	int cont = 0;
    int resultadoBin = 0;	  // Guarda o valor da convers�o AD em BIN�RIO.
	float resolucao = RESOLUCAO; // Guarda o valor da resolu��o do conversor AD.
		
	ConfiguraSistema(); //Fun��o que faz configura��es do firmware
		
	//Escreve msg inicial no LCD
	PosicaoCursorLCD(1,1);
	EscreveFraseRomLCD("ContadorLDR");
	
	SelChanConvADC(ADC_CH5); // Inicia a primeira medida
	
	while(1)
	{
        LATCbits.LATC2 = 1;
        Delay100TCYx(200);
        Delay100TCYx(200);
        LATCbits.LATC2 = 0;
        Delay100TCYx(200);
        Delay100TCYx(200);
        
		// Verifica se o CAD terminou uma convers�o
		if( !BusyADC() ) 
		{
			resultadoBin = ReadADC(); // Guarda o resultado da convers�o
			ConvertADC();//Inicia a nova medida
		}
		//Escreve no LCD, valor em Decimal
		PosicaoCursorLCD(2,1);
		EscreveInteiroLCD(resultadoBin);
		EscreveFraseRomLCD(" : ");
        if(resultadoBin <= 200 )
        {
          
            while(resultadoBin <= 200 )
            {
                cont += 1;
                EscreveInteiroLCD(cont);
             }
            
        }
        
	}//end while(1)
}//end main


/******************************************************************************
 * Funcao:		void ConfiguraSistema(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	ConfiguraSistema � a rotina de configura��o principal do PIC.
 *		Seu objetivo � configurar as portas de I/O e os perif�ricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
	TRISCbits.TRISC2 = 0;
    ADCON1 = ADCON1 | 0x0f; // Desabilita pinos anal�gicos
	ConfiguraLCD(); // Configura o Diaplay LCD
	// Configura o Conversor Analogico Digital (CAD)
	OpenADC(
		  //Par�metro Config
		  ADC_FOSC_64		&	//Clock do AD como FOSC/64
		  ADC_RIGHT_JUST	&	//Justificando a direita
		  ADC_2_TAD,			//Tempo de aquisi��o de 2 TAD
		  //Par�metro Config2
		  ADC_CH5		&	//Canal 5
		  ADC_INT_OFF   	&	//N�o utiliza interrup��o
		  ADC_REF_VDD_VSS,              //Tensoes de referencia
		  //Par�metro PortConfig
		  ADC_5ANA );			//Habilita 5 Portas anal�gicas (AN0 - AN4)
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necess�ria para o compilador C18 saber onde � o in�cio do vetor de
// "reset".
// ATEN��O: Copiar esta parte do c�digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para grava��o in-circuit.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
	_asm goto _startup _endasm
}
#pragma code	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o

/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** FIM DO ARQUIVO main.c ***************************************************************/
