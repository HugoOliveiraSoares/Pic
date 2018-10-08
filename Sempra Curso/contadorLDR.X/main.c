/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:		main_ContLDR.c
 * Dependencias:		Veja a seção INCLUDES abaixo
 * Microcontrolador:            PIC18F4550
 * Opção de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:			C18 v3.37 ou superior
 * Empresa:			SEMPRA
 * Plataforma:			Placa E-P18 v3.6 ou E-PX MINI
 * Autor:			SEMPRA
 * Versão:			v1.0
 * Descrição:	Prática 15: Conversor AD e Potenciometro
 *		Utilizar o display de LCD para mostrar o valor da tensão medida no 
 *              pino RA5/AN4, onde está conectado um Potenciômetro.
 *		Utilize a biblioteca <adc.h> para configurar e usar o CAD.
 *		Utilize a biblioteca "displayLCD.h" para configurar e usar o display LCD.
 * desligado = 400r
 * ligado = 60r
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include <adc.h>	// Biblioteca C18 com funções para Conversor AD
#include "displayLCD.h"// Biblioteca com funções para o Display LCD
#include <delays.h>

#define RESOLUCAO (5.0/1023.0) // Resolução do CAD de 10bits = 5V/(2^10-1)

void ConfiguraSistema(void);

void main(void)
{
	int cont = 0;
    int resultadoBin = 0;	  // Guarda o valor da conversão AD em BINÁRIO.
	float resolucao = RESOLUCAO; // Guarda o valor da resolução do conversor AD.
		
	ConfiguraSistema(); //Função que faz configurações do firmware
		
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
        
		// Verifica se o CAD terminou uma conversão
		if( !BusyADC() ) 
		{
			resultadoBin = ReadADC(); // Guarda o resultado da conversão
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
 * Saída:		Nenhuma (void)
 * Descrição:	ConfiguraSistema é a rotina de configuração principal do PIC.
 *		Seu objetivo é configurar as portas de I/O e os periféricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
	TRISCbits.TRISC2 = 0;
    ADCON1 = ADCON1 | 0x0f; // Desabilita pinos analógicos
	ConfiguraLCD(); // Configura o Diaplay LCD
	// Configura o Conversor Analogico Digital (CAD)
	OpenADC(
		  //Parâmetro Config
		  ADC_FOSC_64		&	//Clock do AD como FOSC/64
		  ADC_RIGHT_JUST	&	//Justificando a direita
		  ADC_2_TAD,			//Tempo de aquisição de 2 TAD
		  //Parâmetro Config2
		  ADC_CH5		&	//Canal 5
		  ADC_INT_OFF   	&	//Não utiliza interrupção
		  ADC_REF_VDD_VSS,              //Tensoes de referencia
		  //Parâmetro PortConfig
		  ADC_5ANA );			//Habilita 5 Portas analógicas (AN0 - AN4)
}//end ConfiguraSistema


/** V E C T O R   R E M A P P I N G ******************************************/
// Rotina necessária para o compilador C18 saber onde é o início do vetor de
// "reset".
// ATENÇÃO: Copiar esta parte do código dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para gravação in-circuit.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
	_asm goto _startup _endasm
}
#pragma code	// Diretiva que retorna a alocação dos endereços 
				// da memória de programa para seus valores padrão

/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** FIM DO ARQUIVO main.c ***************************************************************/
