/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:		US_carro.c
 * Dependencias:		Veja a se��o INCLUDES abaixo
 * Microcontrolador:    PIC18F4550
 * Op��o de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:			C18 v3.37 ou superior
 * Empresa:             SEMPRA
 * Plataforma:			Placa E-P18 v3.6
 * Autor:               Arthur de M. Novaes
 * Vers�o:              v1.0
 * Descri��o:                   Sensor de dist�ncia ultrass�nico utilizado para
 *                              informar ao motorista se ele est� proximo ou n�o
 *                              de um obst�culo que esteja atr�s de seu carro
 *                              quando fora da r�.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necess�rio para que o compilador adicione a biblioteca
                        // com as defini��es do PIC selecionado no projeto, neste
                        // caso, o modelo 18F4550.

#include <delays.h>	// Biblioteca com fun��es de delay do compilador C18

#include "displayLCD.h"	// Biblioteca com fun��es do Display de 7 segmentos

#include <timers.h>     // Biblioteca com fun��es dos timers

#include <delays.h>     // Biblioteca com fun��es dos delays


/** D E F I N E S ************************************************************/
#define DISTANCIA_MAX       14700   // Valor do timer equivalente � 2 metros.
#define ULTRASSOM_CALIB     0       // Calibra��o
#define ULTRASSOM_CONFIG()  TRISBbits.TRISB7 = 1; TRISAbits.TRISA5 = 0;
#define delay50ms()         Delay10KTCYx(60)
#define delay10us()         Delay10TCYx(12)

// Sa�das Digitais
#define BUZZER          LATCbits.LATC1
#define TRIGGER         LATAbits.LATA5

//Entradas digitais
#define	ECHO            PORTBbits.RB7

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);

/******************************************************************************
 * Funcao:		void main(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:   	Fun��o principal do programa.
 *****************************************************************************/
void main(void)
{
    unsigned int distancia;
    unsigned int tempo;
    char a;

    char erro = 0;	// Armazena o valor da contagem de tempo do cronometro

    //Fun��o que faz configura��es do firmware
    ConfiguraSistema();

    // La�o de repeti��o infinito que executa aplica��o do firmware
    while(1)
    {
        // Condi��es para acionamento do buzzer
        
        if (distancia < 5)
        {
            for (a=0;a<8;a++){
                BUZZER = 1;
                delay50ms ();
                delay50ms ();
            }
            BUZZER = 0;
        }
        else if (distancia < 10)
        {
            for (a=0;a<6;a++){
                BUZZER = !BUZZER;
                delay50ms ();
            }
        }
        else if (distancia < 20)
        {
            for (a=0;a<4;a++){
                BUZZER = !BUZZER;
                delay50ms();
                delay50ms();
            }
        }
        else if (distancia < 30)
        {
            for (a=0;a<2;a++)
            {
                BUZZER = !BUZZER;
                delay50ms();
                delay50ms();
                delay50ms();
            }
        }

        erro = 0;
        // Envia um pulso no Trigger de 10uS.
        TRIGGER = 1;
        delay10us();
        TRIGGER = 0;

        // O programa para nessa parte para esperar o echo estar em zero
        while (ECHO == 0);

        // Assim que ele for para n�vel l�gico positivo, escreve-se 0 no valor
        // do Timer1 e inicia-se a contagem.
        WriteTimer0(0);

        // Permanece nesse la�o enquanto Echo for igual � 1 e erro igual � 0
        while (ECHO && erro == 0)
        {
            if (ReadTimer0() > DISTANCIA_MAX)
            {
                // Se o valor do timer for maior que a nossa distancia m�xima,
                // consideramos um erro, quando isso ocorre, saimos deste la�o e
                // entramos em uma rotina que indique o erro
                erro = 1;
            } // end if
        } // end while

        // Salva o valor do timer na vari�vel tempo
        tempo = ReadTimer0();

        // Se a dist�ncia n�o exceder nosso limite, entra nessa condi��o
        if (erro != 1)
        {
            //Pega o valor do timer e calcula a distancia.
            // distancia = Valor lido do TRM0 * PRE / FOSC * velocidade SOM * 100 / 2 + CALIBRACAO
            //distancia = (((ReadTimer0() * 8 / 12000000.0) * 340 * 100  )/ 2) + ULTRASSOM_CALIB ;
            // 8 / 12000000 * 340 * 100 / 2 = 0.011333333

            distancia = tempo * 0.011333333 + ULTRASSOM_CALIB;
            PosicaoCursorLCD(1,1);
            EscreveFraseRomLCD("Dist: ");
            EscreveInteiroLCD(distancia);
            EscreveFraseRomLCD("   ");
            PosicaoCursorLCD(2,1);
            EscreveFraseRomLCD("Tempo: ");
            EscreveInteiroLCD(tempo);
            EscreveFraseRomLCD("   ");
        } // end if

        // Condi��o para quando a distancia exceder o limite definido em
        // DISTANCIA_MAX
        else
        {
            PosicaoCursorLCD(1,1);
            EscreveFraseRomLCD("Dist: erro");
            EscreveFraseRomLCD("   ");
            PosicaoCursorLCD(2,1);
            EscreveFraseRomLCD("Tempo: erro");
            EscreveFraseRomLCD("   ");

            // delay necessario para que o sensor coloque o ECO em zero
            Delay10KTCYx(0);
        } // end else
    }//end while
}//end main


/******************************************************************************
 * Funcao:		void ConfiguraSistema(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri��o:	ConfiguraSistema � a rotina de configura��o principal do PIC.
 *		Seu objetivo � configurar as portas de I/O e os perif�ricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
    // Desabilita pinos anal�gicos
    ADCON1 = ADCON1 | 0x0f;

    // Configura entradas digitais
    TRISCbits.TRISC1 = 0; 	// Buzzer como sa�da digital
    LATCbits.LATC1 = 0;

    ULTRASSOM_CONFIG();

    ConfiguraLCD();

    OpenTimer0 (TIMER_INT_OFF       & // Interrup��o do timer desligado
                    T0_16BIT        & // 16 bits
                    T0_SOURCE_INT   & // Fonte do clock: interno
                    T0_PS_1_8         // Prescaler de 1/8
                    );


}//end ConfiguraSistema



/********************************** ********************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri�?o:	Fun�?o de tratamento das interrup�?es de ALTA prioridade
 *		Nessa fun�?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup�?o, comparando
 *		os flags de cada tipo de interrup�?o.
 *			2- tratar a interrup�?o selecionada.
 *			3- limpar o flag que causou a interrup�?o!!! Importante
 *		para garantir que n?o ocorrer� uma chamada indesejada ao sair
 *		do tratamento da interrup�?o.
 *
 *		Ao sair dessa fun�?o � usado o retorno do tipo "retfie fast",
 *		pois esta fun�?o � declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATEN�?O NA SINTAXE de declara�?o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{

}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Sa�da:		Nenhuma (void)
 * Descri�?o:	Fun�?o de tratamento das interrup�?es de BAIXA prioridade
 *		Nessa fun�?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrup�?o, comparando
 *		os flags de cada tipo de interrup�?o.
 *			2- tratar a interrup�?o selecionada.
 *			3- limpar o flag que causou a interrup�?o!!! Importante
 *		para garantir que n?o ocorrer� uma chamada indesejada ao sair
 *		do tratamento da interrup�?o.
 *
 *		Ao sair dessa fun�?o � usado o retorno do tipo "retfie",
 *		pois esta fun�?o � declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATEN�?O NA SINTAXE de declara�?o com #pragma interruptlow = Baixa prioridade

#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{

}//end Tratamento_Low_Interrupt

/** V E C T O R   R E M A P P I N G ******************************************/
// Se�?o necess�ria para informar ao compilador C18 onde s?o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrup�?o.

//
// ATEN�?O: Copiar esta parte do c�digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para grava�?o in-circuit.

// prot�tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Aloca�?o da fun�?o de tratamento do "reset" da aplica�?o principal
// no endere�o 0x1000 da mem�ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Aloca�?o da fun�?o de tratamento das interrup�?es de ALTA prioridade
// no endere�o 0x1008 da mem�ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Aloca�?o da fun�?o de tratamento das interrup�?es de BAIXA prioridade
// no endere�o 0x1018 da mem�ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a aloca�?o dos endere�os
				// da mem�ria de programa para seus valores padr?o

/** F I M  D A  S E � ? O  D E   V E C T O R   R E M A P P I N G *************/
