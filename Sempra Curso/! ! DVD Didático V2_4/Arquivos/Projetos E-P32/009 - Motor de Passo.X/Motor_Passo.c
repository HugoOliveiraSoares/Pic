/******************************************************************************
 *
 *            Curso PICMINAS de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Motor_Passo.c
 * Dependencias:    	Veja se��o INCLUDES
 * Processador:       	
 * Op��o de Clock:	
 * Compilador:        	
 *
 * Plataforma:		
 *
 * Autor:		James Hamilton Oliveira Junior
 *                      Carla Caldeira Takahshi
 * Data:		24/Fev/2012
 *
 * Descri��o:        	Biblioteca de fun��es para controle de um motor de passo
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
//                      					V A R I � V E I S
//
//
/*****************************************************************************/

unsigned char Pos_Motor;	//Vari�vel que armazena a posi��o do eixo do motor

/*****************************************************************************/
//
//								F U N � � E S
//
//
/*****************************************************************************/

/******************************************************************************
 * Funcao:      void PositionMotor (void)
 * Entrada:     unsigned char Tempo: tempo a ser gasto entra cada passo
 *
 * Sa�da:       Nenhuma (void)
 * Descri��o:   Posiciona o motor de passo executando uma rota��o completa 
 *		a partir do zero, dessa forma, o eixo do motor que estava
 *		em uma posi��o desconhecida � colocado na posi�ao '0001'
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
 * Entrada: unsigned int Passos: N�mero de passos que o motor deve rotacionar:
 *				 (0 at� 65536)
 *				 A dire��o de rota��o � determinada pelo sinal
 *				 do numero de passos. Positivo em um sentido
 *				 negativo no sentido oposto
 *				
 *          unsigned char Tempo: Tempo de delay entre cada passo:
 *				 (0 at� 255)
 *											
 * Sa�da:   Nenhuma (void)
 * 
 * Descri��o:   Controla o numero de passos, a dire��o e o tempo da rota��o do motor
 *
 *****************************************************************************/
 void RotateMotor (int Passos, unsigned char Tempo,unsigned char tempoPosicao)
 {
     int Passos_Restantes =0;
     unsigned char Position = 0;			//posicao atual do motor
 //---------------------------------------------------------------------------------------------
  
  	while (Passos != 0) 				//repete at� executar todos os passos			
 	{	
 		DelayMsx(Tempo);			//Atraso entre os passos enviados para o motor
 		
 		//-----------------------------------------------------------------------------------------
 		if (Passos > 0)					//determina o sentido de rota��o: sentido positivo
 		{
 			Pos_Motor = Pos_Motor<<1; 						//caminha com o bit 1 pela vari�vel para esquerda
 			if (Pos_Motor == 0b10000){Pos_Motor = 0b0001;}
  			Position = Pos_Motor;
  			Passos_Restantes = Passos--;							//decresce o numero de passos
 		}
 		//-----------------------------------------------------------------------------------------	
 		if (Passos < 0)					//determina o sentido de rota��o: sentido negativo
 		{
 			Pos_Motor = Pos_Motor>>1;							//caminha com o bit 1 pela vari�vel para direita
 			if (Pos_Motor == 0){Pos_Motor = 0b1000;}
 			Position = Pos_Motor;
 			Passos_Restantes = Passos++;
 		}
 		//-----------------------------------------------------------------------------------------
 		switch(Position)					//determina a pr�xima posi��o do motor
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
 }//fim fun��o
 
/******************************************************************************
 * Funcao:        	void Travar_Motor (void)
 *											
 * Entrada:         Nenhuma (void)									
 * Sa�da:          	Nenhuma (void)
 * 
 * Descri��o:       Fixa o motor em uma posi��o constante, setando o bit de posi��o
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
 }//fim fun��o
 
 /******************************************************************************
 * Funcao:        	void Destravar_Motor (void)
 *											
 * Entrada:         Nenhuma (void)									
 * Sa�da:          	Nenhuma (void)
 * 
 * Descri��o:       Destrava o motor, resetando todos os bits
 *
 *****************************************************************************/
 void Destravar_Motor (void)
 {
 		STP1 = 1;
  	
		STP2 = 1;

 		STP3 = 1;
 
		STP4 = 1;
		
 }//fim fun��o
 
 /******************************************************************************
 * Funcao:        	void Inicializa_Motor (void)
 *											
 * Entrada:         Nenhuma (void)									
 * Sa�da:          	Nenhuma (void)
 * 
 * Descri��o:       Coloca todos os pinos do motor em zero e configura as portas
 *					como outputs
 *
 *****************************************************************************/
 void InitMotor (void)
 {
 		STP1 = 1;	//Todos os pinos do motor ficam em zero
		STP2 = 1;
		STP3 = 1;
		STP4 = 1;
 
 }//fim fun��o
 
 
 /*******************************************************************************/
 //							F I M       A R Q U I V O
 /*******************************************************************************/