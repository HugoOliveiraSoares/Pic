/******************************************************************************
 *
 *                          SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-P18mini V 1.0
 * Prática:	 	CRONOMETRO
 *
 * Autor:               Bruno A. Dayrell
 * Versão:		v1.0	
 *						
 * Descrição:       	Cronometro progressivo contínuo, que a cada vez em que 
 *			o botão RA3 é apertado, ele atualiza na tela o valor
 *			atual do contador. Utilização do periférico timer para 
 *                      a contagem.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
			// com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include <timers.h>	// Biblioteca do comipilador que possui as funções básicas
			// de registros e configurações dos periféricos timers


#include "displayLCD_mini.h"	// Versão da biblioteca displayLCD para o kit E-P18Mini, 
				// com a declaração dos registradores referentes as portas
				// ligadas no kit	
					 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
//atribuição:	0 = LED desligado
//		1 = LED ligado

#define LED_AMARELO		LATCbits.LATC1
#define LED_VERMELHO            LATCbits.LATC2
#define BOOT			PORTAbits.RA3

/** V A R I A V E I S   G L O B A I S ****************************************/

// Variável contadora global
int count = 0;

// Variáveis globais do cronômetro
int segundos = 0;
int minutos = 0;

/**  P R O T O T I P O S   P R I V A D O S ***********************************/

// Funções de configuração
void ConfiguraSistema (void);
void ConfiguraInterrupcao(void);
// Funções de Tratamento da Interrupção
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);
// Função que escreve diretamente o tempo no display LCD, no devido formato.
// Utilizada de modo a deixar mais limpo o código
void EscreveTempoLCD (char, char, char);

/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa principal,
 *		pois esta é a primeira a ser chamada após o	reset do 
 *		microcontrolador.
 *		Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/

void main(void)
{
	

	
	// Configura as portas e periféricos usados no projeto
	ConfiguraSistema();		

	// Posiciona o cursro na linha 1 e na primeira coluna do display
	PosicaoCursorLCD (1,1);
	
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD ("Cronom. ");
	
	// Escreve o tempo inicial (0'0"0) na pocição 1x9
	PosicaoCursorLCD (1,9);
	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);
		
	// só inicializa o timer após o boot ser pressionado
	while(BOOT){}
	
	// Habilita interrupção
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	
	// Garante que entra no while(1) com boot solto.
	// Enquanto apertado, trava fora do loop principal e atualiza o valor
	while (BOOT==0)
			{
		   	PosicaoCursorLCD(1,9);
		   	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);
			}
	
	// Laço infinito
	while(1)
   	{ 
	 
	   	// Atualiza o valor da contagem no display LCD
	   	PosicaoCursorLCD(1,9);
	   	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);

		Delay100TCYx(120);
		
		// Caso pressionado, fixa um valor na 2ª linha do display
		if (BOOT==0){
		PosicaoCursorLCD (2,1);
		EscreveFraseRomLCD("Pausa : ");
                // escreve o tempo atual
		EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);
		
		
			// Enquanto pressionado, ainda continua atualizando no display
			while (BOOT==0)
			{
		   	PosicaoCursorLCD(1,9);
		   	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);
			}
					
		}// end boot
		
		
	}//end while
	
}//end main

/******************************************************************************
 * Funcao:     	void EscreveTempoLCD(char, char, char)
 * Entrada:    	minutos(char), segundos (char), centésimos de segundo(char)
 * Saída:      	Nenhuma (void)
 * Descrição:  	EscreveTempoLCD é a rotina que atualiza no display 7 segmentos o 
 *		parametro do horário passado para ela.
 *		Seu objetivo é "imprimir" os valores no display, com os caracteres
 *		que deixam intuitivo que são parâmetros de tempo. 
 *****************************************************************************/
void EscreveTempoLCD (char min, char seg, char dec)
{			
			// Escreve na ordem correta os valores no display
			// Faz uma lógica que permite ser escrito números com 2 casas
			if (min<10){		// Deslocamento, caso o tempo seje 1, mostrará 01, por exemplo
			EscreveInteiroLCD(0);	// garante que o número terá no mínimo duas casas decimais.
			}	
			EscreveInteiroLCD(min);
			EscreveCaractereLCD(39);    // Escreve no display aspas simples
			
			if (seg<10){
			EscreveInteiroLCD(0);       // Deslocamento, caso o tempo seje 1, mostrará 01, por exemplo
			} 	
			EscreveInteiroLCD(seg);
			EscreveCaractereLCD(34);    // Escreve no display aspas duplas
			
			EscreveInteiroLCD(dec);
			EscreveFraseRomLCD(" ");
			
}

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Saída:      	Nenhuma (void)
 * Descrição:  	ConfiguraSistema é a rotina de configuração principal do projeto.
 *		Seu objetivo é configurar as portas de I/O e os demais periféricos
 *		do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	
	// Desabilita todas as 13 portas analógicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Configura LED do Kit PICMINAS: saida digital	
	TRISCbits.TRISC1=0;		// RC1: saida digital - LED_AMARELO
	TRISCbits.TRISC2=0;             // RC2: saida digital - LED_VERDE

	// Configura Botão do Kit PICMINAS: entradas digital
	TRISAbits.TRISA3=1;		// RA3: entrada digital - BOTAO BOOT
	
	ConfiguraInterrupcao();         // Configura os registradores necessários
	
	OpenTimer0 (		//função da timeres.h que configura o timer

	TIMER_INT_ON	&	//habilita interrupções para o timer
	T0_16BIT	&	//configura timer de 16 bits
	T0_SOURCE_INT	&	//seleciona clock interno
	T0_PS_1_32);		//prescale selecionado 1:32

	WriteTimer0(28036) ;	//é o valor inicial do timer tal que conte 100ms exatos

	// Configura e inicializa o display LCD
	ConfiguraLCD();
	LimpaDisplay();
	
	
}//end ConfiguraSistema
/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Saída:          Nenhuma (void)
 * Descrição:      Função que configura as interrupções utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	
	
	RCONbits.IPEN = 0;	//Desativa o uso de prioridade
	INTCONbits.GIE = 0;	//Desativa todos as interrupções
	INTCONbits.PEIE = 1;	//Desabilita interrupções de periféricos (IPEN=0)
	
	//início da configuração do timer0
	INTCONbits.TMR0IE = 1;	//TMR0 interrup Eneable
	INTCONbits.TMR0IF = 0;	// TMRO interrup Flag -> zera o flag
	INTCON2bits.TMR0IP = 1;	// Interrupção de altra prioridade. Se não tem prioridade, nao eh necessario
	//fim da configuração do timer0


	
}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:	void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de ALTA prioridade
 *		Nessa função deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupção, comparando 
 *		os flags de cada tipo de interrupção.
 *			2- tratar a interrupção selecionada.
 *			3- limpar o flag que causou a interrupção!!! Importante 
 *		para garantir que não ocorrerá uma chamada indesejada ao sair 
 *		do tratamento da interrupção.
 *		Ao sair dessa função é usado o retorno do tipo "retfie fast",
 *		pois esta função é declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if (INTCONbits.TMR0IF==1){	// se a interrupção foi do flag do TIMER 0
		
	WriteTimer0(28036);	//	já inicia a contagem a partir do número
	INTCONbits.TMR0IF = 0;	//	zera o flag
	
		
		count ++; 	// incrementa em toda interrupção (a cada 100ms)
		if(count==10){
                    count=0;
                    segundos ++;
                            if (segundos==60){
                            segundos=0;
                            minutos++;
                            }
			
		}	
	
	}// end tratamento TMR0
		
}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:	void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de BAIXA prioridade
*		Nessa função deve-se lembrar de fazer a seguinte lista:
*			1- verificar qual foi a causa da interrupção, comparando 
*		os flags de cada tipo de interrupção.
*			2- tratar a interrupção selecionada.
*			3- limpar o flag que causou a interrupção!!! Importante 
*		para garantir que não ocorrerá uma chamada indesejada ao sair 
*		do tratamento da interrupção.
*       	Ao sair dessa função é usado o retorno do tipo "retfie",
*		pois esta função é declarada como BAIXA prioridade com a diretiva
*		#pragma interruptlow
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