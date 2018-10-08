/******************************************************************************
 *
 *            		SEMPRA PROJETOS
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
 * Prática:	 	SEMAFORO PARA PEDESTRES COM ANIMAÇÃO
 *
 * Autor:               Bruno A. Dayrell
 * Versão:		v1.0
 *						
 * Descrição:       	Simulação de um semáforo para pedestres, com apenas 2 leds
 *			cujo sinal amarelo foi substituído pelo vermelho piscante.
 *			também foi implementado no display LCD desenhos que simulam
 *			o pedestre parado ou atravessando a rua.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
                        // com as definições do PIC selecionado no projeto, neste
			// caso, o modelo 18F4550.

#include <delays.h>	// Biblioteca padrão de rotinas de atraso do C18 Microchip
			// mais informações nos arquivos de ajuda da biblioteca C18
			// presentes na propria pasta de instalação, por exemplo,
			// C:\MCC18\doc\hlpC18Lib.chm
			// Procure pelo item: "Delay Functions"	

#include <timers.h>	// Biblioteca do comipilador que possui as funções básicas
			// de registros e configurações dos periféricos timers
                        // mais informações nos arquivos de ajuda da biblioteca C18
                        // presentes na propria pasta de instalação, por exemplo,
                        // C:\MCC18\doc\PIC18F Peripheral Library Help Document


#include "displayLCD_mini.h"    // Versão da biblioteca displayLCD para o kit E-P18Mini,
				// com a declaração dos registradores referentes as portas
				// ligadas no kit
					 			

/** D E F I N E S ************************************************************/
// LED's do Kit PICMINAS:	saida digital
// Atribuição:	0 = LED desligado
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

// defines para as posições dos caracteres criados.
#define PARADO			0x00
#define ANDANDO			0x01
#define	ANDANDO1		0x01
#define ANDANDO2		0x02
#define ANDANDO3		0x03
#define ANDANDO4		0x04


/** V A R I A V E I S   G L O B A I S ****************************************/

// Variável contadora global
int count = 0;

// Variável que armazena o estado do sinal
char status = SINAL_ABERTO;

// Variáveis globais do cronômetro
int segundos = 0;

// armazena variavel na memória de dados (SDRAM)
// outro tipo sintaxe C para inicializar a variável na DECLARAÇÃO
rom unsigned char linha2[20]="Curso SEMPRA";


/**  P R O T O T I P O S   P R I V A D O S ***********************************/
// Função que cria um caractere na CGRam do display LCD
void CriaCaracteresLCD (char,char *caractere);
// funções de configuração
void ConfiguraSistema (void);
void ConfiguraInterrupcao(void);
// funções de tratamendo de interrupção
void Tratamento_High_Interrupt(void);
void Tratamento_Low_Interrupt(void);

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
	
	// a variável é um vetor de char que guarda cada linha de cada novo caractere criado.
	// cada oito linhas (ou oito números de 0x00 a 0x1F) corresponde a um caractere no display
	// a controladora do LCD já entende que após oito números enviado ela deve gravar o próximo
	char robo[] = { 
	
	// Caractere 1, posição da memória CGRAM 0x00
	0b00001110,	// -###-			****	Estático	
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00011111,	// #####
	0b00000100,	// --#--
	0b00001010,	// -#-#-
	0b00001010,	// -#-#-
	
	// Caractere 2, posição da memória CGRAM 0x01
	0b00001110,	// -###-			****	os quatro que dão a impressão de movimento		
	0b00010001,	// #---#	
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00000100,	// --#--
	0b00000100,	// --#--
	0b00001010,	// -#-#-
	0b00010001,	// #---#
	
	// Caractere 3, posição da memória CGRAM 0x02
	0b00001110,	// -###-		
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00001110,	// -###-
	0b00010101,	// #-#-#
	0b00001010,	// -#-#-
	0b00010001,	// #---#
		
	// Caractere 4, posição da memória CGRAM 0x03	
	0b00001110,	// -###-		
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00001110,	// -###-
	0b00010101,	// #-#-#
	0b00000100,	// --#--
	0b00000100,	// --#--
	
	// Caractere 5, posição da memória CGRAM 0x04
	0b00001110,	// -###-		
	0b00010001,	// #---#
	0b00001110,	// -###-
	0b00000100,	// --#--
	0b00000100,	// --#-
	0b00000100,	// --#--
	0b00000100,	// --#--
	0b00000100	// --#--
	
	
	};
	
	// variável que ajuda na animaçao do bonequinho
	unsigned char 	andando = 0;

	
	// Configura as portas e periféricos usados no projeto
	ConfiguraSistema();
			
	
	// Configura e inicializa o display LCD
	ConfiguraLCD();
	LimpaDisplay();
	DesligaCursor();
        // Função que cria os caracteres da variavel robo
	CriaCaracteresLCD (5,&robo);
		
	
	// Habilita interrupção
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	LATDbits.LATD1 = 1;
	
	PosicaoCursorLCD (2,3);
	EscreveFraseRomLCD(linha2);
			
			
			
	// Laço infinito		
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
			
			// Enquanto o contador não zerar (incrementação de segundo)
			while (count){
				
				PosicaoCursorLCD(1,9);	
				
				// Alternar o caractere a ser exibido na tela
				// dando a impressão de movimento
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
			
			// variável contadora que auxilia na exibição dos caracteres
			// a cada segundo, é incrementada a variável
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
				// dando a impressão de piscando
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
 * Saída:      	Nenhuma (void)
 * Descrição:  	CriaCaractereLCD é a rotina que grava na memórica CGRAM do LCD
 *		o conjunto de bytes correspondentes à formação dos caracteres.
 *		deve ser informado o número de caracteres a ser criados,
 *		para então criar, a partir da posição 0x00;
 *****************************************************************************/
 
void CriaCaracteresLCD (char num, char *caractere)
{
	
	// variáveis contadoras
	char i=0;
	char j =0;
	
	/**********************************************************************************************
	*	Processo: O LCD é 5x8, onde GERALMENTE a linha inferior é para o cursor. 
	*	Podemos escrever na linha inferior
	*	o processo consta em acessar a primeira posição de memória
	*	e então enviar as 8 colunas, onde 1 é aceso, formando a imagem desejada.
	**********************************************************************************************/
	
	// Posição 0x00 da CGRAM
	EscreveComandoLCD (0b01000000);
	
	// cada dígido
	for (j=0;j<num;j++){
		
		// cada linha do dígito (1 caractere)
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
	TRISCbits.TRISC2=0; 	// RC2: saida digital - LED_VERDE

	// Configura Botão do Kit PICMINAS: entradas digital
	TRISBbits.TRISB4=1;		// RB4: entrada digital - BOTAO BOOT
	TRISAbits.TRISA3=1;		// RA3: entrada digital

	/*************************************************************/
	/*************************************************************/
	TRISDbits.TRISD1 = 0;	
	
	ConfiguraInterrupcao();
	
	OpenTimer0 (		//função da timeres.h que configura o timer

	TIMER_INT_ON	&	//habilita interrupções para o timer
	T0_16BIT		&	//configura timer de 16 bits
	T0_SOURCE_INT	&	//seleciona clock interno
	T0_PS_1_32);		//prescale selecionado 1:32

	WriteTimer0(28036) ;	//é o número que vai começar para que conte 100ms exatos


	
	
}//end ConfiguraSistema
/******************************************************************************
 * Funcao:         void ConfiguraInterrupcao(void)
 * Entrada:        Nenhuma (void)
 * Saída:          Nenhuma (void)
 * Descrição:      Função que configura as interrupções utilizadas no projeto
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	
	
	RCONbits.IPEN = 0;			//Desativa o uso de prioridade
	INTCONbits.GIE = 0;			//Desativa todos as interrupções
	INTCONbits.PEIE = 1;		//Desabilita interrupções de periféricos (IPEN=0)
	
	//início da configuração do timer0
	INTCONbits.TMR0IE = 1;					//TMR0 interrup Eneable
	INTCONbits.TMR0IF = 0;					// TMRO interrup Flag -> zera o flag
	INTCON2bits.TMR0IP = 1;					// Interrupção de altra prioridade. Se não tem prioridade, nao eh necessario
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
 *
 *		Ao sair dessa função é usado o retorno do tipo "retfie fast",
 *		pois esta função é declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATENÇÃO NA SINTAXE de declaração com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if (INTCONbits.TMR0IF==1){  // se a interrupção foi do flag do TIMER 0
		
	WriteTimer0(28036);     //	já começa a contar a partir desse número.
	INTCONbits.TMR0IF = 0;  //	zera o flag
	
	
		count ++;       //se foi interrompido, incrementa (a cada 100ms)
		if(count==10){
		count=0;
		segundos ++;
		}
		
		
			/**********************************************
			Verificação do tempo e do estado do sinal atual
			**********************************************/
		
		// a mudança de estado do sinal é interpretada e executada na própria interrupção
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
 * Saída:       Nenhuma (void)
 * Descrição:   Função de tratamento das interrupções de BAIXA prioridade
 *		Nessa função deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupção, comparando 
 *		os flags de cada tipo de interrupção.
 *			2- tratar a interrupção selecionada.
 *			3- limpar o flag que causou a interrupção!!! Importante 
 *		para garantir que não ocorrerá uma chamada indesejada ao sair 
 *		do tratamento da interrupção.
 *
 *		Ao sair dessa função é usado o retorno do tipo "retfie",
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