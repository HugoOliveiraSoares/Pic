/******************************************************************************
 *
 *            SEMPRATEC - Sistemas Microcontrolados
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.c
 * Dependencias:    	Veja arquivo "my_xlcd.h"
 * Processador:       	PIC18F4550 ou PIC18F2550
 * Op��o de Clock:	HS 20MHz (externo) - CPU: 48MHz	
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA - Axoon - UFMG
 *
 *
 *                  Porta	::   Display LCD
 *
 * 			RB0 	::	  D0
 *			RB1   	::	  D1
 *			RB2   	::	  D2
 *			RB3  	::	  D3
 *      		RB4  	::	  D4
 *			RB5   	::	  D5
 *			RB6  	::	  D6
 *			RB7   	::	  D7
 *                              
 *									
 *			RD7     :: 	  EN
 *			RD6	::	  R/W
 *			RD5    	::	  RS
 *
 *
 *									
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include "displayLCD_mini.h"


/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:	void ConfiguraLCD(void)
 * Entrada:	Nenhuma (void)
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	Configura portas do PIC 18F4550 que est�o conectadas ao 
 *		display LCD como saida. Essa rotina � baseada no controlador 
 *		de LCD Hitachi HD44780. Configura os parametros de comunica��o
 *		com o display, tais como:
 *			- modo de opera��o (4 ou 8 data bits)
 *			- tipo de cursor
 *			- tamanho da fonte
 *		Ao final da configura��o limpa o display.
 *****************************************************************************/
void ConfiguraLCD(void)
{
	// Desabilita todas as 13 portas anal�gicas ANx (portas do conversor A/D),
	// assim as mesmas fucionam como pinos digitais
	ADCON1 |= 0x0F;

	// Configura os pinos de controle (RW,RS,E) como sa�da.
	//n�o usado // 	TRIS_RW = 0;
	TRIS_RS = 0;
	TRIS_E = 0;

	// Configura os pinos de dados (D4,D5,D6,D7) como sa�da.
	TRIS_D4=0;
	TRIS_D5=0;
	TRIS_D6=0;
	TRIS_D7=0;

// Inicio da rotina de inicializa��o do display LCD
// Aguardar tempos e enviar 3 vezes o comando 0b0011XXXX como descrito no datasheet
// do controlador HD44780 ou SPLC780D

	//Seleciona pinos de Controle para escrita do comando
	//n�o usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//selecioan pinos de dados com comando de inicializa��o 0b0011 no Nibble-High
	//(os 4 bits de dados mais significativos), os bits do Nibble-Low s�o Don't Care 
	D7=0;
	D6=0;
	D5=1;
	D4=1;

//Passo 1: Envio do comando de inicializa��o 0b0011

	// Delay inicial de 15ms ap�s alimentar o LCD: Vdd > 4,5V
	DELAY_5ms();
	DELAY_5ms();
	DELAY_5ms();

	//Habilita leitura do comando pelo LCD, atrav�s do pino de enable, para tanto,
	//um pulso de 1ms com borda de descida � efetuado
	E_PIN = 1;      			
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 2: Envio do comando de inicializa��o 0b0011

	// Delay de pelo menos 4.1ms
	DELAY_5ms();

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;      			
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 3: Envio do comando de inicializa��o 0b0011

	// Delay de pelo menos 100us
	DELAY_5ms();

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;      			
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 4: Envio da Configura��o 0b0010 no Nibble-High
	D7=0;
	D6=0;
	D5=1;
	D4=0;


	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;      			
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();


//Envio dos comandos de Configura��o do LCD
	EscreveComandoLCD(0b00101000);	// Function Set: 4bit interface, 2 lines, Font 5x7  
	EscreveComandoLCD(0b00000110);	// Entry mode set: Increment, Shift OFF
	EscreveComandoLCD(0b00001110);	// Display Control: Display ON, Cursor ON, Blink OFF
	EscreveComandoLCD(0b00000001);	// Clear display
}

/******************************************************************************
 * Funcao:	void EscreveComandoLCD(unsigned char cmd)
 * Entrada:	cmd: comando que ser� enviado para o LCD
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	(Write a command to the LCD)
 *		Escreve um comando para o display de LCD.
 *****************************************************************************/
void EscreveComandoLCD(unsigned char cmd)
{
	//Seleciona pinos de Controle para escrita do comando
	//n�o usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;	// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	if(cmd&0b00010000){D4=1;}
	else {D4=0;}
	if(cmd&0b00100000){D5=1;}
	else {D5=0;}
	if(cmd&0b01000000){D6=1;}
	else {D6=0;}
	if(cmd&0b10000000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

	//Seleciona pinos de Dados: Nibble-Low
	if(cmd&0b00000001){D4=1;}
	else {D4=0;}
	if(cmd&0b00000010){D5=1;}
	else {D5=0;}
	if(cmd&0b00000100){D6=1;}
	else {D6=0;}
	if(cmd&0b00001000){D7=1;}
	else {D7=0;}    

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

/******************************************************************************
 * Funcao:	void EnderecoCursor(unsigned char endereco)
 * Entrada:	endereco: endere�o da memoria de dados do display que se deseja apontar
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	(Set the Display Data RAM Address)
 *		Essa rotina seta o endere�o da memoria RAM de dados do 
 *		display LCD para o endere�o	que se deseja escrever um caracter
 *		usando as fun��es EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
void EnderecoCursor(unsigned char endereco)
{
	//Seleciona pinos de Controle para escrita do comando
	//n�o usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	D7 = 1;	
	if(endereco&0b00010000){D4=1;}
	else {D4=0;}
	if(endereco&0b00100000){D5=1;}
	else {D5=0;}
	if(endereco&0b01000000){D6=1;}
	else {D6=0;}
	
	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

	//Seleciona pinos de Dados: Nibble-Low
	if(endereco&0b00000001){D4=1;}
	else {D4=0;}
	if(endereco&0b00000010){D5=1;}
	else {D5=0;}
	if(endereco&0b00000100){D6=1;}
	else {D6=0;}
	if(endereco&0b00001000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

/******************************************************************************
 * Funcao:	void PosicaoCursorLCD(unsigned char endereco)
 * Entrada:	N�mero da linha e da coluna em que se desja escrever o caracter 
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	(Set the Display Data RAM Address)
 *		Essa rotina posiciona o cursor do display de LCD para a linha
 *		e coluna em que se deseja escrever um caracter usando as fun��es
 *		EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
void PosicaoCursorLCD(unsigned char linha, unsigned char coluna)
{
	#define linha1	0x00
	#define	linha2	0x40
	
	unsigned char endereco = 0x00;
	
	coluna--;
	
	if (coluna >= 0)
	{
		switch (linha)
		{
			case 1: // 	linha1Desliga ambos pontos decimais
				endereco = linha1 + coluna;
				EnderecoCursor(endereco);		
			break;
		
			case 2: // 	linha1Desliga ambos pontos decimais
				endereco = linha2 + coluna;
				EnderecoCursor(endereco);
			break;
		
			default:
				endereco = linha1;
			break;
		}
	}
	else
	{
		endereco = linha1;
	}
}

/******************************************************************************
 * Funcao:	void EscreveCaractereLCD(unsigned char data)
 * Entrada:	data: Byte de dados para ser escrito na memoria RAM do LCD
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	(Write a Data byte to the LCD)
 *		Essa rotina escreve o byte de caracteres no display a partir da
 *		posi��o de memoria atual do cursor ou da posi��o de mem�ria
 *		escolhida com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveCaractereLCD(char data)
{
	//Seleciona pinos de Controle para escrita do comando
	//n�o usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 1;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	if(data&0b00010000){D4=1;}
	else {D4=0;}
	if(data&0b00100000){D5=1;}
	else {D5=0;}
	if(data&0b01000000){D6=1;}
	else {D6=0;}
	if(data&0b10000000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();


	//Seleciona pinos de Dados: Nibble-Low
	if(data&0b00000001){D4=1;}
	else {D4=0;}
	if(data&0b00000010){D5=1;}
	else {D5=0;}
	if(data&0b00000100){D6=1;}
	else {D6=0;}
	if(data&0b00001000){D7=1;}
	else {D7=0;}    

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

/******************************************************************************
 * Funcao:	void EscreveInteiroLCD(int valor)
 * Entrada:	valor: inteiro com sinal (de -32768 a 32767) a ser escrito no
 *		display.
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	Essa rotina escreve o numero inteiro no display a partir da posi��o
 *		de memoria atual do cursor ou da posi��o de mem�ria escolhida com as
 *		fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveInteiroLCD(int valor)
{
	char texto[7] = " ";
	itoa( valor, texto);
	EscreveFraseRamLCD(texto);
} 
 
/******************************************************************************
 * Funcao:	void EscreveFraseRamLCD(char *buffer)
 * Entrada:	*buffer: apontador para string na memoria de dados(RAM)
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	Essa rotina copia uma string terminada com caracter nulo
 *		da memoria de dados do microcontrolador para o display de LCD.
 *		A string apontada por *buffer � copiada no display a partir da
 *		posi��o de memoria atual do cursor ou da posi��o de mem�ria
 *		escolhida com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveFraseRamLCD(char *buffer)
{
	while(*buffer)                  // escreve dados no LCD ate achar caracter nulo
	{
	        EscreveCaractereLCD(*buffer); // escreve caracter no LCD
	        buffer++;               // incrementa apontador
	}
}

/******************************************************************************
 * Funcao:	void EscreveFraseRomLCD(const rom char *buffer)
 * Entrada:	*buffer: apontador para string na memoria de programa(ROM)
 * Sa�da:	Nenhuma (void)
 * Descri��o: 	Essa rotina copia uma string terminada com caracter nulo
 *		da memoria de programa do microcontrolador para o display de LCD.
 *		A string apontada por *buffer � copiada no display a partir da
 *		posi��o de memoria atual do cursor ou da posi��o de mem�ria escolhida
 *		com as fun��es PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveFraseRomLCD(const rom char *buffer)
{
	while(*buffer)                  // escreve dados no LCD ate achar caracter nulo
	{
	        EscreveCaractereLCD(*buffer); // escreve caracter no LCD
	        buffer++;               // incrementa apontador
	}
}
