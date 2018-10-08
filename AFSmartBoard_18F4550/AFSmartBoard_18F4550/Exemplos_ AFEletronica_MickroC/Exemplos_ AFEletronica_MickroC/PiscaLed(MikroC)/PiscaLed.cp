#line 1 "F:/PROJETO/AF_PIC/EXEMPLOS MickroC AFEletronica/PiscaLed/PiscaLed.c"
#pragma orgall 0x1000
#line 2 "F:/PROJETO/AF_PIC/EXEMPLOS MickroC AFEletronica/PiscaLed/PiscaLed.c"
void AFSmartBoard_Init (void);
void main (void) org 0x1000
{
AFSmartBoard_Init();

PORTA.RA5 = 1;
while (1)
{

PORTA.RA5 ^= 1;
PORTA.RA4 ^= 1;

Delay_ms(2000);
}
}
void AFSmartBoard_Init (void)
{
RCON = 0X80;
ADCON1 = 0x0F;
CMCON = 0x0F;
LATA = 0;
TRISA = 0b11001111;
T0CON = 0b11000101;
LATB = 0;
TRISB = 0;
LATD = 0;
TRISD = 0x00;
LATE = 0;
}
