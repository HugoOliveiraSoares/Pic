#pragma orgall 0x1000
void AFSmartBoard_Init (void);

void main (void) org 0x1000
{
  AFSmartBoard_Init(); // fun��o que inicializa a placa AFSmartBoard
  // Alterna um dos Leds
  PORTA.RA5 = 1;

  while (1)
  {
    // Altera o estado que se encontra o LED
    PORTA.RA5 ^= 1;
    PORTA.RA4 ^= 1;
    // Delay
    Delay_ms(2000);
  }

}

void AFSmartBoard_Init (void)
{
  RCON = 0X80; // Limpa o Registro de Reset
  ADCON1 = 0x0F; // Configura todas a portas como Portas Analogicas exeto A0
  CMCON = 0x0F; // Desabilita o Comparador
  LATA = 0;
  TRISA = 0b11001111;
  T0CON = 0b11000101; // Habilita Timer , 8 bits,clock interno, preescale 1:64
  LATB = 0; // Limpa Latch PortB
  TRISB = 0; // Coloca todos como tudo Saida
  LATD = 0;
  TRISD = 0x00; // Colocar PORTD como sa�da
  LATE = 0;
}
