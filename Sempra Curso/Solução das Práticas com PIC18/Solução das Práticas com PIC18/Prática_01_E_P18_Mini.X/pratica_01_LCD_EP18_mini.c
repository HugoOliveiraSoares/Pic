/******************************************************************************
 *
 *            SEMPRATEC PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Prática_01_LCD
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:        	C18 v3.37 ou superior
 * Empresa:         	SEMPRATEC
 * Prática: 			
 * Plataforma:          E-P18 Mini
 * Autor:		SEMPRATEC
 * Versão:		v1.0
 * Descrição:   	 
 *
 *
 *
 *
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include "displayLCD.h" // Necessário incluir a biblioteca do display de lcd


/** D E F I N E S ************************************************************/


/** V A R I A V E I S   G L O B A I S ****************************************/

char frase[17] = "sempratec.com.br" ; // variavel criada na RAM


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/**  P R O T O T I P O S   D A S   F U N Ç Õ E S   D E   I N T E R R U P Ç Ã O*/
void ConfiguraInterrupcao(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:        	void main(void)
 * Entrada:         Nenhuma (void)
 * Saída:          	Nenhuma (void)
 * Descrição:       Função principal do programa. 
 *****************************************************************************/
void main(void)
{

	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();
	
	
	// desabilita TODAS as interrupções
	INTCONbits.GIE = 0 ;

        LimpaDisplay(); // função que limpa o display de lcd
	
	// Laço infinito que executa a operação principal do projeto.

	while (1)
	{
            
            PosicaoCursorLCD(1,1); // função que posiciona o cursor do lcd na linha 1 e coluna 1
            EscreveFraseRomLCD(" Curso Sempra "); // função que escrevre uma frase no display (ROM)

            PosicaoCursorLCD(2,1); // função que posiciona o cursor do lcd na linha 2 e coluna 1
            EscreveFraseRamLCD(frase); // função que escrevre uma frase no display (RAM)
            
		
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
	// Desabilita todas as 13 portas analógicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Função que configura as interrupções do sistema
	ConfiguraInterrupcao();

        ConfiguraLCD(); // Função que deve ser chamada para configurar o display de lcd
		
}//end ConfiguraSistema


/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Saída:          Nenhuma (void)
 * Descrição:      Função que configura as interrupções utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{


}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de ALTA prioridade
 *				Nessa função deve-se lembrar de fazer a seguinte lista:
 *					1- verificar qual foi a causa da interrupção, comparando 
 *				os flags de cada tipo de interrupção.
 *					2- tratar a interrupção selecionada.
 *					3- limpar o flag que causou a interrupção!!! Importante 
 *				para garantir que não ocorrerá uma chamada indesejada ao sair 
 *				do tratamento da interrupção.
 *
 *				Ao sair dessa função é usado o retorno do tipo "retfie fast",
 *				pois esta função é declarada como ALTA prioridade com a diretiva
 *				#pragma interrupt
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	// Escreva a função de tratamento de interrupção de alta prioridade aqui
	
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de BAIXA prioridade
 *				Nessa função deve-se lembrar de fazer a seguinte lista:
 *					1- verificar qual foi a causa da interrupção, comparando 
 *				os flags de cada tipo de interrupção.
 *					2- tratar a interrupção selecionada.
 *					3- limpar o flag que causou a interrupção!!! Importante 
 *				para garantir que não ocorrerá uma chamada indesejada ao sair 
 *				do tratamento da interrupção.
 *
 *				Ao sair dessa função é usado o retorno do tipo "retfie",
 *				pois esta função é declarada como BAIXA prioridade com a diretiva
 *				#pragma interruptlow
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrupção de baixa prioridade aqui

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Seção necessária para informar ao compilador C18 onde são os novos endereços
//da memória de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupção.

//
//ATENÇÃO: COPIAR ESTA SEÇÃO DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
//UTILIZAM O BOOTLOADER PARA GRAVAÇÃO IN-CIRCUIT.

// protótipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocação da função de tratamento do "reset" da aplicação principal 
// no endereço 0x800 da memória de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Alocação da função de tratamento das interrupções de ALTA prioridade
// no endereço 0x808 da memória de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Alocação da função de tratamento das interrupções de BAIXA prioridade 
// no endereço 0x818 da memória de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code  	// Diretiva que retorna a alocação dos endereços 
				// da memória de programa para seus valores padrão

/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/