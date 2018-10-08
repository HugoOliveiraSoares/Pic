/****************************************************************
Placa Desenvolvimento AFSmartBoard PIC18F4550 by AFEletronica
www.afeletronica.com.br
Arquivos da placa:

Descrição: Mostra Mensagem no LCD 16x2 controlador padrão HD44780, comunicação com LCD no modo "4 bits" usando DB4 à DB7 p/ dados

Detalhes Importantes sobre a Placa e self programming USB:
        - devido ao Bootloader-self programming USB - ocupar do endereço 0x0000 ao 0x0FFF, o programa/ código
        deverá começar sempre à partir do endereço 0x1000, para isto usar sempre o linker script "rm18f4550 - USB Bootloader v2.90a"
        que fará o realocamento na compilação
        - Devido ao Uso com USB o Clock do PIC está em 48MHz, considerar este quando calculando baud, delays, etc.
        - Configurações de IOs e gerais de hardware estão na função AFSmartBoard_Init

Ligações: LCD no PORTB
Pino Placa                Pino LCD
RB0 ------------ 11 (DB4)
RB1 ------------ 12 (DB5)
RB2 ------------ 13 (DB6)
RB3 ------------ 14 (DB7)
RB4 ------------ 6  (EN)
RB5 ------------ 4  (RS)
GND----+ 5  (RW)
+ 1  (Gnd)
+5V----- 2  (Vdd)
Trimpot--------- 3  (Vo)

REV.0 - Janeiro 2016

Notas: usando programa acima endereço 0x1000  - compatibilidade BootLoader USB
*****************************************************************/

#pragma orgall 0x1000

#define  AFSmartBoard_str lcd_out


sbit LCD_RS at RB5_bit;
sbit LCD_EN at RB4_bit;      // CONFIGURAÇAO DOS PINOS DE LCD
sbit LCD_D7 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

sbit LCD_RS_Direction at TRISB5_bit;              // DIREÇAO DOS PINOS DO LCD
sbit LCD_EN_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

char MsgWelcome1 [] = " AFSMARTBOARD   ";
char MsgWelcome2 [] = " PIC 18F4550    ";

char MsgWelcome3 [] = "  Iniciando...  ";
char MsgWelcome4 [] = "     2016       ";

void AFSmartBoard_Init (void);
void Delay_LED (void);
int i;

void main (void) org 0x1000
{

        AFSmartBoard_Init();                // inicia placa

       lcd_init ( );
       lcd_cmd (_LCD_CLEAR);
       lcd_cmd (_LCD_CURSOR_OFF);

       while (1)
       {
       AFSmartBoard_str (1,1, MsgWelcome3 );
       DELAY_MS (500);
       AFSmartBoard_str (2,1, MsgWelcome4 ) ;
       Delay_ms (500);
       LCD_cmd (_LCD_CLEAR);

       AFSmartBoard_str (1,1, MsgWelcome1 );
       DELAY_MS (500);
       AFSmartBoard_str (2,1, MsgWelcome2 ) ;
       Delay_ms (500);



        PORTA.RA4 = 1;

        for (i=0;i<15;i++)
        {
                // alterna LEDs
                PORTA.RA4 ^= 1;
                PORTA.RA5 ^= 1;
                Delay_ms (120);
        }

        while (1)
        {
                // alterna LEDs
                PORTA.RA4 ^= 1;
                PORTA.RA5 ^= 1;
                Delay_ms (120);

        }


}

          }

void AFSmartBoard_Init (void)
{
        RCON = 0X80;                                // LIMPA REGISTRO DE RESET
        ADCON1 = 0x0F;                                // CONFIGURA TODAS AS PORTAS ANALOGICAS COMO I/O

        CMCON = 0x0F;                                // DESABILITA COMPARADOR

    T0CON = 0b11000101;                        // timer ativo, 8 bits,clock interno, preescale 1:64

        TRISA = 0;
        TRISB = 0;                        // todos Saida
        TRISC = 0;
        TRISD = 0;
        TRISE = 0;

        PORTA = 0;                                // nível 0 saída
        PORTB = 0;
        PORTC = 0;
        PORTD = 0;
        PORTE = 0;


}