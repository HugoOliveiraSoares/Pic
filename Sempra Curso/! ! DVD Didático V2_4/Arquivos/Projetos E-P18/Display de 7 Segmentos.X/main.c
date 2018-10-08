/******************************************************************************
 *
 *                      SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:          KIT E-P18 v3.6
 * Prática:	 	Uso de bibliotecas (.h) criadas pelo
 *			programdor para escrita no Display Duplo de 7 Segmentos.
 *						
 * Descrição:           Exemplificar como deve ser comentado e dividido um arquivo
 *			biblioteca (.h) criado pelo usuário. Demonstrar como adicionar
 *			e utilizar funções da biblioteca de usuário no projeto do MPLAB.
 *			Escrever os numeros decimais, entre 0 e 99, no display duplo de 
 *			7 segmentos. 
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
						// com as definições do PIC selecionado no projeto, neste
						// caso, o modelo 18F4550.
						
#include "display7seg.h" // Biblioteca de usuário com funções para utilização
						  //com o display de 7 segmentos do Kit PICMINAS v3.6



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

	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();
	
	// Laço infinito que executa a operação principal do projeto.
	while (1)
	{
			EscreveDisplay7seg (13,PONTO_NENHUM);
		
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
    // Configura os pinos do KIT E-P18 que estão ligados ao display duplo
	// de 7 segmentos chamando a função da biblioteca de usuário.
	ConfiguraDisplay7seg();
	

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
