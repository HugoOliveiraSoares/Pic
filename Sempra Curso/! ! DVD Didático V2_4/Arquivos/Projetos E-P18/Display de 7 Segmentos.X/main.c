/******************************************************************************
 *
 *                      SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:          KIT E-P18 v3.6
 * Pr�tica:	 	Uso de bibliotecas (.h) criadas pelo
 *			programdor para escrita no Display Duplo de 7 Segmentos.
 *						
 * Descri��o:           Exemplificar como deve ser comentado e dividido um arquivo
 *			biblioteca (.h) criado pelo usu�rio. Demonstrar como adicionar
 *			e utilizar fun��es da biblioteca de usu�rio no projeto do MPLAB.
 *			Escrever os numeros decimais, entre 0 e 99, no display duplo de 
 *			7 segmentos. 
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
						// com as defini��es do PIC selecionado no projeto, neste
						// caso, o modelo 18F4550.
						
#include "display7seg.h" // Biblioteca de usu�rio com fun��es para utiliza��o
						  //com o display de 7 segmentos do Kit PICMINAS v3.6



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

	// Configura as portas e perif�ricos do PIC.
	ConfiguraSistema();
	
	// La�o infinito que executa a opera��o principal do projeto.
	while (1)
	{
			EscreveDisplay7seg (13,PONTO_NENHUM);
		
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
    // Configura os pinos do KIT E-P18 que est�o ligados ao display duplo
	// de 7 segmentos chamando a fun��o da biblioteca de usu�rio.
	ConfiguraDisplay7seg();
	

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
