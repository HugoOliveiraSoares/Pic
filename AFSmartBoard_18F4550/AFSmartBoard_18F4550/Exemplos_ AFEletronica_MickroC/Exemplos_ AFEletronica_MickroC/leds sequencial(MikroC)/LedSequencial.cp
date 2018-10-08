#line 1 "F:/PROJETO/AF_PIC/EXEMPLOS MickroC AFEletronica/leds sequencial(MikroC)/LedSequencial.c"
#pragma orgall 0x1000
#line 26 "F:/PROJETO/AF_PIC/EXEMPLOS MickroC AFEletronica/leds sequencial(MikroC)/LedSequencial.c"
void Board_Init (void);
void Delay_LED (void);

void main (void) org 0x1000
{
 Board_Init();

 PORTA = 1;
 PORTB = 1;
 PORTC = 1;
 PORTD = 1;
 PORTE = 1;
 Delay_LED ();
 PORTA = 0;
 PORTB = 0;
 PORTC = 0;
 PORTD = 0;
 PORTE = 0;
 Delay_LED ();


 while (1)
 {

 PORTA.RA0 = 1;
 Delay_LED ();
 PORTA.RA0 = 0;
 PORTA.RA1 = 1;
 PORTA.RA0 = 0;
 Delay_LED ();
 PORTA.RA1 = 0;
 PORTA.RA2 = 1;
 Delay_LED ();
 PORTA.RA2 = 0;
 PORTA.RA3 = 1;
 Delay_LED ();
 PORTA.RA3 = 0;
 PORTA.RA4 = 1;
 Delay_LED ();
 PORTA.RA4 = 0;
 PORTA.RA5 = 1;
 Delay_LED ();
 PORTA.RA5 = 0;

 PORTE.RE0 = 1;
 Delay_LED ();
 PORTE.RE0 = 0;
 PORTE.RE1 = 1;
 Delay_LED ();
 PORTE.RE1 = 0;
 PORTE.RE2 = 1;
 Delay_LED ();
 PORTE.RE2 = 0;

 PORTC.RC0 = 1;
 Delay_LED ();
 PORTC.RC0 = 0;
 PORTC.RC1 = 1;
 Delay_LED ();
 PORTC.RC1 = 0;
 PORTC.RC2 = 1;
 Delay_LED ();
 PORTC.RC2 = 0;
 PORTC.RC6 = 1;
 Delay_LED ();
 PORTC.RC6 = 0;
 PORTC.RC7 = 1;
 Delay_LED ();
 PORTC.RC7 = 0;

 PORTD.RD0 = 1;
 Delay_LED ();
 PORTD.RD0 = 0;
 PORTD.RD1 = 1;
 Delay_LED ();
 PORTD.RD1 = 0;
 PORTD.RD2 = 1;
 Delay_LED ();
 PORTD.RD2 = 0;
 PORTD.RD3 = 1;
 Delay_LED ();
 PORTD.RD3 = 0;
 PORTD.RD4 = 1;
 Delay_LED ();
 PORTD.RD4 = 0;
 PORTD.RD5 = 1;
 Delay_LED ();
 PORTD.RD5 = 0;
 PORTD.RD6 = 1;
 Delay_LED ();
 PORTD.RD6 = 0;
 PORTD.RD7 = 1;
 Delay_LED ();
 PORTD.RD7 = 0;

 PORTB.RB0 = 1;
 Delay_LED ();
 PORTB.RB0 = 0;
 PORTB.RB1 = 1;
 Delay_LED ();
 PORTB.RB1 = 0;
 PORTB.RB2 = 1;
 Delay_LED ();
 PORTB.RB2 = 0;
 PORTB.RB3 = 1;
 Delay_LED ();
 PORTB.RB3 = 0;
 PORTB.RB4 = 1;
 Delay_LED ();
 PORTB.RB4 = 0;
 PORTB.RB5 = 1;
 Delay_LED ();
 PORTB.RB5 = 0;
 PORTB.RB6 = 1;
 Delay_LED ();
 PORTB.RB6 = 0;
 PORTB.RB7 = 1;
 Delay_LED ();
 PORTB.RB7 = 0;

 }


}

void Delay_LED (void)
{
 Delay_ms (40);
}

void Board_Init (void)
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

}
