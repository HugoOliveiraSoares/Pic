/******************************************************************************
 *
 *            Curso SEMPRA de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     main.c master
 * Dependencias:    	Veja a seção INCLUDES abaixo
 * Processador:       	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU:48MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Descrição:		Configurações do PIC18 para se trabalhar como MESTRE.
 *                      Velocidade de comunicação de 100kHz.
  *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>// Biblioteca do compilador C18 com configuraç±oes da
                    // família PIC18

#include <i2c.h>// Biblioteca do compilador C18 com funç±oes para uso do módulo
                // I2C

#include "TimeDelay.h"// Biblioteca com funções de Delay

/******************************************************************************
 * Funcao:      void main(void)
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * Descrição:   Função principal do programa. O termo "main" significa 
 *		principal, e isto é relacionado a esta função pois eh a 
 *		mesma é a primeira a ser chamada apos o reset da PIC.
 *		Todas as outras funções sao chamadas a partir da "main".
 *****************************************************************************/
void main(void)
{
    char codigo = 0;
    ADCON1 |= 0x0F;// Configura todos os pinos como digital

    // Configuração pedida pelo módulo I2C, pinos de SCL e SDA como entrada
    // digitais no modo MESTRE
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;

    TRISDbits.TRISD1 = 0;// Configura o pino RC1 como saida digital
    TRISCbits.TRISC2 = 0;// Configura o pino RC2 como saida digital

    TRISEbits.TRISE1 = 1;// Configura o pino RE1 como entrada digital
    TRISEbits.TRISE2 = 1;// Configura o pino RE2 como entrada digital

    LATDbits.LATD1 = 0; // Inicia o LED desligado
    LATCbits.LATC2 = 0; // Inicia o LED desligado

    // Configura o módulo I2C.
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
            while(PORTEbits.RE1){}// Espera o usuário soltar o botão

            IdleI2C();// Espera até que o barramento esteja liberado
            StartI2C();// Gera uma condição de Start

            // Envio do endereço do escravo
            if(WriteI2C(0xA0) == 0)// Envia o endereço do escravo a ser
                                   // contactado e verifica se o envio teve
                                   // sucesso. Endereço enviado com sinal de
                                   // Escrita.
            {
                // Caso o escravo tenha respondido com um Ack
                // continua a comunicação
                IdleI2C();
                // Envio de dados para o escravo
                if(!WriteI2C(1))// Envio de dados para o escravo selecionado
                {
                    IdleI2C();// Espera até que o barramento seja liberado
                    StopI2C();// Gera uma condição de Stop
                }// Fim if
                else
                {
                    // Caso ocorra um erro na comunicação liga/desliga o LED
                    // e para a comunicação
                    IdleI2C();// Espera até que o barramento seja liberado
                    // Liga ou desliga o led indicando que houve um erro na
                    // comunicação
                    LATDbits.LATD1 = !LATDbits.LATD1;
                    StopI2C();// Gera uma condição de Stop
                }// Fim else

            }// Fim if WriteI2C
            // Caso o sinal de Ack não seja recebido termina a comunicação
            else
            {
                IdleI2C();// Espera até que o barramento seja liberado
                StopI2C();// Gera uma condição de Stop
            }// Fim else
        }// Fim if PORTEbits.RE1

        // Verifica o estado do pino RE2
        if (PORTEbits.RE2)
        {
            DelayMs(1);// Debounce
            while(PORTEbits.RE2){}// Espera o usuário soltar o botão

            IdleI2C();// Espera até que o barramento esteja liberado
            StartI2C();// Gera uma condição de Start

            // Envio do endereço do escravo
            if(WriteI2C(0xA1) == 0)// Envia o endereço do escravo a ser
                                   // contactado e verifica se o envio teve
                                   // sucesso. Endereço enviado com sinal de
                                   // leitura
            {
                // Caso o escravo tenha respondido com um Ack
                // continua a comunicação
                IdleI2C();// Espera até que o barramento seja liberado
                codigo = ReadI2C();// Armazena o dado lido

                IdleI2C();// Espera até que o barramento seja liberado
                StopI2C();// Gera uma condição de Stop

                // Verifica o dado recebido
                if (codigo == 1)
                {
                    LATCbits.LATC2 = !LATCbits.LATC2;// Inverte o estado do LED
                }// Fim if codigo == 1
            }// Fim if WriteI2C(endereço)
        }// Fim if RE2
    }// Fim while 1
}//Fim main

/** V E C T O R   R E M A P P I N G ******************************************/
// Seção necessár§ia para informar ao compilador C18 onde são os novos endereços
//da memória de programa que ele deve alocar as rotinas de tratamento do evento
//de "reset" do microcontrolador.
//
//ATENÇÃO: COPIAR ESTA SEÇÃO DO CODIGO PARA TODO ARQUIVO "main.c" DOS PROJETOS
//QUE UTILIZAM O BOOTLOADER PARA GRAVAÇÃO IN-CIRCUIT.

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code
/** F I M  D A  S E Ç Ã O  D E   V E C T O R   R E M A P P I N G *************/

/** EOF main.c ***************************************************************/
