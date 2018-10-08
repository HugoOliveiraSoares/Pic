/******************************************************************************
 *
 *            Curso PICMINAS de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Motor_Passo.h
 * Dependencias:    	Veja se��o INCLUDES
 * Processador:       	PIC32MX775F512L
 * Op��o de Clock:	HS 8MHz (externo) - CPU: 80MHz
 * Compilador:        	C32
 *
 * Plataforma:		PICMinas32
 *
 * Autor:		James Hamilton Oliveira Junior
 *                      Carla Caldeira Takahshi
 * Data:		24/Fev/2012
 *	
 *
 * Descri��o:        	Biblioteca de fun��es para controle de um motor de passo
 *			monopolar (5 fios) com o Kit PICMINAS 32.
 *
 *					
 *****************************************************************************/

/*****************************************************************************/
//
//								I N C L U D E S
//
//
/*****************************************************************************/

#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.
#include <Delays.h>		//biblioteca padr�o de atrasos
#include <HardwareProfile.h>    //Biblioteca de defini��o do Hardware

						
/*****************************************************************************/
//
//							P R O T � T I P O S
//
//
/*****************************************************************************/						

/******************************************************************************
 * Funcao:        void PositionMotor (void)
 * Entrada:       unsigned char Tempo: tempo a ser gasto entra cada passo
 *
 * Sa�da:         Nenhuma (void)
 * Descri��o:     Posiciona o motor de passo executando uma rota��o completa 
 *                a partir do zero, dessa forma, o eixo do motor que estava
 *                 em uma posi��o desconhecida � colocado na posi�ao '0001'
 *
 *****************************************************************************/
 extern void PositionMotor (unsigned char Tempo);

/******************************************************************************
 * Funcao:      void RotateMotor (unsigned int Passos, unsigned char Tempo)
 *											
 * Entrada:     unsigned int Passos:    N�mero de passos que o motor deve rotacionar:
 *                                  (0 at� 65536)
 *                                  A dire��o de rota��o � determinada pelo sinal
 *                                  do numero de passos. Positivo em um sentido
 *                                  negativo no sentido oposto
 *													
 *              unsigned char Tempo:    Tempo de delay entre cada passo:
 *                                  (0 at� 255)
 *											
 * Sa�da:       Nenhuma (void)
 * 
 * Descri��o:   Controla o numero de passos, a dire��o e o tempo da rota��o do motor
 *
 *****************************************************************************/
 extern void RotateMotor (int Passos, unsigned char Tempo, unsigned char tempoPosicao);
 
/******************************************************************************
 * Funcao:      void LockMotor (void)
 *											
 * Entrada:     Nenhuma (void)									
 * Sa�da:       Nenhuma (void)
 * 
 * Descri��o:   Fixa o motor em uma posi��o constante, setando o bit de posi��o
 *
 *****************************************************************************/
 extern void LockMotor (void);
 
 /******************************************************************************
 * Funcao:      void UnlockMotor (void)
 *											
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * 
 * Descri��o:   Destrava o motor, resetando todos os bits
 *
 *****************************************************************************/
 extern void UnlockMotor (void);
 
 /******************************************************************************
 * Funcao:      void InitMotor (void)
 *											
 * Entrada:     Nenhuma (void)
 * Sa�da:       Nenhuma (void)
 * 
 * Descri��o:   Coloca todos os pinos do motor em zero e configura as portas
 *					como outputs
 *
 *****************************************************************************/
 extern void InitMotor (void);
 
 /****************************************************************************/
 //							F I M       A R Q U I V O
 /****************************************************************************/