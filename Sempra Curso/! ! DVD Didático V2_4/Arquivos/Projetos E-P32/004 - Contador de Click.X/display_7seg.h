/******************************************************************************
 *
 * 				  Biblioteca PICMINAS (PIC32MX775F256L)
 *
 ******************************************************************************
 * Nome do Arquivo:     display_7seg.h
 * Dependencias:    	
 * Processador:       	PIC32MX775F256L
 * Opção de Clock:		HS 10MHz (externo) - CPU: 80MHz	
 * Compilador:        	C32
 * Empresa:         	PICMINAS
 *
 * Plataforma:			Placa de desenvolvimento PICMinas32 v1.0
 * 
 * Autor:				Bruno Silveira Avelar
 *
 * Data:				v1 - 21/Fev/2010
 *
 * Descrição:        	Biblioteca de funções para escrever no display multiplexado
 *						de 7 segmentos da placa de desenvolvimento PICMinas32.
 *						Os  4 displays são do tipo CATODO COMUM e seus segmentos 
 *						são LIGADOS com nivel lógico 1.
 *						O display apresenta 4 digitos e seus respectivos
 *						pontos decimais. 
 *						Nesta biblioteca usa-se os rótulos:
 *						D - digito
 *						p - ponto decimal do digito
 *
 *						Nomes usados para os segmentos do displays presentes
 *						na placa de desenvolvimento PICMINAS32:
 * 
 *					  	  Display 4		Display 3		Display 2		Display 1 			   
 *					       (B3)			   (B2) 		   (B1)			   (B0)

 *						  ---a---  	 	 ---a--- 		 ---a--- 		 ---a--- 
 *						 |       |		|       |		|       |		|       | 
 *						 f       b		f       b		f       b		f       b	
 *						 |       |		|       |		|       |		|       |	
 *						  ---g---		 ---g--- 		 ---g--- 		 ---g--- 
 *						 |       |		|       |		|       |		|       |			
 *						 e       c		e       c		e       c		e       c		
 *						 |       |		|       |		|       |		|       |			
 *						  ---d--- .p	 ---d--- .p		 ---d--- .p		 ---d--- .p		
 *
 *						A multiplexação é feita pela função uptate() que coloca cada
 *						valor em seu respectivo dígito enquanto os outros estão apagados.
 *					 	Os displays sao numerados da esquerda para direita.
 *
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include "HardwareProfile.h"


/** P R O T O T I P O S *******************************************************/

/******************************************************************************
 * Funcao:        	void ConfigDisplay7Seg (void)
 * Entrada:         Nenhuma (void)
 * Saída:          	Nenhuma (void)
 * Descrição:       Configura portas do que estão conectadas ao 
 *					displays de 7 segmentos como saida. 
 *					Desliga todos os segmentos do display apos a configuração
 *
 *****************************************************************************/
 extern void ConfigDisplay7Seg(void);

/******************************************************************************
 * Funcao:        	void EscreveDisplay7Seg(unsigned int numero, unsigned char ponto)
 * 
 * Entrada:         int caracter: valor decimal de 0 a 9999 a ser apresentado no display
 *					char ponto: liga o ponto decimal e a posição do ponto
 *							0b00000000  	:desliga ponto decimal
 *							0b00000001		:liga ponto decimal do diplay 1
 *							0b00000010  	:liga ponto decimal do diplay 2
 *							0b00000100		:liga ponto decimal do diplay 3
 *							0b00001000		:liga ponto decimal do diplay 4
 * 
 * Saída:          	Nenhuma (void)
 * Descrição:       Escreve valor decimal de 0000 a 9999 nos display's de 7 segmentos.
 *					e salva o valor de cada dígito nas variaveis globais correspondentes.
 *					Este valor fica armazenado e é preciso chamar periodicamente a função
 *					update para manter o número visível.
 *					Liga/desliga o ponto decimal.
 *
 *****************************************************************************/
 extern void EscreveDisplay7Seg(unsigned int numero, unsigned char ponto);

/******************************************************************************
 * Funcao:        	void UpdateDisplay7Seg()
 * 
 * Entrada:         Nenhuma (void)
 *					
 * Saída:          	Nenhuma (void)
 * Descrição:       Deve chamada a cada 20 ms durante a execução do programa.
 *					É recomendado que esta função seja chamada em uma interrupção
 *				    ativada pelo timer.
 *
 *****************************************************************************/
 extern void UpdateDisplay7Seg();


/******************************************************************************
 * Funcao:        	void SetDisplay7Seg(char numero,char display)
 * 
 * Entrada:         Número que deve aparecer no diplay, display em que o número
 *					deve aparecer
 * Saída:          	Nenhuma (void)
 * Descrição:       A função escreve um número em um display.
 *
 *****************************************************************************/
 extern void SetDisplay7Seg(char numero, char display);
