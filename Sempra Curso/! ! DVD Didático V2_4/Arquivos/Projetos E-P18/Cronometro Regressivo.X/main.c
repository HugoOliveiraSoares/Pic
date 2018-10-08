/******************************************************************************
 *
 *                 SEMPRA PROJETOS (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo)	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	PICMINAS
 * Pr�tica: 			Cronometro regressivo
 * Descri��o:        	Este projeto implementa um alarme configur�vel com contador regressivo 
 *			utilizando o KIT PICMinas. Ao inicializar, o programa deve pedir ao usu�rio
 *			(atrav�s do display de LCD alfanum�rico) para entrar com um hor�rio composto
 *			de minutos e segundos. A entrada de dados deve ser feita da seguinte forma: 
 *                          B1 - Incrementa o digito subindo de 0 a 9 e voltando a 0 caso ultrapasse 9.
 *                          B2- Decrementa o digito descendo  de 9 a 0 e voltando em 9 caso ultrapasse 0.
 *                          Boot - Confirma e passa para o pr�ximo digito ou termina a fase de configura��o
 *                                 caso esteja no ultimo  d�gito.
 *			Ap�s finalizar a configura��o o programa deve usar o perif�rico TIMER1 
 *			para implementar um contador decrescente no display de LCD. 
 *			Ao terminar a contagem o rel� e o buzzer devem ser ligados e permanecerem assim
 *			at� que o usu�rio pressione o bot�o BOOT.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>            // Necess�rio para que o compilador adicione a biblioteca
				// com as defini��es do PIC selecionado no projeto, neste
				// caso, o modelo 18F4550.

#include <timers.h>		// Biblioteca do compilador para uso dos m�dulos TIMERs

#include <delays.h>		// Biblioteca do compilador para gerar atrasos com o uso
				// da CPU.

#include "displayLCD.h"         // Biblioteca desenvolvida pelo PICMinas para escrever
				// no display de LCD.

/** D E F I N E S ************************************************************/

#define BOOT        PORTBbits.RB4
#define B1          PORTEbits.RE1
#define B2          PORTEbits.RE2

#define LEDVERDE    PORTCbits.RC2
#define LEDAMARELO  PORTDbits.RD0
#define LEDVERMELHO PORTDbits.RD1

#define BUZZER 	    PORTCbits.RC1
#define RELE        PORTCbits.RC0

#define INICIO_TMR1 28036   
						 			
/** V A R I A V E I S   G L O B A I S ****************************************/

char segundos = 0;
char minutos  = 0;
char overflow = 0;

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);
void ConfiguraInterrupcao();
void ConfiguraTempo(void);
void HighPriorityISRCode();
void LowPriorityISRCode();
/** F U N C O E S ************************************************************/
/******************************************************************************
 * Funcao:        	void main(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Fun��o principal do programa. Responsavel apenas por atualizar
 *					o LCD com os valores das variaveis minutos e segundos.
 *****************************************************************************/
void main(void)
{
	char bala = 30;

	BUZZER = bala;
	ConfiguraSistema();		// Configura as portas e perif�ricos do PIC.


	//Garante que os dispositivos estar�o inativos
	BUZZER      = 0;
        RELE        = 0;
	LEDVERDE    = 0;
	LEDAMARELO  = 0;
	LEDVERMELHO = 0;
	ConfiguraTempo(); 	    // Menu de sele��o (configura��o) do tempo do alarme pelo usu�rio

	INTCONbits.GIE  = 1; 		// Desabilita TODAS as interrup��es	
	
	PosicaoCursorLCD(0,0);
	EscreveFraseRomLCD("  CONTAGEM REG. "); //Informa atrav�s do LCD o novo estado do programa

    while(1)				// La�o infinito que executa o funcionamento principal do projeto.
   { 
		EnderecoCursor(0x46);
		if(minutos < 10)
		{
		   EscreveInteiroLCD(0);
		}
		EscreveInteiroLCD(minutos);
		
		EnderecoCursor(0x49);
		if(segundos < 10)
		{
                    EscreveInteiroLCD(0);
		}
		EscreveInteiroLCD(segundos);
	
	}//end while(1)
}//end main

/******************************************************************************
 * Funcao:        	void ConfiguraSistema(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       InicializaSistema � a rotina de configura��o principal do PIC.
 *					Seu objetivo � configurar as portas de I/O e os perif�ricos
 *					do microcontrolador para que os mesmos trabalhem da maneira
 *					desejada no projeto.  
 *****************************************************************************/
void ConfiguraSistema(void)
{

	ADCON1 |= 0x0F; 		// configura todas as portas como digitais

	TRISBbits.TRISB4 = 1; // BOOT
	TRISEbits.TRISE1 = 1; // B1
	TRISEbits.TRISE2 = 1; // B2
	
	TRISCbits.TRISC2 = 0; // LED verde
	TRISDbits.TRISD0 = 0; // LED amarelo
	TRISDbits.TRISD1 = 0; // LED vermelho

	TRISCbits.TRISC0 = 0; //RELE
	TRISCbits.TRISC1 = 0; //Buzzer

	ConfiguraLCD();
	ConfiguraInterrupcao();

}//end ConfiguraSistema
/******************************************************************************
 * Funcao:        	void ConfiguraInterrupcao(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:          	Nenhuma (void)
 * Descri��o:       Configura o m�dulo TIMER1
 *****************************************************************************/
void ConfiguraInterrupcao(void)
{
	RCONbits.IPEN   = 0;	// Desabilita prioridade de interrup��o	
	INTCONbits.GIE  = 0;	// Desabilita TODAS as interrup��es
	INTCONbits.PEIE = 1;	// Habilita interrup��o de perif�ricos	

	OpenTimer1(TIMER_INT_ON    &
			   T1_16BIT_RW     &
			   T1_SOURCE_INT   &
			   T1_PS_1_8       &
			   T1_OSC1EN_OFF   &
 			   T1_SYNC_EXT_OFF);
 
	WriteTimer1(INICIO_TMR1); // Escreve o valor correspondente ao atraso de um segundo
                         	  // nos registradores do Timer0: TMR0L e TMR0H
	
	PIE1bits.TMR1IE  = 1;	// TImer1 enable
	IPR1bits.TMR1IP  = 1; 	// Alta prioridade
	PIR1bits.TMR1IF  = 0;	// Zera o flag do timer1

}// end ConfiguraInterrupcao
/******************************************************************************
 * Funcao:          void ConfiguraTempo(void)
 * Entrada:         Nenhuma (void)
 * Sa�da:           Nenhuma (void)
 * Descri��o:       Cria o menu inicial do programa onde o usu�rio escolhe o
 * 		    valor inicial do cronometro.
 *****************************************************************************/
void ConfiguraTempo(void)
{
	char cont = 0;
	// CONFIGURACAO DO TEMPO DEFINIDO PELO USUARIO
	EnderecoCursor(0x00);
	EscreveFraseRomLCD(" PROGRAMA TIMER ");

	Delay10KTCYx(0);
	Delay10KTCYx(0);	
	Delay10KTCYx(0);
	Delay10KTCYx(0);

	EnderecoCursor(0x00);
	EscreveFraseRomLCD("  CONFIGURACAO  ");
	EnderecoCursor(0x40);
	EscreveFraseRomLCD("TIME: 00:00     ");
	

    while(BOOT) // DEZEMA DOS MINUTOS
	{
		Delay10KTCYx(100);
		
		EnderecoCursor(0x46);
		EscreveFraseRomLCD(cont);
		EnderecoCursor(0x46);
		if(B1)
		{
			Delay10KTCYx(100);
			if(cont >= 9)
			{
				cont = 0;
			}
			else
			{
				cont++;
			}
		}
		if(B2)
 		{
			Delay10KTCYx(100);
			if(cont <= 0 )
			{
				cont = 9;
			}
			else
			{
				cont--;
			}
		}
	}
	Delay10KTCYx(100);
	while(!BOOT){}
	minutos += cont *10;
	cont = 0;

	while(BOOT) // UNIDADE DOS MINUTOS
	{
		Delay10KTCYx(100);
		
		EnderecoCursor(0x47);
		EscreveInteiroLCD(cont);
		EnderecoCursor(0x47);
		if(B1)
		{
			Delay10KTCYx(100);
			if(cont >= 9)
			{
				cont = 0;
			}
			else
			{
				cont++;
			}
		}
		if(B2)
 		{
			Delay10KTCYx(100);
			if(cont <= 0 )
			{
				cont = 9;
			}
			else
			{
				cont--;
			}
		}
	}
	Delay10KTCYx(100);
	while(!BOOT){}
	minutos += cont;
	cont = 0;
	while(BOOT) // DEZENA DOS SEGUNDOS
	{
		Delay10KTCYx(100);
		
		EnderecoCursor(0x49);
		EscreveInteiroLCD(cont);
		EnderecoCursor(0x49);
		if(B1)
		{
			Delay10KTCYx(100);
			if(cont >= 6)
			{
				cont = 0;
			}
			else
			{
				cont++;
			}
		}
		if(B2)
 		{
			Delay10KTCYx(100);
			if(cont <= 0 )
			{
				cont = 6;
			}
			else
			{
				cont--;
			}
		}
	}
	Delay10KTCYx(100);
	while(!BOOT){}
	segundos += cont * 10;
	cont = 0;

	while(BOOT) // UNIDADE DOS SEGUNDOS
	{
		Delay10KTCYx(100);
		
		EnderecoCursor(0x4A);
		EscreveInteiroLCD(cont);
		EnderecoCursor(0x4A);
		if(B1)
		{
			Delay10KTCYx(100);
			if(cont >= 9)
			{
				cont = 0;
			}
			else
			{
				cont++;
			}
		}
		if(B2)
 		{
			Delay10KTCYx(100);
			if(cont <= 0 )
			{
				cont = 9;
			}
			else
			{
				cont--;
			}
		}
	}
	Delay10KTCYx(100);
	while(!BOOT){}
	segundos += cont;
	cont = 0;

// FIM DA CONFIGURAC�O

}


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
 *
 *****************************************************************************/
// ATEN��O NA SINTAXE de declara��o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{
	if(PIR1bits.TMR1IF)
	{
		WriteTimer1(INICIO_TMR1);		// Escreve o valor correspondente ao atraso de um segundo
		if(overflow < 40)
		{
			overflow++;	
			
		}
		else // 1 segundo
		{
			overflow = 0;
			if(segundos > 0)
			{
				segundos--;
			}
			else
			{
				if(minutos>0)
				{
					minutos-- ;
					segundos = 59;
				}
				else
				{
					BUZZER =1;
					RELE = 1;
					while(!BOOT)
					{
						BUZZER = 0;
						RELE   = 0;
						while(1)
						{}
					}
				}
			}
		}
		PIR1bits.TMR1IF  = 0;	// Zera o flag do timer1	

	}
		
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
 *
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
//UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT atrav�s do BOOTLoader.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca��o da fun��o de tratamento do "reset" da aplica��o principal 
// no endere�o 0x1000 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de ALTA prioridade
// no endere�o 0x1008 da mem�ria de programa.
// 
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x001008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca��o da fun��o de tratamento das interrup��es de BAIXA prioridade 
// no endere�o 0x1018 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x001018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code  	// Diretiva que retorna a aloca��o dos endere�os 
				// da mem�ria de programa para seus valores padr�o

/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/
