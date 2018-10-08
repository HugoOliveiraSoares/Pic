/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c master
 * Dependencias:    	Veja a se��o INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Descri��o:		Configura��es do PIC18 para se trabalhar como MESTRE.
 *                      Velocidade de comunica��o de 100kHz.
  *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>// Biblioteca do compilador C18 com configura�oes da
                    // fam�lia PIC18

#include <i2c.h>// Biblioteca do compilador C18 com fun�oes para uso do m�dulo
                // I2C

#include "TimeDelay.h"// Biblioteca com fun��es de Delay

/******************************************************************************
 * Funcao:      void main(void)
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Fun��o principal do programa. O termo "main" significa 
 *		principal, e isto � relacionado a esta fun��o pois eh a 
 *		mesma � a primeira a ser chamada apos o reset da PIC.
 *		Todas as outras fun��es sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{
    char codigo = 0;
    ADCON1 |= 0x0F;// Configura todos os pinos como digital

    // Configura��o pedida pelo m�dulo I2C, pinos de SCL e SDA como entrada
    // digitais no modo MESTRE
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;

    TRISDbits.TRISD1 = 0;// Configura o pino RC1 como saida digital
    TRISCbits.TRISC2 = 0;// Configura o pino RC2 como saida digital

    TRISEbits.TRISE1 = 1;// Configura o pino RE1 como entrada digital
    TRISEbits.TRISE2 = 1;// Configura o pino RE2 como entrada digital

    LATDbits.LATD1 = 0; // Inicia o LED desligado
    LATCbits.LATC2 = 0; // Inicia o LED desligado

    // Configura o m�dulo I2C.
    // Modo mestre e bitRate desejado = 100kHz
    OpenI2C(MASTER, SLEW_OFF);

    // bitRate desejado = 100kHz
    // Fosc =  48MHz
    // SSPADD = ((Fosc/bitRate)/4)-1
    SSPADD = 119;

    // Loop Infinito
    while (1)
    {
        // Verfica o estado do pino RE1
        if (PORTEbits.RE1)
        {
            DelayMs(1);// Debounce
            while(PORTEbits.RE1){}// Espera o usu�rio soltar o bot�o

            IdleI2C();// Espera at� que o barramento esteja liberado
            StartI2C();// Gera uma condi��o de Start

            // Envio do endere�o do escravo
            if(WriteI2C(0xA0) == 0)// Envia o endere�o do escravo a ser
                                   // contactado e verifica se o envio teve
                                   // sucesso. Endere�o enviado com sinal de
                                   // Escrita.
            {
                // Caso o escravo tenha respondido com um Ack
                // continua a comunica��o
                IdleI2C();
                // Envio de dados para o escravo
                if(!WriteI2C(1))// Envio de dados para o escravo selecionado
                {
                    IdleI2C();// Espera at� que o barramento seja liberado
                    StopI2C();// Gera uma condi��o de Stop
                }// Fim if
                else
                {
                    // Caso ocorra um erro na comunica��o liga/desliga o LED
                    // e para a comunica��o
                    IdleI2C();// Espera at� que o barramento seja liberado
                    // Liga ou desliga o led indicando que houve um erro na
                    // comunica��o
                    LATDbits.LATD1 = !LATDbits.LATD1;
                    StopI2C();// Gera uma condi��o de Stop
                }// Fim else

            }// Fim if WriteI2C
            // Caso o sinal de Ack n�o seja recebido termina a comunica��o
            else
            {
                IdleI2C();// Espera at� que o barramento seja liberado
                StopI2C();// Gera uma condi��o de Stop
            }// Fim else
        }// Fim if PORTEbits.RE1

        // Verifica o estado do pino RE2
        if (PORTEbits.RE2)
        {
            DelayMs(1);// Debounce
            while(PORTEbits.RE2){}// Espera o usu�rio soltar o bot�o

            IdleI2C();// Espera at� que o barramento esteja liberado
            StartI2C();// Gera uma condi��o de Start

            // Envio do endere�o do escravo
            if(WriteI2C(0xA1) == 0)// Envia o endere�o do escravo a ser
                                   // contactado e verifica se o envio teve
                                   // sucesso. Endere�o enviado com sinal de
                                   // leitura
            {
                // Caso o escravo tenha respondido com um Ack
                // continua a comunica��o
                IdleI2C();// Espera at� que o barramento seja liberado
                codigo = ReadI2C();// Armazena o dado lido

                IdleI2C();// Espera at� que o barramento seja liberado
                StopI2C();// Gera uma condi��o de Stop

                // Verifica o dado recebido
                if (codigo == 1)
                {
                    LATCbits.LATC2 = !LATCbits.LATC2;// Inverte o estado do LED
                }// Fim if codigo == 1
            }// Fim if WriteI2C(endere�o)
        }// Fim if RE2
    }// Fim while 1
}//Fim main

/** V E C T O R   R E M A P P I N G ******************************************/
// Se��o necess�r�ia para informar ao compilador C18 onde s�o os novos endere�os
//da mem�ria de programa que ele deve alocar as rotinas de tratamento do evento
//de "reset" do microcontrolador.
//
//ATEN��O: COPIAR ESTA SE��O DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS
//QUE UTILIZAM O BOOTLOADER PARA GRAVA��O IN-CIRCUIT.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code
/** F I M  D A  S E � � O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
