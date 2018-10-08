/******************************************************************************
 *
 *            Curso PICMINAS de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Motor_Passo.c
 * Dependencias:    	Veja seção INCLUDES
 * Processador:       	
 * Opção de Clock:	
 * Compilador:        	
 *
 * Plataforma:		
 *
 * Autor:		James Hamilton Oliveira Junior
 *                      Carla Caldeira Takahshi
 * Data:		24/Fev/2012
 *
 * Descrição:        	Biblioteca de funções para controle de um motor de passo
 *			monopolar (5 fios) com o Kit PICMINAS32.
 *
 *					
 *****************************************************************************/

/*****************************************************************************/
//
//								I N C L U D E S
//
//
/*****************************************************************************/
#include "Motor_Passo.h"
					 

/*****************************************************************************/
//
//                      					V A R I Á V E I S
//
//
/*****************************************************************************/

unsigned char Pos_Motor;	//Variável que armazena a posição do eixo do motor

/*****************************************************************************/
//
//								F U N Ç Õ E S
//
//
/*****************************************************************************/

/******************************************************************************
 * Funcao:      void PositionMotor (void)
 * Entrada:     unsigned char Tempo: tempo a ser gasto entra cada passo
 *
 * Saída:       Nenhuma (void)
 * Descrição:   Posiciona o motor de passo executando uma rotação completa 
 *		a partir do zero, dessa forma, o eixo do motor que estava
 *		em uma posição desconhecida é colocado na posiçao '0001'
 *
 *****************************************************************************/
 void Position_Motor (unsigned char Tempo)
 {
 	Pos_Motor = 0b0001;
 	RotateMotor(4, Tempo,20);
 }
 
/******************************************************************************
 * Funcao:  void RotateMotor (unsigned int Passos, unsigned char Tempo)
 *											
 * Entrada: unsigned int Passos: Número de passos que o motor deve rotacionar:
 *				 (0 até 65536)
 *				 A direção de rotação é determinada pelo sinal
 *				 do numero de passos. Positivo em um sentido
 *				 negativo no sentido oposto
 *				
 *          unsigned char Tempo: Tempo de delay entre cada passo:
 *				 (0 até 255)
 *											
 * Saída:   Nenhuma (void)
 * 
 * Descrição:   Controla o numero de passos, a direção e o tempo da rotação do motor
 *
 *****************************************************************************/
 void RotateMotor (int Passos, unsigned char Tempo,unsigned char tempoPosicao)
 {
     int Passos_Restantes =0;
     unsigned char Position = 0;			//posicao atual do motor
 //---------------------------------------------------------------------------------------------
  
  	while (Passos != 0) 				//repete até executar todos os passos			
 	{	
 		DelayMsx(Tempo);			//Atraso entre os passos enviados para o motor
 		
 		//-----------------------------------------------------------------------------------------
 		if (Passos > 0)					//determina o sentido de rotação: sentido positivo
 		{
 			Pos_Motor = Pos_Motor<<1; 						//caminha com o bit 1 pela variável para esquerda
 			if (Pos_Motor == 0b10000){Pos_Motor = 0b0001;}
  			Position = Pos_Motor;
  			Passos_Restantes = Passos--;							//decresce o numero de passos
 		}
 		//-----------------------------------------------------------------------------------------	
 		if (Passos < 0)					//determina o sentido de rotação: sentido negativo
 		{
 			Pos_Motor = Pos_Motor>>1;							//caminha com o bit 1 pela variável para direita
 			if (Pos_Motor == 0){Pos_Motor = 0b1000;}
 			Position = Pos_Motor;
 			Passos_Restantes = Passos++;
 		}
 		//-----------------------------------------------------------------------------------------
 		switch(Position)					//determina a próxima posição do motor
 		{
 			case (0b0001):
 				STP1 = 0;
 				STP2 = 0;
 				DelayMsx(tempoPosicao);
 				STP1 = 1;
 				STP2 = 1;
  			break;
 		  	//-------------------------------------------------------------------------------------
 			case (0b0010):
 				STP2 = 0;
 				STP3 = 0;
 				DelayMsx(tempoPosicao);
 				STP2 = 1;
 				STP3 = 1;
 			break;
 		    //-------------------------------------------------------------------------------------
 			case (0b0100):
 				STP3 = 0;
 				STP4 = 0;
 				DelayMsx(tempoPosicao);
 				STP3 = 1;
 				STP4 = 1;
 			break;
 		    //-------------------------------------------------------------------------------------
 			case (0b1000):
 				STP4 = 0;
 				STP1 = 0;
 				DelayMsx(tempoPosicao);
 				STP4 = 1;
 				STP1 = 1;
 			break;
 			
 			default:
 			break;
 		}//fim switch
 	}//fim while
 }//fim função
 
/******************************************************************************
 * Funcao:        	void Travar_Motor (void)
 *											
 * Entrada:         Nenhuma (void)									
 * Saída:          	Nenhuma (void)
 * 
 * Descrição:       Fixa o motor em uma posição constante, setando o bit de posição
 *
 *****************************************************************************/
 void Travar_Motor (void)
 {
 	switch(Pos_Motor)
 	{
 		case (0b0001): STP1 = 0;
  		break;

 		case (0b0010): STP2 = 0;
 		break;

 		case (0b0100): STP3 = 0;
 		break;

		case (0b1000): STP4 = 0;
		break;
 			
		default:
		break;
 	}//fim switch
 }//fim função
 
 /******************************************************************************
 * Funcao:        	void Destravar_Motor (void)
 *											
 * Entrada:         Nenhuma (void)									
 * Saída:          	Nenhuma (void)
 * 
 * Descrição:       Destrava o motor, resetando todos os bits
 *
 *****************************************************************************/
 void Destravar_Motor (void)
 {
 		STP1 = 1;
  	
		STP2 = 1;

 		STP3 = 1;
 
		STP4 = 1;
		
 }//fim função
 
 /******************************************************************************
 * Funcao:        	void Inicializa_Motor (void)
 *											
 * Entrada:         Nenhuma (void)									
 * Saída:          	Nenhuma (void)
 * 
 * Descrição:       Coloca todos os pinos do motor em zero e configura as portas
 *					como outputs
 *
 *****************************************************************************/
 void InitMotor (void)
 {
 		STP1 = 1;	//Todos os pinos do motor ficam em zero
		STP2 = 1;
		STP3 = 1;
		STP4 = 1;
 
 }//fim função
 
 
 /*******************************************************************************/
 //							F I M       A R Q U I V O
 /*******************************************************************************/