#include<p18cxxx.h>
#include"displayLCD.h"

void ConfiguraSistema(void);


void main(void)
{
	ConfiguraSistema();


	EnderecoCursor(0x00);

	EscreveFraseRomLCD("OLA MUND0");

	while(1)
   	{ 
		
	}//end while
    
}//end main

void ConfiguraSistema (void)
{
	// Desabilita todas as 13 portas anal�gicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	//Configura os pinos que s�o usados pelo LCD 16x2 alfa-numerico
	ConfiguraLCD();
	
}

/** V E C T O R   R E M A P P I N G ******************************************/

// ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x1000 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
