/******************************************************************************
 *
 *            SEMPRA PROJETOS PLACA E-P18 (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:		US_carro.c
 * Dependencias:		Veja a seção INCLUDES abaixo
 * Microcontrolador:    PIC18F4550
 * Opção de Clock:		HS 20MHz (externo) - CPU:48MHz (interno)
 * Compilador:			C18 v3.37 ou superior
 * Empresa:             SEMPRA
 * Plataforma:			Placa E-P18 v3.6
 * Autor:               Arthur de M. Novaes
 * Versão:              v1.0
 * Descrição:                   Sensor de distância ultrassônico utilizado para
 *                              informar ao motorista se ele está proximo ou não
 *                              de um obstáculo que esteja atrás de seu carro
 *                              quando fora da ré.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>	// Necessário para que o compilador adicione a biblioteca
                        // com as definições do PIC selecionado no projeto, neste
                        // caso, o modelo 18F4550.

#include <delays.h>	// Biblioteca com funções de delay do compilador C18

#include "displayLCD.h"	// Biblioteca com funções do Display de 7 segmentos

#include <timers.h>     // Biblioteca com funções dos timers

#include <delays.h>     // Biblioteca com funções dos delays


/** D E F I N E S ************************************************************/
#define DISTANCIA_MAX       14700   // Valor do timer equivalente à 2 metros.
#define ULTRASSOM_CALIB     0       // Calibração
#define ULTRASSOM_CONFIG()  TRISBbits.TRISB7 = 1; TRISAbits.TRISA5 = 0;
#define delay50ms()         Delay10KTCYx(60)
#define delay10us()         Delay10TCYx(12)

// Saídas Digitais
#define BUZZER          LATCbits.LATC1
#define TRIGGER         LATAbits.LATA5

//Entradas digitais
#define	ECHO            PORTBbits.RB7

/**  P R O T O T I P O S   P R I V A D O S ***********************************/
void ConfiguraSistema(void);

/******************************************************************************
 * Funcao:		void main(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição:   	Função principal do programa.
 *****************************************************************************/
void main(void)
{
    unsigned int distancia;
    unsigned int tempo;
    char a;

    char erro = 0;	// Armazena o valor da contagem de tempo do cronometro

    //Função que faz configurações do firmware
    ConfiguraSistema();

    // Laço de repetição infinito que executa aplicação do firmware
    while(1)
    {
        // Condições para acionamento do buzzer
        
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

        // Assim que ele for para nível lógico positivo, escreve-se 0 no valor
        // do Timer1 e inicia-se a contagem.
        WriteTimer0(0);

        // Permanece nesse laço enquanto Echo for igual à 1 e erro igual à 0
        while (ECHO && erro == 0)
        {
            if (ReadTimer0() > DISTANCIA_MAX)
            {
                // Se o valor do timer for maior que a nossa distancia máxima,
                // consideramos um erro, quando isso ocorre, saimos deste laço e
                // entramos em uma rotina que indique o erro
                erro = 1;
            } // end if
        } // end while

        // Salva o valor do timer na variável tempo
        tempo = ReadTimer0();

        // Se a distância não exceder nosso limite, entra nessa condição
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

        // Condição para quando a distancia exceder o limite definido em
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
 * Saída:		Nenhuma (void)
 * Descrição:	ConfiguraSistema é a rotina de configuração principal do PIC.
 *		Seu objetivo é configurar as portas de I/O e os periféricos
 *		do microcontrolador para que os mesmos trabalhem da maneira
 *		desejada no projeto.
 *****************************************************************************/
void ConfiguraSistema(void)
{
    // Desabilita pinos analógicos
    ADCON1 = ADCON1 | 0x0f;

    // Configura entradas digitais
    TRISCbits.TRISC1 = 0; 	// Buzzer como saída digital
    LATCbits.LATC1 = 0;

    ULTRASSOM_CONFIG();

    ConfiguraLCD();

    OpenTimer0 (TIMER_INT_OFF       & // Interrupção do timer desligado
                    T0_16BIT        & // 16 bits
                    T0_SOURCE_INT   & // Fonte do clock: interno
                    T0_PS_1_8         // Prescaler de 1/8
                    );


}//end ConfiguraSistema



/********************************** ********************************************
 * Funcao:		void Tratamento_High_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Saï¿½da:		Nenhuma (void)
 * Descriï¿½?o:	Funï¿½?o de tratamento das interrupï¿½?es de ALTA prioridade
 *		Nessa funï¿½?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupï¿½?o, comparando
 *		os flags de cada tipo de interrupï¿½?o.
 *			2- tratar a interrupï¿½?o selecionada.
 *			3- limpar o flag que causou a interrupï¿½?o!!! Importante
 *		para garantir que n?o ocorrerï¿½ uma chamada indesejada ao sair
 *		do tratamento da interrupï¿½?o.
 *
 *		Ao sair dessa funï¿½?o ï¿½ usado o retorno do tipo "retfie fast",
 *		pois esta funï¿½?o ï¿½ declarada como ALTA prioridade com a diretiva
 *		#pragma interrupt
 *****************************************************************************/
// ATENï¿½?O NA SINTAXE de declaraï¿½?o com #pragma interrupt = Alta prioridade
#pragma interrupt Tratamento_High_Interrupt
void Tratamento_High_Interrupt(void)
{

}// end Tratamento_High_Interrupt

/******************************************************************************
 * Funcao:		void Tratamento_Low_Interrupt(void)
 * Entrada:		Nenhuma (void)
 * Saï¿½da:		Nenhuma (void)
 * Descriï¿½?o:	Funï¿½?o de tratamento das interrupï¿½?es de BAIXA prioridade
 *		Nessa funï¿½?o deve-se lembrar de fazer a seguinte lista:
 *			1- verificar qual foi a causa da interrupï¿½?o, comparando
 *		os flags de cada tipo de interrupï¿½?o.
 *			2- tratar a interrupï¿½?o selecionada.
 *			3- limpar o flag que causou a interrupï¿½?o!!! Importante
 *		para garantir que n?o ocorrerï¿½ uma chamada indesejada ao sair
 *		do tratamento da interrupï¿½?o.
 *
 *		Ao sair dessa funï¿½?o ï¿½ usado o retorno do tipo "retfie",
 *		pois esta funï¿½?o ï¿½ declarada como BAIXA prioridade com a diretiva
 *		#pragma interruptlow
 *****************************************************************************/
// ATENï¿½?O NA SINTAXE de declaraï¿½?o com #pragma interruptlow = Baixa prioridade

#pragma interruptlow Tratamento_Low_Interrupt
void Tratamento_Low_Interrupt(void)
{

}//end Tratamento_Low_Interrupt

/** V E C T O R   R E M A P P I N G ******************************************/
// Seï¿½?o necessï¿½ria para informar ao compilador C18 onde s?o os novos endereï¿½os
//da memï¿½ria de programa que ele deve alocar as rotinas de tratamento do "reset"
//do microcontrolador e das rotinas de tratamento de interrupï¿½?o.

//
// ATENï¿½?O: Copiar esta parte do cï¿½digo dentro do arquivo "main.c" dos
// projetos usados com o Bootloader USB-HID para gravaï¿½?o in-circuit.

// protï¿½tipo usado pelo compilador C18
extern void _startup (void);        // See c018i.c in your C18 compiler dir

// Alocaï¿½?o da funï¿½?o de tratamento do "reset" da aplicaï¿½?o principal
// no endereï¿½o 0x1000 da memï¿½ria de programa
#pragma code REMAPPED_RESET_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}

// Alocaï¿½?o da funï¿½?o de tratamento das interrupï¿½?es de ALTA prioridade
// no endereï¿½o 0x1008 da memï¿½ria de programa.
//
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    _asm goto Tratamento_High_Interrupt _endasm
}

// Alocaï¿½?o da funï¿½?o de tratamento das interrupï¿½?es de BAIXA prioridade
// no endereï¿½o 0x1018 da memï¿½ria de programa
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
    _asm goto Tratamento_Low_Interrupt _endasm
}

#pragma code	// Diretiva que retorna a alocaï¿½?o dos endereï¿½os
				// da memï¿½ria de programa para seus valores padr?o

/** F I M  D A  S E ï¿½ ? O  D E   V E C T O R   R E M A P P I N G *************/
