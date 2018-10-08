/******************************************************************************
 *
 *            SEMPRATEC PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Prática_02_LCD
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
#include <p18cxxx.h>	    // Necessário para que o compilador adicione a biblioteca
			   // com as definições do PIC selecionado no projeto, neste
			  // caso, o modelo 18F4550.

#include "displayLCD.h"  // Necessário incluir a biblioteca do display de lcd

#include <delays.h>     // Necessário incluir a bliblioteca de delay para realizar o "BEEP"


/** D E F I N E S ************************************************************/

#define BOTAO_INCRE_CONFIG TRISCbits.TRISC0           // configura botão start_stop como entrada
#define BOTAO_CRES_DESCRES_CONFIG TRISCbits.TRISC1   // configura botão crescente_decrescente como entrada
#define BOTAO_RESET_CONFIG TRISCbits.TRISC2         // configura botão reset como entrada
#define BUZZER_CONFIG TRISEbits.TRISE0             // configura buzzer como saida


#define BOTAO_INCRE PORTCbits.RC0                // define para fazer a leitura do botão start, logica positiva
#define BOTAO_CRES_DESCRES PORTCbits.RC1        // define para fazer a leitura do botão stop, logica positiva
#define BOTAO_RESET PORTCbits.RC2              // define para fazer a leitura do botão reset, logica positiva

#define BUZZER LATEbits.LATE0                // definie para ligar (1) e desligar (0) o buzzer



/** V A R I A V E I S   G L O B A I S ****************************************/

int cont = 0;      // variavel inteira que salva o valor do contador
char sentido = 1; // variavel char que salva o sentido de contagem , crescente ou decrescente


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/**  P R O T O T I P O S   D A S   F U N Ç Õ E S   D E   I N T E R R U P Ç Ã O*/
void ConfiguraInterrupcao(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:          void main(void)
 * Entrada:         Nenhuma (void)
 * Saída:           Nenhuma (void)
 * Descrição:       Função principal do programa. 
 *****************************************************************************/
void main(void)
{

	// Configura as portas e periféricos do PIC.
	ConfiguraSistema();
	
	
	// Desabilita TODAS as interrupções
	INTCONbits.GIE = 0 ;

	// Inicializar o display para que não fique em branco até o usuario começar a contagem ou escolher o sentido
        PosicaoCursorLCD(1,1);                   // Função que determina a posição do cursor linha 1, coluna 1
        EscreveFraseRomLCD("Pecas Contadas :"); // Função que escreve uma frase no display, no caso Pecas Contadas
        PosicaoCursorLCD(2,1);                 // Função que determina a proxima posição do cursor linha 2, coluna 1
        EscreveInteiroLCD(cont);              // Função que escreve um numero inteiro (cont) no display

        // Laço infinito que executa a operação principal do projeto.

	while (1)
	{

            // Este if faz a leitura do botão que determina o sentido de contagem , crescente ou decrescente

            if(BOTAO_CRES_DESCRES)    // Se o BOTAO_CRES_DECRES for verdadeiro executa o if
            {
                sentido = !sentido ; // invertemos a variavel sentido, ou seja, se for 1 mundamos para 0 e vice-versa

                if(sentido) // Verifiva se a variavel sentido é positiva
                {
                    LimpaDisplay();                     // Função que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);             // Função que determina a posição do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("CRESCENTE");  // Função que escreve uma frase no display, no caso CRESCENTE

                    // Delay utilizado para que o usuario veja a mensagem no display
                    Delay10KTCYx(0);
                    Delay10KTCYx(0);

                }

                else // Verifica se a variavel sentido é falsa
                {
                    LimpaDisplay();                      // Função que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);              // Função que determina a posição do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("DECRESCENTE"); // Função que escreve uma frase no display, no caso DECRESCENTE

                    // Delay utilizado para que o usuario veja a mensagem no display
                    Delay10KTCYx(0);
                    Delay10KTCYx(0);
                }

                
                while(BOTAO_CRES_DESCRES) // While utizado para evitar o debounce do BOTAO_CRES_DESCRES
                {
                    
                }

                // Apos a escolha do sentido de contagem retornamos com a informação Pecas Contadas e o numero de pecas

                LimpaDisplay();                            // Função que limpa qq escrita anterior no display
                PosicaoCursorLCD(1,1);                    // Função que determina a posição do cursor linha 1, coluna 1
                EscreveFraseRomLCD("Pecas Contadas :");  // Função que escreve uma frase no display, no caso Pecas Contadas
                PosicaoCursorLCD(2,1);                  // Função que determina a posição do cursor linha 2, coluna 1
                EscreveInteiroLCD(cont);               // Função que escreve um numero inteiro (cont) no display
                
            }

            // Este if faz a leitura do botao que incrementa ou decrementa o valor do contador

            if(BOTAO_INCRE)
            {

                if(sentido)    // if que verifica se a variavel sentido é posisita (crescente)
                {
                    cont++;   // caso sentido seja verdadeiro soma-se um na variavel inteira cont
                    LimpaDisplay();                             // Função que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);                     // Função que determina a posição do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("Pecas Contadas :");   // Função que escreve uma frase no display, no caso Pecas Contadas
                    PosicaoCursorLCD(2,1);                   // Função que determina a posição do cursor linha 2, coluna 1
                    EscreveInteiroLCD(cont);                // Função que escreve um numero inteiro (cont) no display

                }

                else         // Verifica se a variavel sentido é negativa (decrescente)
                {
                    cont--; // caso sentido seja falsa diminiui-se um na variavel inteira cont

                    if(cont <= 0)  // if que verifica se o numero de peças contadas é zero ou negativa
                    {
                        cont = 0; // cont recebe o valor zero pq não existe contagem negativa do numero de peças
                    }

                    LimpaDisplay();                            // Função que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);                    // Função que determina a posição do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("Pecas Contadas :");  // Função que escreve uma frase no display, no caso Pecas Contadas
                    PosicaoCursorLCD(2,1);                  // Função que determina a posição do cursor linha 2, coluna 1
                    EscreveInteiroLCD(cont);               // Função que escreve um numero inteiro (cont) no display

                }

                if(cont % 10 == 0) // if que verifica se a variavel se o valor atual da variavel cont é multiplo de 10
                {                 // se cont for divido por 10 e o resto da divisão for zero , significa que cont é multiplo de 10

                    BUZZER = 1;        // o pino que está ligado o buzzer recebe nivel logico 1
                    Delay10KTCYx(0);  // delay utilazdo para realizar o beep
                    BUZZER = 0;      // o pino que está ligado o buzzer recebe nivel logico 0

                }

                while(BOTAO_INCRE) // While utizado para evitar o debounce do BOTAO_CRES_DESCRES
                {

                }

            }

            // Este if faz a leitura do botão que faz o reset do contador, ou seja , zera a variavel cont

            if(BOTAO_RESET) // verifica se o BOTAO_RESET é verdadeiro
            {
                cont = 0;  // variavel cont recebe zero
                LimpaDisplay();                           // Função que limpa qq escrita anterior no display
                PosicaoCursorLCD(1,1);                   // Função que determina a posição do cursor linha 1, coluna 1
                EscreveFraseRomLCD("Pecas Contadas :"); // Função que escreve uma frase no display, no caso Pecas Contadas
                PosicaoCursorLCD(2,1);                 // Função que determina a posição do cursor linha 2, coluna 1
                EscreveInteiroLCD(cont);              // Função que escreve um numero inteiro (cont) no display

                while(BOTAO_RESET)  // While utizado para evitar o debounce do BOTAO_RESET
                {
                    
                }

            }

                    
		
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
        LimpaDisplay();

        BOTAO_INCRE_CONFIG = 1;
        BOTAO_CRES_DESCRES_CONFIG = 1;
        BOTAO_RESET_CONFIG = 1;
        BUZZER_CONFIG = 0;

        BUZZER = 0;
		
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