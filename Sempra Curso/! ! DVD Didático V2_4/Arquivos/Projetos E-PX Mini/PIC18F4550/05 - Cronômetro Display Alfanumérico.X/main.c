/******************************************************************************
 *
 *                          SEMPRA PROJETOS
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		Kit SEMPRA E-P18mini V 1.0
 * Pr�tica:	 	CRONOMETRO
 *
 * Autor:               Bruno A. Dayrell
 * Vers�o:		v1.0	
 *						
 * Descri��o:       	Cronometro progressivo cont�nuo, que a cada vez em que 
 *			o bot�o RA3 � apertado, ele atualiza na tela o valor
 *			atual do contador. Utiliza��o do perif�rico timer para 
 *                      a contagem.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
			// com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include <timers.h>	// Biblioteca do comipilador que possui as fun��es b�sicas
			// de registros e configura��es dos perif�ricos timers


#include "displayLCD_mini.h"	// Vers�o da biblioteca displayLCD para o kit E-P18Mini, 
				// com a declara��o dos registradores referentes as portas
				// ligadas no kit	
					 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
//atribui��o:	0 = LED desligado
//		1 = LED ligado

#define LED_AMARELO		LATCbits.LATC1
#define LED_VERMELHO            LATCbits.LATC2
#define BOOT			PORTAbits.RA3

/** V A R I A V E I S   G L O B A I S ****************************************/

// Vari�vel contadora global
int count = 0;

// Vari�veis globais do cron�metro
int segundos = 0;
int minutos = 0;

/**  P R O T O T I P O S   P R I V A D O S ***********************************/

// Fun��es de configura��o
void ConfiguraSistema (void);
void ConfiguraInterrupcao(void);
// Fun��es de Tratamento da Interrup��o
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);
// Fun��o que escreve diretamente o tempo no display LCD, no devido formato.
// Utilizada de modo a deixar mais limpo o c�digo
void EscreveTempoLCD (char, char, char);

/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:    	void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa principal,
 *		pois esta � a primeira a ser chamada ap�s o	reset do 
 *		microcontrolador.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/

void main(void)
{
	

	
	// Configura as portas e perif�ricos usados no projeto
	ConfiguraSistema();		

	// Posiciona o cursro na linha 1 e na primeira coluna do display
	PosicaoCursorLCD (1,1);
	
	// Escreve a string da "ROM" no display LCD	
	EscreveFraseRomLCD ("Cronom. ");
	
	// Escreve o tempo inicial (0'0"0) na poci��o 1x9
	PosicaoCursorLCD (1,9);
	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);
		
	// s� inicializa o timer ap�s o boot ser pressionado
	while(BOOT){}
	
	// Habilita interrup��o
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	
	// Garante que entra no while(1) com boot solto.
	// Enquanto apertado, trava fora do loop principal e atualiza o valor
	while (BOOT==0)
			{
		   	PosicaoCursorLCD(1,9);
		   	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);
			}
	
	// La�o infinito
	while(1)
   	{ 
	 
	   	// Atualiza o valor da contagem no display LCD
	   	PosicaoCursorLCD(1,9);
	   	EscreveTempoLCD ( (char)minutos, (char)segundos, (char)count);

		Delay100TCYx(120);
		
		// Caso pressionado, fixa um valor na 2� linha do display
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
 * Entrada:    	minutos(char), segundos (char), cent�simos de segundo(char)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	EscreveTempoLCD � a rotina que atualiza no display 7 segmentos o 
 *		parametro do hor�rio passado para ela.
 *		Seu objetivo � "imprimir" os valores no display, com os caracteres
 *		que deixam intuitivo que s�o par�metros de tempo. 
 *****************************************************************************/
void EscreveTempoLCD (char min, char seg, char dec)
{			
			// Escreve na ordem correta os valores no display
			// Faz uma l�gica que permite ser escrito n�meros com 2 casas
			if (min<10){		// Deslocamento, caso o tempo seje 1, mostrar� 01, por exemplo
			EscreveInteiroLCD(0);	// garante que o n�mero ter� no m�nimo duas casas decimais.
			}	
			EscreveInteiroLCD(min);
			EscreveCaractereLCD(39);    // Escreve no display aspas simples
			
			if (seg<10){
			EscreveInteiroLCD(0);       // Deslocamento, caso o tempo seje 1, mostrar� 01, por exemplo
			} 	
			EscreveInteiroLCD(seg);
			EscreveCaractereLCD(34);    // Escreve no display aspas duplas
			
			EscreveInteiroLCD(dec);
			EscreveFraseRomLCD(" ");
			
}

/******************************************************************************
 * Funcao:     	void ConfiguraSistema(void)
 * Entrada:    	Nenhuma (void)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	ConfiguraSistema � a rotina de configura��o principal do projeto.
 *		Seu objetivo � configurar as portas de I/O e os demais perif�ricos
 *		do microcontrolador para que operem da maneira desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema (void)
{
	
	// Desabilita todas as 13 portas anal�gicas ANx (portas do conversor A/D) assim
	//as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;
	
	// Configura LED do Kit PICMINAS: saida digital	
	TRISCbits.TRISC1=0;		// RC1: saida digital - LED_AMARELO
	TRISCbits.TRISC2=0;             // RC2: saida digital - LED_VERDE

	// Configura Bot�o do Kit PICMINAS: entradas digital
	TRISAbits.TRISA3=1;		// RA3: entrada digital - BOTAO BOOT
	
	ConfiguraInterrupcao();         // Configura os registradores necess�rios
	
	OpenTimer0 (		//fun��o da timeres.h que configura o timer

	TIMER_INT_ON	&	//habilita interrup��es para o timer
	T0_16BIT	&	//configura timer de 16 bits
	T0_SOURCE_INT	&	//seleciona clock interno
	T0_PS_1_32);		//prescale selecionado 1:32

	WriteTimer0(28036) ;	//� o valor inicial do timer tal que conte 100ms exatos

	// Configura e inicializa o display LCD
	ConfiguraLCD();
	LimpaDisplay();
	
	
}//end ConfiguraSistema
/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Fun��o que configura as interrup��es utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	
	
	RCONbits.IPEN = 0;	//Desativa o uso de prioridade
	INTCONbits.GIE = 0;	//Desativa todos as interrup��es
	INTCONbits.PEIE = 1;	//Desabilita interrup��es de perif�ricos (IPEN=0)
	
	//in�cio da configura��o do timer0
	INTCONbits.TMR0IE = 1;	//TMR0 interrup Eneable
	INTCONbits.TMR0IF = 0;	// TMRO interrup Flag -> zera o flag
	INTCON2bits.TMR0IP = 1;	// Interrup��o de altra prioridade. Se n�o tem prioridade, nao eh necessario
	//fim da configura��o do timer0


	
}// end ConfiguraInterrupcao

/******************************************************************************
 * Funcao:	void Tratamento_High_Interrupt(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de ALTA prioridade
 *		Nessa fun��o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup��o, comparando 
 *		os flags de cada tipo de interrup��o.
 *			2- tratar a interrup��o selecionada.
 *			3- limpar o flag que causou a interrup��o!!! Importante 
 *		para garantir que n�o ocorrer� uma chamada indesejada ao sair 
 *		do tratamento da interrup��o.
 *		Ao sair dessa fun��o � usado o retorno do tipo "retfie fast",
 *		pois esta fun��o � declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if (INTCONbits.TMR0IF==1){	// se a interrup��o foi do flag do TIMER 0
		
	WriteTimer0(28036);	//	j� inicia a contagem a partir do n�mero
	INTCONbits.TMR0IF = 0;	//	zera o flag
	
		
		count ++; 	// incrementa em toda interrup��o (a cada 100ms)
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
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o de tratamento das interrup��es de BAIXA prioridade
*		Nessa fun��o deve-se lembrar de fazer a seguinte lista:
*			1- verificar qual foi a causa da interrup��o, comparando 
*		os flags de cada tipo de interrup��o.
*			2- tratar a interrup��o selecionada.
*			3- limpar o flag que causou a interrup��o!!! Importante 
*		para garantir que n�o ocorrer� uma chamada indesejada ao sair 
*		do tratamento da interrup��o.
*       	Ao sair dessa fun��o � usado o retorno do tipo "retfie",
*		pois esta fun��o � declarada como BAIXA prioridade com a diretiva
*		#pragma interruptlow
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