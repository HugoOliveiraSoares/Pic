/******************************************************************************
 *
 *            SEMPRATEC PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Pr�tica_02_LCD
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:        	C18 v3.37 ou superior
 * Empresa:         	SEMPRATEC
 * Pr�tica: 			
 * Plataforma:          E-P18 Mini
 * Autor:		SEMPRATEC
 * Vers�o:		v1.0
 * Descri��o:   	
 *
 *
 *
 *
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	    // Necess�rio para que o compilador adicione a biblioteca
			   // com as defini��es do PIC selecionado no projeto, neste
			  // caso, o modelo 18F4550.

#include "displayLCD.h"  // Necess�rio incluir a biblioteca do display de lcd

#include <delays.h>     // Necess�rio incluir a bliblioteca de delay para realizar o "BEEP"


/** D E F I N E S ************************************************************/

#define BOTAO_INCRE_CONFIG TRISCbits.TRISC0           // configura bot�o start_stop como entrada
#define BOTAO_CRES_DESCRES_CONFIG TRISCbits.TRISC1   // configura bot�o crescente_decrescente como entrada
#define BOTAO_RESET_CONFIG TRISCbits.TRISC2         // configura bot�o reset como entrada
#define BUZZER_CONFIG TRISEbits.TRISE0             // configura buzzer como saida


#define BOTAO_INCRE PORTCbits.RC0                // define para fazer a leitura do bot�o start, logica positiva
#define BOTAO_CRES_DESCRES PORTCbits.RC1        // define para fazer a leitura do bot�o stop, logica positiva
#define BOTAO_RESET PORTCbits.RC2              // define para fazer a leitura do bot�o reset, logica positiva

#define BUZZER LATEbits.LATE0                // definie para ligar (1) e desligar (0) o buzzer



/** V A R I A V E I S   G L O B A I S ****************************************/

int cont = 0;      // variavel inteira que salva o valor do contador
char sentido = 1; // variavel char que salva o sentido de contagem , crescente ou decrescente


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema (void);


/**  P R O T O T I P O S   D A S   F U N � � E S   D E   I N T E R R U P � � O*/
void ConfiguraInterrupcao(void);
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:          void main(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:           Nenhuma (void)
 * Descri��o:       Fun��o principal do programa. 
 *****************************************************************************/
void main(void)
{

	// Configura as portas e perif�ricos do PIC.
	ConfiguraSistema();
	
	
	// Desabilita TODAS as interrup��es
	INTCONbits.GIE = 0 ;

	// Inicializar o display para que n�o fique em branco at� o usuario come�ar a contagem ou escolher o sentido
        PosicaoCursorLCD(1,1);                   // Fun��o que determina a posi��o do cursor linha 1, coluna 1
        EscreveFraseRomLCD("Pecas Contadas :"); // Fun��o que escreve uma frase no display, no caso Pecas Contadas
        PosicaoCursorLCD(2,1);                 // Fun��o que determina a proxima posi��o do cursor linha 2, coluna 1
        EscreveInteiroLCD(cont);              // Fun��o que escreve um numero inteiro (cont) no display

        // La�o infinito que executa a opera��o principal do projeto.

	while (1)
	{

            // Este if faz a leitura do bot�o que determina o sentido de contagem , crescente ou decrescente

            if(BOTAO_CRES_DESCRES)    // Se o BOTAO_CRES_DECRES for verdadeiro executa o if
            {
                sentido = !sentido ; // invertemos a variavel sentido, ou seja, se for 1 mundamos para 0 e vice-versa

                if(sentido) // Verifiva se a variavel sentido � positiva
                {
                    LimpaDisplay();                     // Fun��o que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);             // Fun��o que determina a posi��o do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("CRESCENTE");  // Fun��o que escreve uma frase no display, no caso CRESCENTE

                    // Delay utilizado para que o usuario veja a mensagem no display
                    Delay10KTCYx(0);
                    Delay10KTCYx(0);

                }

                else // Verifica se a variavel sentido � falsa
                {
                    LimpaDisplay();                      // Fun��o que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);              // Fun��o que determina a posi��o do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("DECRESCENTE"); // Fun��o que escreve uma frase no display, no caso DECRESCENTE

                    // Delay utilizado para que o usuario veja a mensagem no display
                    Delay10KTCYx(0);
                    Delay10KTCYx(0);
                }

                
                while(BOTAO_CRES_DESCRES) // While utizado para evitar o debounce do BOTAO_CRES_DESCRES
                {
                    
                }

                // Apos a escolha do sentido de contagem retornamos com a informa��o Pecas Contadas e o numero de pecas

                LimpaDisplay();                            // Fun��o que limpa qq escrita anterior no display
                PosicaoCursorLCD(1,1);                    // Fun��o que determina a posi��o do cursor linha 1, coluna 1
                EscreveFraseRomLCD("Pecas Contadas :");  // Fun��o que escreve uma frase no display, no caso Pecas Contadas
                PosicaoCursorLCD(2,1);                  // Fun��o que determina a posi��o do cursor linha 2, coluna 1
                EscreveInteiroLCD(cont);               // Fun��o que escreve um numero inteiro (cont) no display
                
            }

            // Este if faz a leitura do botao que incrementa ou decrementa o valor do contador

            if(BOTAO_INCRE)
            {

                if(sentido)    // if que verifica se a variavel sentido � posisita (crescente)
                {
                    cont++;   // caso sentido seja verdadeiro soma-se um na variavel inteira cont
                    LimpaDisplay();                             // Fun��o que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);                     // Fun��o que determina a posi��o do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("Pecas Contadas :");   // Fun��o que escreve uma frase no display, no caso Pecas Contadas
                    PosicaoCursorLCD(2,1);                   // Fun��o que determina a posi��o do cursor linha 2, coluna 1
                    EscreveInteiroLCD(cont);                // Fun��o que escreve um numero inteiro (cont) no display

                }

                else         // Verifica se a variavel sentido � negativa (decrescente)
                {
                    cont--; // caso sentido seja falsa diminiui-se um na variavel inteira cont

                    if(cont <= 0)  // if que verifica se o numero de pe�as contadas � zero ou negativa
                    {
                        cont = 0; // cont recebe o valor zero pq n�o existe contagem negativa do numero de pe�as
                    }

                    LimpaDisplay();                            // Fun��o que limpa qq escrita anterior no display
                    PosicaoCursorLCD(1,1);                    // Fun��o que determina a posi��o do cursor linha 1, coluna 1
                    EscreveFraseRomLCD("Pecas Contadas :");  // Fun��o que escreve uma frase no display, no caso Pecas Contadas
                    PosicaoCursorLCD(2,1);                  // Fun��o que determina a posi��o do cursor linha 2, coluna 1
                    EscreveInteiroLCD(cont);               // Fun��o que escreve um numero inteiro (cont) no display

                }

                if(cont % 10 == 0) // if que verifica se a variavel se o valor atual da variavel cont � multiplo de 10
                {                 // se cont for divido por 10 e o resto da divis�o for zero , significa que cont � multiplo de 10

                    BUZZER = 1;        // o pino que est� ligado o buzzer recebe nivel logico 1
                    Delay10KTCYx(0);  // delay utilazdo para realizar o beep
                    BUZZER = 0;      // o pino que est� ligado o buzzer recebe nivel logico 0

                }

                while(BOTAO_INCRE) // While utizado para evitar o debounce do BOTAO_CRES_DESCRES
                {

                }

            }

            // Este if faz a leitura do bot�o que faz o reset do contador, ou seja , zera a variavel cont

            if(BOTAO_RESET) // verifica se o BOTAO_RESET � verdadeiro
            {
                cont = 0;  // variavel cont recebe zero
                LimpaDisplay();                           // Fun��o que limpa qq escrita anterior no display
                PosicaoCursorLCD(1,1);                   // Fun��o que determina a posi��o do cursor linha 1, coluna 1
                EscreveFraseRomLCD("Pecas Contadas :"); // Fun��o que escreve uma frase no display, no caso Pecas Contadas
                PosicaoCursorLCD(2,1);                 // Fun��o que determina a posi��o do cursor linha 2, coluna 1
                EscreveInteiroLCD(cont);              // Fun��o que escreve um numero inteiro (cont) no display

                while(BOTAO_RESET)  // While utizado para evitar o debounce do BOTAO_RESET
                {
                    
                }

            }

                    
		
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
	// Desabilita todas as 13 portas anal�gicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Fun��o que configura as interrup��es do sistema
	ConfiguraInterrupcao();

        ConfiguraLCD(); // Fun��o que deve ser chamada para configurar o display de lcd
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
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Fun��o que configura as interrup��es utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{


}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de ALTA prioridade
 *				Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *					1- verificar qual foi a causa da interrup��o, comparando 
 *				os flags de cada tipo de interrup��o.
 *					2- tratar a interrup��o selecionada.
 *					3- limpar o flag que causou a interrup��o!!! Importante 
 *				para garantir que n�o ocorrer� uma chamada indesejada ao sair 
 *				do tratamento da interrup��o.
 *
 *				Ao sair dessa fun��o � usado o retorno do tipo "retfie fast",
 *				pois esta fun��o � declarada como ALTA prioridade com a diretiva
 *				#pragma interrupt
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	// Escreva a fun��o de tratamento de interrup��o de alta prioridade aqui
	
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de BAIXA prioridade
 *				Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *					1- verificar qual foi a causa da interrup��o, comparando 
 *				os flags de cada tipo de interrup��o.
 *					2- tratar a interrup��o selecionada.
 *					3- limpar o flag que causou a interrup��o!!! Importante 
 *				para garantir que n�o ocorrer� uma chamada indesejada ao sair 
 *				do tratamento da interrup��o.
 *
 *				Ao sair dessa fun��o � usado o retorno do tipo "retfie",
 *				pois esta fun��o � declarada como BAIXA prioridade com a diretiva
 *				#pragma interruptlow
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interruptlow = Baixa prioridade
#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{
	//Escreva o codigo de tratamento da interrup��o de baixa prioridade aqui

}//end Tratamento_Low_Interrupt


/** V E C T O R   R E M A P P I N G ******************************************/
// Se��o necess�ria para informar ao compilador C18 onde s�o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup��o.

//
//ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS QUE
//UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x800 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x808 da mem�ria de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de BAIXA prioridade 
// no endere�o 0x818 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o

/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/