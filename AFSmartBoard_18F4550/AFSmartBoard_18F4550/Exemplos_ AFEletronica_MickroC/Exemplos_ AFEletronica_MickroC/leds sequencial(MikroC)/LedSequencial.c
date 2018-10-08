/****************************************************************
Placa Desenvolvimento AFBoard PIC18F4550 by AFeletronica
http://www.afeletronica.com.br/pd-296167-placa-desenvolvimento-pic-18f4550-nao-necessita-gravador.html?ct=8ecc4&p=1&s=1
Arquivos da placa:

Descrição: Sequencial de  LEDs em todos IOs da placa

Detalhes Importantes sobre a Placa e self programming USB:
        - devido ao Bootloader-self programming USB - ocupar do endereço 0x0000 ao 0x0FFF, o programa/ código
        deverá começar sempre à partir do endereço 0x1000, para isto usar sempre o linker script "rm18f4550 - USB Bootloader v2.90a"
        que fará o realocamento na compilação
        - Devido ao Uso com USB o Clock do PIC está em 48MHz, considerar este quando calculando baud, delays, etc.
        - Configurações de IOs e gerais de hardware estão na função AFSmartBoard_Init()

Ligações: LEDs externos conectados nos IOs



REV.0 - FEV2016

Notas: usando programa acima endereço 0x1000  - compatibilidade BootLoader USB

*****************************************************************/
#pragma orgall 0x1000

void Board_Init (void);
void Delay_LED (void);

void main (void)  org 0x1000
{
        Board_Init();                // inicia placa

        PORTA = 1;                // acende todos - teste
        PORTB = 1;
        PORTC = 1;
        PORTD = 1;
        PORTE = 1;
        Delay_LED ();
        PORTA = 0;                // apaga todos
        PORTB = 0;
        PORTC = 0;
        PORTD = 0;
        PORTE = 0;
        Delay_LED ();


        while (1)
        {

                PORTA.RA0 = 1;                // Ativa LED
                Delay_LED ();                        // Aguarda tempo aceso
                PORTA.RA0 = 0;                // apaga LED
                PORTA.RA1 = 1;                // e repete ...
                PORTA.RA0 = 0;                // apaga LED
                Delay_LED ();                        //
                PORTA.RA1 = 0;                //
                PORTA.RA2 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTA.RA2 = 0;                //
                PORTA.RA3 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTA.RA3 = 0;                //
                PORTA.RA4 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTA.RA4 = 0;                //
                PORTA.RA5 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTA.RA5 = 0;                //

                PORTE.RE0 = 1;                // e repete ... PORT E
                Delay_LED ();                        //
                PORTE.RE0 = 0;                //
                PORTE.RE1 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTE.RE1 = 0;                //
                PORTE.RE2 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTE.RE2 = 0;                //

                PORTC.RC0 = 1;                // e repete ... PORT C
                Delay_LED ();                        //
                PORTC.RC0 = 0;                //
                PORTC.RC1 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTC.RC1 = 0;                //
                PORTC.RC2 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTC.RC2 = 0;                //
                PORTC.RC6 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTC.RC6 = 0;                //
                PORTC.RC7 = 1;                // e repete ...
                Delay_LED ();                        //
                PORTC.RC7 = 0;                //

                PORTD.RD0 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD0 = 0;                //
                PORTD.RD1 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD1 = 0;                //
                PORTD.RD2 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD2 = 0;                //
                PORTD.RD3 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD3 = 0;                //
                PORTD.RD4 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD4 = 0;                //
                PORTD.RD5 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD5 = 0;                //
                PORTD.RD6 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD6 = 0;                //
                PORTD.RD7 = 1;                // e repete ... PORT D
                Delay_LED ();                        //
                PORTD.RD7 = 0;                //

                PORTB.RB0 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB0 = 0;                //
                PORTB.RB1 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB1 = 0;                //
                PORTB.RB2 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB2 = 0;                //
                PORTB.RB3 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB3 = 0;                //
                PORTB.RB4 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB4 = 0;                //
                PORTB.RB5 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB5 = 0;                //
                PORTB.RB6 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB6 = 0;                //
                PORTB.RB7 = 1;                // e repete ... PORT B
                Delay_LED ();                        //
                PORTB.RB7 = 0;                //

        }


}

void Delay_LED (void)
{
                Delay_ms (40);
}

void Board_Init (void)
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

}