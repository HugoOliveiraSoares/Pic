/******************************************************************************
 *
 *           SEMPRA Bibliotecas (PIC32MX775F512L)- tecladoPS2
 *
 ******************************************************************************
 * Nome do Arquivo:     tecladoPS2.h
 * Dependencias:    	Veja seção INCLUDES
 * Processador:       	PIC32MX775F512L
 * Opção de Clock:      HS 8MHz (externo) - CPU: 80MHz
 *                      Barramento de Periférico (PBU) = 80MHz (interno)
 * Compilador:        	C32
 * Empresa:         	SEMPRA
 *
 * Plataforma:		KIT E-P32 SEMPRA V1.01
 *
 * Autor:		Bruno Silveira Avelar
 *			James Hamilton Oliveira Junior
 *
 * Data:		v1 - 01/Fev/2011 - Bruno Silveira Avelar
 *                      v2 - 04/Set/2012 - Bruno Silveira Avelar
 *
 * Descrição:		Biblioteca desenvolvida para trabalhar com teclado
 *			de computador (PS/2) no PIC.
 *
 * 			H A R D W A R E:
 *
 *  			Conector Femea:		Pinos | Porta | Função
 *                                        1      RA15    Teclado Data
 *      	6 [] 5			  2      RA15	 MOUSE Data
 *             4      3                   3       - 	 GND
 *                                        4       -	 VCC
 *            	 2  1                     5      RA10	 Telcado Clock
 *                                        6      RA10	 MOUSE Clock
 *
 *		F I R M W A R E:
 *
 *		Estados do barramentos:
 *
 *		Data 5V, Clock 5V - Idle
 *		Data 5V, Clock 0V - Impede comunicação
 *		Data 0V, Clock 5V - PIC ñ requisita envio de dados
 *
 *		Comunicação Telcado -> PIC
 *
 *		1 start bit.  Sempre 0 (Pode ser usado para ativar interrupção).
 *		8 data bits, Menos significante primeiro.
 *		1 bit de paridade (paridade ímpar
 *		1 stop bit.  Sempre 1.
 *
 *              O responsável por gerar o clock é o teclado.
 *
 * Notas:
 *		- A função char LeDadoTeclado() pode ser chamada como pulling ou
 *		ser chamada em uma SRF. A configuração da interrupção e a
 *              rotina de tratamento devem ser feitas pelo usuário em seu
 *              programa.
 *
 *****************************************************************************/
/*****************************************************************************
 * Log de modificações:
 * 29/02/2012   -   Adaptação para plataforma E-P32
 * 04/09/2012   -   Melhoria do algoritimo de leitura do telcaodo
 *
******************************************************************************/
#include "tecladoPS2.h"

 unsigned char LeDadoTeclado()
 {
	char dadoRecebido = 0;  //Variavel que irá receber os bits da comunicação
                            //e ao final terá o valor recebido pelo teclado.
	unsigned char i;
        unsigned char timeOut; //Variavel para contagem de tentativas de
                               //recebimento de um bit. Essa variavel é usada
                               //para impedir que o microcontrolador fique
                               //em um laço infinito caso nao receba o numero
                               //correto de bits.

	char paridadeBit = 0,paridadeByte = 0; // Variaveis para o cálculo de
                                               // paridade da comunicação.

	DATAPIN_CONFIG  = 1;    // Configura o pino de dados como entrada digital
	CLOCKPIN_CONFIG = 1;    // Configura o pino de clock como entrada digital
		
	// Quando esta função é chamada, o início do start bit já aconteceu.
        //(Entrou no if do pulling ou gerou a interrupção por borda de descida)
        // O pino de clock está em 0. Devemos esperar o termino do start bit
        // com o pino de clock indo para 1 para então receber os dados enviados.
        // Caso a borda de subida do clock nao aconteça em 1,275ms a função
        // retornará TIMEOUT_ERRO.

	for(i = 0; i<8; i++)
	{
		timeOut = 0;
                // Espera a subida do clock com timeout
		while(PS2_CLOCKPIN==1 && timeOut<255 )
		{
			Delay5Micro();
			timeOut++;
		}
                // Verifica se houve um timeOut. Caso tenha acontecido retorna
                // o erro TIMEOUT_ERRO.
		if(timeOut == 255)
		{
                    // Impede que seja pego o código da tecla quando ela é solta
			Delay25Micro();   
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
//			INTCONbits.INT0IE = 1;// Habilita a interrupção do barramento de dados
                        return TIMEOUT_ERRO;
		}	

               // Houve a subida do clock indicando o final do start bit.
               // Os proximos 8 bits serão o dado. Precisamos recebe-los lendo o pino
               // de dados na transição de descida do pino de clock e armazena-los
               // na variavel dadoRecebido.

               timeOut = 0;

               //Aguarda a borda de descida

               while(timeOut<200  && PS2_CLOCKPIN==0)
               {
                       Delay5Micro();
                       timeOut++;

               }

		if(timeOut == 255)
		{

			Delay25Micro();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
	//		INTCONbits.INT0IE = 1;// Habilita a interrupção do barramento de dados
			return TIMEOUT_ERRO;
		}
               // Houve a borda de descida indicando que é preciso fazer a
               // leitura de um novo bit no barramento de dados.

		Delay25Micro(); 		// Delay para evitar ruidos da transição
		dadoRecebido += PS2_DATAPIN << i; // Leitura do bit
	}
	//Os 8 bits de dados foram recebidos. O proximo bit enviado é o bit de
        //paridade. Devemos esperar o clock ir para 1 para na descida do clock
        //lermos o bit de paridade.

        timeOut = 0;
	//Aguarda o clock
        while(PS2_CLOCKPIN==1  && timeOut<255) // Espera a subida do clock com timeout
	{
		Delay5Micro();
		timeOut++;
	}
	if(timeOut == 255)
	{
			Delay25Micro();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
	//	INTCONbits.INT0IE = 1;// Habilita a interrupção do barramento de dados
		return TIMEOUT_ERRO;
	}	
	
	paridadeBit = PS2_DATAPIN; // Leitura do bit de paridade
        
        //O dado foi recebido assim como sua paridade.
        //Para receber o proximo dado precisamos receber o bit de stop.
        //Aguarda o STOPbit

         while(PS2_CLOCKPIN==0  && timeOut<255) // Espera a subida do clock com timeout
	{
		Delay5Micro();
		timeOut++;
	}
	if(timeOut == 255)
	{
			Delay25Micro();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
			Delay25Micro();
	//	INTCONbits.INT0IE = 1;// Habilita a interrupção do barramento de dados
		return TIMEOUT_ERRO;
	}

	// Cálculo de paridade do byte recebido
	for(i =0; i<8; i++)
	{
		if(dadoRecebido && (0x00000001 <<i))
		{
			paridadeByte++;
		}	
	}	
	paridadeByte = paridadeByte %2;

        if(paridadeBit != paridadeByte)
        {
            return PARIDADE_ERRO;
        }
		
        //Dado recebido com sucesso.
        // Converte o dado recebido para ASCII e envia como retorno da função
	switch(dadoRecebido)  
	{
		case 0x1C:
			return('a');
		break;
		case 0x32:
			return('b');
		break;
		case 0x21:
			return('c');
		break;
		case 0x23:
			return('d');
		break;
		case 0x24:
			return('e');
		break;
		case 0x2B:
			return('f');
		break;
		case 0x34:
			return('g');
		break;
		case 0x33:
			return('h');
		break;
		case 0x43:
			return('i');
		break;
		case 0x3B:
			return('j');
		break;
		case 0x42:
			return('k');
		break;
		case 0x4B:
			return('l');
		break;
		case 0x3A:
			return('m');
		break;
		case 0x31:
			return('n');
		break;
		case 0x44:
			return('o');
		break;
		case 0x4D:
			return('p');
		break;
		case 0x15:
			return('q');
		break;
		case 0x2D:
			return('r');
		break;
		case 0x1B:
			return('s');
		break;
		case 0x2C:
			return('t');
		break;
		case 0x3C:
			return('u');
		break;
		case 0x2A:
			return('v');
		break;
		case 0x1D:
			return('w');
		break;
		case 0x22:
			return('x');
		break;
		case 0x35:
			return('y');
		break;
		case 0x1A:
			return('z');
		break;
		case 0x45:
			return('0');
		break;
		case 0x16:
			return('1');
		break;
		case 0x1E:
			return('2');
		break;
		case 0x26:
			return('3');
		break;
		case 0x25:
			return('4');
		break;
		case 0x2E:
			return('5');
		break;
		case 0x36:
			return('6');
		break;
		case 0x3D:
			return('7');
		break;
		case 0x3E:
			return('8');
		break;
		case 0x46:
			return('9');
		break;
		case 0x4E:
			return('-');
		break;
		case 0x55:
			return('=');
		break;
		case 0x5B:
			return(']');
		break;
		case 0x54:
			return('[');
		break;
		case 0x4C:
			return(';');
		break;																																																
		case 0x29:
			return(' ');
		break;
		
		
		case 0x5A: // ENTER
			return(0x0D);
		case 0x66: // Backspace
			return(0x08);
		break;
		//Despressionar

		case 0xF0:
		
			return (0x01);
		break;
		case 0xE0:
		
			return (0x01);
		break;
		default:
	
			return (0x01);
		
	}	
}	



 