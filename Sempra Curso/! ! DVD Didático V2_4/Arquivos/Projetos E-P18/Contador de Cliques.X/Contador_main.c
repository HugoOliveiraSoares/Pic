/******************************************************************************
 *
 *                       SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P18 V3.6
 * Pr�tica:	 	Contador de cliques
 *						
 *						
 * Descri��o: 	       Este projeto � um contador de cliques. 
 *                     O display duplo de 7 segmentos � utilizado para mostar
 *                     o valor atual. O programa come�a a contagem do n�emro 0,
 *                     a cada clique do bot�o1 (RE1) o contador � incrementado.
 *                     A cada clique do bot�o2 o contador � decrementado.
 *                     O contador trabalha apenas na faixa de 00 a 99.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.
						
#include "display7seg.h" // Biblioteca de usu�rio com fun��es para utiliza��o
			 //com o display de 7 segmentos do KIT E-P18 v3.6
#include <delays.h>
/** D E F I N E S ************************************************************/

#define BOTAO_1 PORTEbits.RE1
#define BOTAO_2 PORTEbits.RE2

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *				pois esta � a primeira a ser chamada ap�s o	reset do 
 *				microcontrolador.
 *				Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{ 
	char contador = 0;
	// Configura as portas e perif�ricos do PIC.
	ConfiguraSistema();
	
	// La�o infinito que executa a opera��o principal do projeto.
	while (1)
	{
		if(BOTAO_1)
		{
		   Delay10KTCYx(255); //Debauncer para tirar ruido da chave
		   if(contador < 99)
		   {
				contador ++;
		   }
		   while(BOTAO_1); // Aguarda o usu�rio soltar o bot�o
		}
		if(BOTAO_2)
		{
			Delay10KTCYx(255); //Debauncer para tirar ruido da chave
		   if(contador > 0)
		   {
				contador --;
		   }
		   while(BOTAO_2); // Aguarda o usu�rio soltar o bot�o
		}
		
		EscreveDisplay7seg (contador,PONTO_NENHUM);
		
	}//end while
}//end main

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	ConfiguraSistema � a rotina de configura��o principal do projeto.
 *				Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *				do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
    ADCON1 |= 0x0F; //Configura todas as portas de I/O como digitais.
    // Configura os pinos do Kit PICMINAS que est�o ligados ao display duplo 
	// de 7 segmentos chamando a fun��o da biblioteca de usu�rio.
	ConfiguraDisplay7seg();
	
	//CONFIGURA OS BOTOES 1 e 2 como ENTRADAS digitias
	TRISEbits.TRISE1 = 1; // BOTAO 1 
	TRISEbits.TRISE2 = 1; // BOTAO 2

}//end ConfiguraSistema

/** V E C T O R   R E M A P P I N G ******************************************/

// ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x800 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
