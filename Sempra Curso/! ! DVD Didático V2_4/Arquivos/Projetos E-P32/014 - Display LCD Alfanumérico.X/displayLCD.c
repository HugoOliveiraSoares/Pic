/******************************************************************************
 *
 *           SEMPRA Bibliotecas (PIC32MX775F512L) - Display de LCD Alfanumerico
 *
 ******************************************************************************
 * Nome do Arquivo:     displayLCD.c
 * Dependencias:    	Veja seção INCLUDES
 * Processador:       	PIC32MX775F512L
 * Opção de Clock:      HS 8MHz (externo) - CPU: 80MHz
 * Compilador:        	C18 v3.20 ou superior
 * Empresa:         	SEMPRA
 *
 * Plataforma:		kit SEMPRA E-P32
 *
 * Autor:				M.Sc. Henrique Resende Martins
 * 						Mauricio Ferrari Santos Corrêa
 *						Bruno Silveira Avelar
 *						James Hamilton Oliveira Junior
 *
 *****************************************************************************/


/** I N C L U D E S **********************************************************/
#include "displayLCD.h"


/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:		void ConfiguraLCD(void)
 * Entrada:		Nenhuma (void)
 * Saída:		Nenhuma (void)
 * Descrição: 	Configura portas do PIC 18F4550 que estão conectadas ao 
 *				display LCD como saida. Essa rotina é baseada no controlador 
 *				de LCD Hitachi HD44780. Configura os parametros de comunicação
 *				com o display, tais como:
 *					- modo de operação (4 ou 8 data bits)
 *					- tipo de cursor
 *					- tamanho da fonte
 *				Ao final da configuração limpa o display.
 *****************************************************************************/
void ConfiguraLCD(void)
{

	//Configura os pinos como coletores abertos.
	OPEN_COLECTOR_A;
	OPEN_COLECTOR_G;
	
	// Configura os pinos de controle (RW,RS,E) como saída.
	//TRIS_RW = 0;
	TRIS_RS = 0;
	TRIS_E = 0;

	// Configura os pinos de dados (D4,D5,D6,D7) como saída.
	TRIS_D4=0;
	TRIS_D5=0;
	TRIS_D6=0;
	TRIS_D7=0;

// Inicio da rotina de inicialização do display LCD
// Aguardar tempos e enviar 3 vezes o comando 0b0011XXXX como descrito no datasheet
// do controlador HD44780 ou SPLC780D

	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1
	//RW_PIN = 0;
	//selecioan pinos de dados com comando de inicialização 0b0011 no Nibble-High
	//(os 4 bits de dados mais significativos), os bits do Nibble-Low são Don't Care 
	D7=0;
	D6=0;
	D5=1;
	D4=1;

//Passo 1: Envio do comando de inicialização 0b0011

	// Delay inicial de 15ms após alimentar o LCD: Vdd > 4,5V
	DELAY_5ms();
	DELAY_5ms();
	DELAY_5ms();

	//Habilita leitura do comando pelo LCD, através do pino de enable, para tanto,
	//um pulso de 1ms com borda de descida é efetuado
	E_PIN = 1;      			
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 2: Envio do comando de inicialização 0b0011

	// Delay de pelo menos 4.1ms
	DELAY_5ms();

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;      			
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 3: Envio do comando de inicialização 0b0011

	// Delay de pelo menos 100us
	DELAY_5ms();

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;      			
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 4: Envio da Configuração 0b0010 no Nibble-High
	D7=0;
	D6=0;
	D5=1;
	D4=0;


	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;      			
    DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();


//Envio dos comandos de Configuração do LCD
	EscreveComandoLCD(0b00101000);	// Function Set: 4bit interface, 2 lines, Font 5x7  
	EscreveComandoLCD(0b00000110);	// Entry mode set: Increment, Shift OFF
	EscreveComandoLCD(0b00001110);	// Display Control: Display ON, Cursor ON, Blink OFF
	EscreveComandoLCD(0b00000001);	// Clear display
}

/******************************************************************************
 * Funcao:		void EscreveComandoLCD(unsigned char cmd)
 * Entrada:		cmd: comando que será enviado para o LCD
 * Saída:		Nenhuma (void)
 * Descrição: 	(Write a command to the LCD)
 *				Escreve um comando para o display de LCD.
 *****************************************************************************/
void EscreveComandoLCD(unsigned char cmd)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1
	//RW_PIN = 0;
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
 * Funcao:		void EnderecoCursor(unsigned char endereco)
 * Entrada:		endereco: endereço da memoria de dados do display que se deseja apontar
 * Saída:		Nenhuma (void)
 * Descrição: 	(Set the Display Data RAM Address)
 *				Essa rotina seta o endereço da memoria RAM de dados do 
 *				display LCD para o endereço	que se deseja escrever um caracter
 *				usando as funções EscreveCaractereLCD() e EscreveInteiroLCD().
 *****************************************************************************/
void EnderecoCursor(unsigned char endereco)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1
 	//RW_PIN = 0;
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
 * Funcao:		void PosicaoCursorLCD(unsigned char endereco)
 * Entrada:		Número da linha e da coluna em que se desja escrever o caracter 
 * Saída:		Nenhuma (void)
 * Descrição: 	(Set the Display Data RAM Address)
 *				Essa rotina posiciona o cursor do display de LCD para a linha
 *				e coluna em que se deseja escrever um caracter usando as funções
 *				EscreveCaractereLCD() e EscreveInteiroLCD().
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
 * Funcao:		void EscreveCaractereLCD(unsigned char data)
 * Entrada:		data: Byte de dados para ser escrito na memoria RAM do LCD
 * Saída:		Nenhuma (void)
 * Descrição: 	(Write a Data byte to the LCD)
 *				Essa rotina escreve o byte de caracteres no display a partir da
 *				posição de memoria atual do cursor ou da posição de memória
 *				escolhida com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveCaractereLCD(char cmd)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 1;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1
//	RW_PIN = 0;
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
 * Funcao:		void EscreveInteiroLCD(int valor)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) a ser escrito no
 *				display.
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina escreve o numero inteiro no display a partir da posição
 *				de memoria atual do cursor ou da posição de memória escolhida com as
 *				funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveInteiroLCD(int valor)
{
	char *texto;
	
	texto = itoa(valor);
	EscreveFraseRamLCD(texto);
} 
/******************************************************************************
 * Funcao:		void EscreveFloatLCD(float valor, char formatacao)
 * Entrada:		valor: float com sinal a ser escrito no	display.
 *				formataçao: numero de casas decimais desejadas (0 a 4 casas decimais)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina escreve o numero float no display a partir da posição
 *				de memoria atual do cursor ou da posição de memória escolhida com as
 *				funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveFloatLCD(float valor, char formatacao)

{
	char ponto = '.';
	char i;
	int casasDecimais = 1;
	
	if(formatacao == 0)
	{
		EscreveInteiroLCD((int)valor);
	}
	else
	{
		EscreveInteiroLCD(valor);
		EscreveCaractereLCD(ponto);
		for (i = 0; i<formatacao; i++)
		{
			casasDecimais *= 10;
		}	
		EscreveInteiroLCD(((int)(valor * casasDecimais) % casasDecimais));
	}		
}	 
/******************************************************************************
 * Funcao:		void EscreveFraseRamLCD(char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de dados(RAM)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina copia uma string terminada com caracter nulo
 *				da memoria de dados do microcontrolador para o display de LCD.
 *				A string apontada por *buffer é copiada no display a partir da
 *				posição de memoria atual do cursor ou da posição de memória
 *				escolhida com as funções PosicaoCursorLCD() ou EnderecoCursor().
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
 * Funcao:		void EscreveFraseRomLCD(const rom char *buffer)
 * Entrada:		*buffer: apontador para string na memoria de programa(ROM)
 * Saída:		Nenhuma (void)
 * Descrição: 	Essa rotina copia uma string terminada com caracter nulo
 *				da memoria de programa do microcontrolador para o display de LCD.
 *				A string apontada por *buffer é copiada no display a partir da
 *				posição de memoria atual do cursor ou da posição de memória escolhida
 *				com as funções PosicaoCursorLCD() ou EnderecoCursor().
 *****************************************************************************/
void EscreveFraseConstLCD(const char *buffer)
{
	while(*buffer)                  // escreve dados no LCD ate achar caracter nulo
	{
	        EscreveCaractereLCD(*buffer); // escreve caracter no LCD
	        buffer++;               // incrementa apontador
	}
}
/******************************************************************************
 * Funcao:		char * itoa(int value)
 * Entrada:		valor: inteiro com sinal (de -32768 a 32767) 
 * Saída:		char * ponteiro para um string
 * Descrição: 	Esta função converte numeros inteiros positivos e negativos
 *				para strings.
 *****************************************************************************/
char *itoa(int value) 
{
     static char buffer[12];        // 12 bytes é o suficiente para o int32
     int original = value;          // salva o valor original
 
     int c = sizeof(buffer)-1;		
 
     buffer[c] = 0;                 // Escreve 0 (null) no ultimo byte de buffer
 
     if (value < 0)                 // Se for negativo pegar o valor absoluto
         value = -value;
     
     do                             //Escreve o digito menos significante do valor no buffer
     {
         buffer[--c] = (value % 10) + '0';    
         value /= 10;
     } while (value);
 
     if (original < 0) 
         buffer[--c] = '-'; // coloca o sinal de negativo
 
     return &buffer[c];
 }
 