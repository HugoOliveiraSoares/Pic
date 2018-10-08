/******************************************************************************
 *
 *            		SEMPRA PROJETOS
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
 * Pr�tica:	 	SEMAFORO PARA PEDESTRES COM ANIMA��O
 *
 * Autor:               Bruno A. Dayrell
 * Vers�o:		v1.0
 *						
 * Descri��o:       	Simula��o de um sem�foro para pedestres, com apenas 2 leds
 *			cujo sinal amarelo foi substitu�do pelo vermelho piscante.
 *			tamb�m foi implementado no display LCD desenhos que simulam
 *			o pedestre parado ou atravessando a rua.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
                        // com as defini��es do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include <delays.h>	// Biblioteca padr�o de rotinas de atraso do C18 Microchip
			// mais informa��es nos arquivos de ajuda da biblioteca C18
			// presentes na propria pasta de instala��o, por exemplo,
			// C:\MCC18\doc\hlpC18Lib.chm
			// Procure pelo item: "Delay Functions"	

#include <timers.h>	// Biblioteca do comipilador que possui as fun��es b�sicas
			// de registros e configura��es dos perif�ricos timers
                        // mais informa��es nos arquivos de ajuda da biblioteca C18
                        // presentes na propria pasta de instala��o, por exemplo,
                        // C:\MCC18\doc\PIC18F Peripheral Library Help Document


#include "displayLCD_mini.h"    // Vers�o da biblioteca displayLCD para o kit E-P18Mini,
				// com a declara��o dos registradores referentes as portas
				// ligadas no kit
					 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
// Atribui��o:	0 = LED desligado
//				1 = LED ligado
#define LED_AMARELO	LATCbits.LATC2
#define LED_VERMELHO 	LATCbits.LATC1
#define BOOT		PORTAbits.RA3

#define SINAL_ABERTO	0x00
#define SINAL_PISCANDO	0x01
#define SINAL_FECHADO	0x02

#define TEMPO_ABERTO	10
#define TEMPO_PISCANDO	3
#define TEMPO_FECHADO	10

// defines para as posi��es dos caracteres criados.
#define PARADO			0x00
#define ANDANDO			0x01
#define	ANDANDO1		0x01
#define ANDANDO2		0x02
#define ANDANDO3		0x03
#define ANDANDO4		0x04


/** V A R I A V E I S   G L O B A I S ****************************************/

// Vari�vel contadora global
int count = 0;

// Vari�vel que armazena o estado do sinal
char status = SINAL_ABERTO;

// Vari�veis globais do cron�metro
int segundos = 0;

// armazena variavel na mem�ria de dados (SDRAM)
// outro tipo sintaxe C para inicializar a vari�vel na DECLARA��O
rom unsigned char linha2[20]="Curso SEMPRA";


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
// Fun��o que cria um caractere na CGRam do display LCD
void CriaCaracteresLCD (char,char *caractere);
// fun��es de configura��o
void ConfiguraSistema (void);
void ConfiguraInterrupcao(void);
// fun��es de tratamendo de interrup��o
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

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
	
	// a vari�vel � um vetor de char que guarda cada linha de cada novo caractere criado.
	// cada oito linhas (ou oito n�meros de 0x00 a 0x1F) corresponde a um caractere no display
	// a controladora do LCD j� entende que ap�s oito n�meros enviado ela deve gravar o pr�ximo
	char robo[] = { 
	
	// Caractere 1, posi��o da mem�ria CGRAM 0x00
	0b00001110,	// -###-			****	Est�tico	
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00011111,	// #####
	0b00000100,	// --#--
	0b00001010,	// -#-#-
	0b00001010,	// -#-#-
	
	// Caractere 2, posi��o da mem�ria CGRAM 0x01
	0b00001110,	// -###-			****	os quatro que d�o a impress�o de movimento		
	0b00010001,	// #---#	
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00000100,	// --#--
	0b00000100,	// --#--
	0b00001010,	// -#-#-
	0b00010001,	// #---#
	
	// Caractere 3, posi��o da mem�ria CGRAM 0x02
	0b00001110,	// -###-		
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00001110,	// -###-
	0b00010101,	// #-#-#
	0b00001010,	// -#-#-
	0b00010001,	// #---#
		
	// Caractere 4, posi��o da mem�ria CGRAM 0x03	
	0b00001110,	// -###-		
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00001110,	// -###-
	0b00010101,	// #-#-#
	0b00000100,	// --#--
	0b00000100,	// --#--
	
	// Caractere 5, posi��o da mem�ria CGRAM 0x04
	0b00001110,	// -###-		
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00000100,	// --#-
	0b00000100,	// --#--
	0b00000100,	// --#--
	0b00000100	// --#--
	
	
	};
	
	// vari�vel que ajuda na anima�ao do bonequinho
	unsigned char 	andando = 0;

	
	// Configura as portas e perif�ricos usados no projeto
	ConfiguraSistema();
			
	
	// Configura e inicializa o display LCD
	ConfiguraLCD();
	LimpaDisplay();
	DesligaCursor();
        // Fun��o que cria os caracteres da variavel robo
	CriaCaracteresLCD (5,&robo);
		
	
	// Habilita interrup��o
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	LATDbits.LATD1 = 1;
	
	PosicaoCursorLCD (2,3);
	EscreveFraseRomLCD(linha2);
			
			
			
	// La�o infinito		
	while(1)
   	{ 
	   
	   	// Rotina que atualiza o valor da contagem no display LCD
	   	PosicaoCursorLCD(1,9);
		Delay100TCYx(120);
		
                // --------------------------------------------------------------------------------
                // Sinal aberto
		
		if (status == SINAL_ABERTO){
			
			
			LED_AMARELO = 1;
			LED_VERMELHO = 0;
			
			// espera um pouco a mais que 100ms
			Delay10KTCYx(121);
			PosicaoCursorLCD(2,1);
			
			// Enquanto o contador n�o zerar (incrementa��o de segundo)
			while (count){
				
				PosicaoCursorLCD(1,9);	
				
				// Alternar o caractere a ser exibido na tela
				// dando a impress�o de movimento
				if (count<5){
					
					// Desenha um dos caracteres criados no display LCD			
					EscreveCaractereLCD(ANDANDO1+andando);
					while(count<5){}
			
				}
				
				else{
						
					// Desenha um dos caracteres criados no display LCD	
					EscreveCaractereLCD(ANDANDO2+andando);									
					while(count>=5){}
				}	
				
			}
			
			// vari�vel contadora que auxilia na exibi��o dos caracteres
			// a cada segundo, � incrementada a vari�vel
			if(andando==2)andando=0;
			else andando = 2;
			
							
		}
		
		// --------------------------------------------------------------------------------
		// Sinal fechado
		if(status == SINAL_FECHADO){
			
			// Desenha um dos caracteres criados no display LCD	
			EscreveCaractereLCD(PARADO);
			LED_VERMELHO = 1;
			LED_AMARELO = 0;
			
		}
		
		// --------------------------------------------------------------------------------
		// Sinal piscando, equivalente ao sinal amarelo
		
		if (status == SINAL_PISCANDO){
			PosicaoCursorLCD(1,9);
			LED_AMARELO = 0;
			
				// Altera o caractere a ser exibido na tela,
				// dando a impress�o de piscando
				if (count<5){			
					EscreveCaractereLCD(' ');					
					LED_VERMELHO = 0;	
				}
				else{
					
					// Desenha um dos caracteres criados no display LCD	
					EscreveCaractereLCD(PARADO);
					LED_VERMELHO = 1;
				}
		}		
		
		
	}//end while
	
}//end main



/******************************************************************************
 * Funcao:     	void CriaCaractereLCD (char,char)
 * Entrada:    	num(char), caracteres(char)
 * Sa�da:      	Nenhuma (void)
 * Descri��o:  	CriaCaractereLCD � a rotina que grava na mem�rica CGRAM do LCD
 *		o conjunto de bytes correspondentes � forma��o dos caracteres.
 *		deve ser informado o n�mero de caracteres a ser criados,
 *		para ent�o criar, a partir da posi��o 0x00;
 *****************************************************************************/
 
void CriaCaracteresLCD (char num, char *caractere)
{
	
	// vari�veis contadoras
	char i=0;
	char j =0;
	
	/**********************************************************************************************
	*	Processo: O LCD � 5x8, onde GERALMENTE a linha inferior � para o cursor. 
	*	Podemos escrever na linha inferior
	*	o processo consta em acessar a primeira posi��o de mem�ria
	*	e ent�o enviar as 8 colunas, onde 1 � aceso, formando a imagem desejada.
	**********************************************************************************************/
	
	// Posi��o 0x00 da CGRAM
	EscreveComandoLCD (0b01000000);
	
	// cada d�gido
	for (j=0;j<num;j++){
		
		// cada linha do d�gito (1 caractere)
		for (i=0;i<(8);i++){
		EscreveCaractereLCD (*caractere);
		caractere++;	
		}	
	}
	// Comando que diz o fim da escrita
	EscreveComandoLCD(0b0000000001);

	
	

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
	TRISCbits.TRISC2=0; 	// RC2: saida digital - LED_VERDE

	// Configura Bot�o do Kit PICMINAS: entradas digital
	TRISBbits.TRISB4=1;		// RB4: entrada digital - BOTAO BOOT
	TRISAbits.TRISA3=1;		// RA3: entrada digital

	/*************************************************************/
	/*************************************************************/
	TRISDbits.TRISD1 = 0;	
	
	ConfiguraInterrupcao();
	
	OpenTimer0 (		//fun��o da timeres.h que configura o timer

	TIMER_INT_ON	&	//habilita interrup��es para o timer
	T0_16BIT		&	//configura timer de 16 bits
	T0_SOURCE_INT	&	//seleciona clock interno
	T0_PS_1_32);		//prescale selecionado 1:32

	WriteTimer0(28036) ;	//� o n�mero que vai come�ar para que conte 100ms exatos


	
	
}//end ConfiguraSistema
/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Fun��o que configura as interrup��es utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	
	
	RCONbits.IPEN = 0;			//Desativa o uso de prioridade
	INTCONbits.GIE = 0;			//Desativa todos as interrup��es
	INTCONbits.PEIE = 1;		//Desabilita interrup��es de perif�ricos (IPEN=0)
	
	//in�cio da configura��o do timer0
	INTCONbits.TMR0IE = 1;					//TMR0 interrup Eneable
	INTCONbits.TMR0IF = 0;					// TMRO interrup Flag -> zera o flag
	INTCON2bits.TMR0IP = 1;					// Interrup��o de altra prioridade. Se n�o tem prioridade, nao eh necessario
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
 *
 *		Ao sair dessa fun��o � usado o retorno do tipo "retfie fast",
 *		pois esta fun��o � declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if (INTCONbits.TMR0IF==1){  // se a interrup��o foi do flag do TIMER 0
		
	WriteTimer0(28036);     //	j� come�a a contar a partir desse n�mero.
	INTCONbits.TMR0IF = 0;  //	zera o flag
	
	
		count ++;       //se foi interrompido, incrementa (a cada 100ms)
		if(count==10){
		count=0;
		segundos ++;
		}
		
		
			/**********************************************
			Verifica��o do tempo e do estado do sinal atual
			**********************************************/
		
		// a mudan�a de estado do sinal � interpretada e executada na pr�pria interrup��o
		if(status == SINAL_ABERTO && segundos >= TEMPO_ABERTO){
			status = SINAL_PISCANDO;
			segundos = 0;
		}		
		else if (status == SINAL_PISCANDO && segundos >= TEMPO_PISCANDO){
			status = SINAL_FECHADO;
			segundos = 0;
		}	
		else if (status == SINAL_FECHADO && segundos >= TEMPO_FECHADO)
		{
			status = SINAL_ABERTO;
			segundos = 0;
		}	
	
	}
}// end Tratamento_High_Interrupt



/******************************************************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
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
 *
 *		Ao sair dessa fun��o � usado o retorno do tipo "retfie",
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