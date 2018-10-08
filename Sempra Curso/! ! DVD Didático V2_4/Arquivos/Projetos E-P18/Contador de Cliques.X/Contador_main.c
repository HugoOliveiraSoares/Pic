/******************************************************************************
 *
 *                       SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P18 V3.6
 * Prática:	 	Contador de cliques
 *						
 *						
 * Descrição: 	       Este projeto é um contador de cliques. 
 *                     O display duplo de 7 segmentos é utilizado para mostar
 *                     o valor atual. O programa começa a contagem do núemro 0,
 *                     a cada clique do botão1 (RE1) o contador é incrementado.
 *                     A cada clique do botão2 o contador é decrementado.
 *                     O contador trabalha apenas na faixa de 00 a 99.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.
						
#include "display7seg.h" // Biblioteca de usuário com funções para utilização
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
 * Saída:      	Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa principal,
 *				pois esta é a primeira a ser chamada após o	reset do 
 *				microcontrolador.
 *				Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{ 
	char contador = 0;
	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();
	
	// Laço infinito que executa a operação principal do projeto.
	while (1)
	{
		if(BOTAO_1)
		{
		   Delay10KTCYx(255); //Debauncer para tirar ruido da chave
		   if(contador < 99)
		   {
				contador ++;
		   }
		   while(BOTAO_1); // Aguarda o usuário soltar o botão
		}
		if(BOTAO_2)
		{
			Delay10KTCYx(255); //Debauncer para tirar ruido da chave
		   if(contador > 0)
		   {
				contador --;
		   }
		   while(BOTAO_2); // Aguarda o usuário soltar o botão
		}
		
		EscreveDisplay7seg (contador,PONTO_NENHUM);
		
	}//end while
}//end main

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:  	ConfiguraSistema é a rotina de configuração principal do projeto.
 *				Seu objetivo é configurar as portas de I/O e os demais periféricos
 *				do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
    ADCON1 |= 0x0F; //Configura todas as portas de I/O como digitais.
    // Configura os pinos do Kit PICMINAS que estão ligados ao display duplo 
	// de 7 segmentos chamando a função da biblioteca de usuário.
	ConfiguraDisplay7seg();
	
	//CONFIGURA OS BOTOES 1 e 2 como ENTRADAS digitias
	TRISEbits.TRISE1 = 1; // BOTAO 1 
	TRISEbits.TRISE2 = 1; // BOTAO 2

}//end ConfiguraSistema

/** V E C T O R   R E M A P P I N G ******************************************/

// ATENÇÃO: COPIAR ESTA SEÇÃO DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
// UTILIZAM O BOOTLOADER PARA GRAVAÇÃO IN-CIRCUIT.

// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal 
// no endereço 0x800 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code  	// Diretiva que retorna a alocação dos endereços 
				// da memória de programa para seus valores padrão
/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
