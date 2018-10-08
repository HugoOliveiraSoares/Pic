#line 1 "F:/PROJETO/AF_PIC/EXEMPLOS MickroC AFEletronica/LCD16x2(MikroC)/Lcd16x2(MicroC).c"
#pragma orgall 0x1000
#line 38 "F:/PROJETO/AF_PIC/EXEMPLOS MickroC AFEletronica/LCD16x2(MikroC)/Lcd16x2(MicroC).c"
sbit LCD_RS at RB5_bit;
sbit LCD_EN at RB4_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

sbit LCD_RS_Direction at TRISB5_bit;
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

 AFSmartBoard_Init();

 lcd_init ( );
 lcd_cmd (_LCD_CLEAR);
 lcd_cmd (_LCD_CURSOR_OFF);

 while (1)
 {
  lcd_out  (1,1, MsgWelcome3 );
 DELAY_MS (500);
  lcd_out  (2,1, MsgWelcome4 ) ;
 Delay_ms (500);
 LCD_cmd (_LCD_CLEAR);

  lcd_out  (1,1, MsgWelcome1 );
 DELAY_MS (500);
  lcd_out  (2,1, MsgWelcome2 ) ;
 Delay_ms (500);



 PORTA.RA4 = 1;

 for (i=0;i<15;i++)
 {

 PORTA.RA4 ^= 1;
 PORTA.RA5 ^= 1;
 Delay_ms (120);
 }

 while (1)
 {

 PORTA.RA4 ^= 1;
 PORTA.RA5 ^= 1;
 Delay_ms (500);

 }


}

 }

void AFSmartBoard_Init (void)
{
 RCON = 0X80;
 ADCON1 = 0x0F;

 CMCON = 0x0F;

 T0CON = 0b11000101;

 TRISA = 0;
 TRISB = 0;
 TRISC = 0;
 TRISD = 0;
 TRISE = 0;

 PORTA = 0;
 PORTB = 0;
 PORTC = 0;
 PORTD = 0;
 PORTE = 0;


}
