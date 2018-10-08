/******************************************************************************
 *
 *            Curso PICMINAS de Microcontroladores (PIC18F4550)
 *
 ******************************************************************************
 * Nome do Arquivo:     Motor_Passo.h
 * Dependencias:    	Veja seção INCLUDES
 * Processador:       	PIC32MX775F512L
 * Opção de Clock:	HS 8MHz (externo) - CPU: 80MHz
 * Compilador:        	C32
 *
 * Plataforma:		PICMinas32
 *
 * Autor:		James Hamilton Oliveira Junior
 *                      Carla Caldeira Takahshi
 * Data:		24/Fev/2012
 *	
 *
 * Descrição:        	Biblioteca de funções para controle de um motor de passo
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

#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include <Delays.h>		//biblioteca padrão de atrasos
#include <HardwareProfile.h>    //Biblioteca de definição do Hardware

						
/*****************************************************************************/
//
//							P R O T Ó T I P O S
//
//
/*****************************************************************************/						

/******************************************************************************
 * Funcao:        void PositionMotor (void)
 * Entrada:       unsigned char Tempo: tempo a ser gasto entra cada passo
 *
 * Saída:         Nenhuma (void)
 * Descrição:     Posiciona o motor de passo executando uma rotação completa 
 *                a partir do zero, dessa forma, o eixo do motor que estava
 *                 em uma posição desconhecida é colocado na posiçao '0001'
 *
 *****************************************************************************/
 extern void PositionMotor (unsigned char Tempo);

/******************************************************************************
 * Funcao:      void RotateMotor (unsigned int Passos, unsigned char Tempo)
 *											
 * Entrada:     unsigned int Passos:    Número de passos que o motor deve rotacionar:
 *                                  (0 até 65536)
 *                                  A direção de rotação é determinada pelo sinal
 *                                  do numero de passos. Positivo em um sentido
 *                                  negativo no sentido oposto
 *													
 *              unsigned char Tempo:    Tempo de delay entre cada passo:
 *                                  (0 até 255)
 *											
 * Saída:       Nenhuma (void)
 * 
 * Descrição:   Controla o numero de passos, a direção e o tempo da rotação do motor
 *
 *****************************************************************************/
 extern void RotateMotor (int Passos, unsigned char Tempo, unsigned char tempoPosicao);
 
/******************************************************************************
 * Funcao:      void LockMotor (void)
 *											
 * Entrada:     Nenhuma (void)									
 * Saída:       Nenhuma (void)
 * 
 * Descrição:   Fixa o motor em uma posição constante, setando o bit de posição
 *
 *****************************************************************************/
 extern void LockMotor (void);
 
 /******************************************************************************
 * Funcao:      void UnlockMotor (void)
 *											
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * 
 * Descrição:   Destrava o motor, resetando todos os bits
 *
 *****************************************************************************/
 extern void UnlockMotor (void);
 
 /******************************************************************************
 * Funcao:      void InitMotor (void)
 *											
 * Entrada:     Nenhuma (void)
 * Saída:       Nenhuma (void)
 * 
 * Descrição:   Coloca todos os pinos do motor em zero e configura as portas
 *					como outputs
 *
 *****************************************************************************/
 extern void InitMotor (void);
 
 /****************************************************************************/
 //							F I M       A R Q U I V O
 /****************************************************************************/