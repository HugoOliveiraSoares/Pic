
/******************************************************************************
 *
 *            Biblioteca SEMPRA (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     teclado.c
 * Dependencias:        Veja se��o INCLUDES
 * Processador:         PIC32MX775F512L
 * Op��o de Clock:      HS 8MHz (externo) - CPU: 80MHz
 * Compilador:          C32 v.1.01 ou superior
 * Empresa:             SEMPRA - Axoon
 *
 * Plataforma:          Kit SEMPRA E-P32
 *
 * Autores:             James Hamilton Oliveira Junior
 *                      Bruno S. Avelar
 *                      Bruno Al�pio Dayrell
 *
 * Data:            v1 - 24/Jan/2010
 *                  v2 - 25/Jan/2010
 *                  v3 - 26/Jan/2010
 *                  v4 - 28/Jan/2010
 *                  v5 - 24/Fev/2012
 *
 * Descri��o:       Biblioteca de fun��es para ler de um teclado de 16 ou 12 teclas
 *                  (4x4 ou 4x3) atrav�s de interrup��es. O teclado dever� ser 
 *                  conectado a porta do microcontrolador que possui interrup��es 
 *                  de grupo, no caso do PIC18F4550, portaB de RB4 at� RB7.
 *                  
 *                  O funcionamento de um teclado do tipo matriz � simples. Sempre que
 *                  uma tecla � pressionada, a linha a coluna s�o conectas. Por exemplo,
 *                  pressionada, a linha 2 ficar� com nivel logico 1 tamb�m. 
 *                  
 *                  No uso desse teclado com o microcontrolador, conectamos suas linhas
 *                  em portas de output, e suas colunas em portas de input. As colunas 
 *                  s�o conectas am pinos de input do microcontrolador e assume nivel
 *                  logico 1. Colocando nivel logico 0 nas linhas, podemos saber quando
 *                  uma tecla � pressionada pela varia��o de uma coluna. Para indentificar
 *                  a tecla, basta fazer uma busca pelo teclado, alternando o bit '0'
 *                  entre as linhas e verificando qual coluna permanece em '0'.
 *                  
 *                  As coluna do teclado devem ser conectas as portas com interrup��es
 *                  ,inputs, enquanto as linhas devem ser conectas a portas configuras
 *                  como outpus. O esquema abaixo demonstra as liga��es
 *                  
 *         
 *                                 C     C     C     C
 *                                 O     O     O     O
 *                                 L     L     L     L
 *                                 U     U     U     U
 *                                 N     N     N     N
 *                                 A     A     A     A
 *                                 |     |     |     |
 *                                 0     1     2     3  -> Coluna 3 n�o implementada
 *                                :     :     :     :
 *                                   :     :     :     :
 *                               __:    __:    __:    __:
 *                              |00|   |01|   |02|   |03|
 *                  LINHA_0   --------|__|----|__|----|__|----|__|
 *                                   :     :     :     :
 *                               __:    __:    __:    __:
 *                              |10|   |11|   |12|   |13|
 *                  LINHA_1   --------|__|----|__|----|__|----|__|
 *                                   :     :     :     :
 *                               __:    __:    __:    __:
 *                              |20|   |21|   |22|   |23|
 *                  LINHA_2   --------|__|----|__|----|__|----|__|
 *                                       :     :     :     :
 *                               __:    __:    __:    __:
 *                              |30|   |31|   |32|   |33|
 *                  LINHA_3   --------|__|----|__|----|__|----|__|            
 *      
 *      
 *      
 *                  Como queremos que os pinos de input do PIC fiquem em nivel
 *                  logico alto (1) quando desconectados (nenhuma tecla pressionada)
 *                  precisamos habilitar os resistores de pull-up internos
 *                  ou acrescentar resistores externos:
 * 
 *                  Resistores de Pull-up:
 *               
 *                  /|\
 *                 /_|_\ Vcc
 *                   |
 *                   |               
 *                      _|_
 *                 |  |
 *                 | R |
 *                 |_ _|
 *                   |              ()
 *                   |                 \      |  GND
 *                 __|____              \      ||
 *                  pino  |_________()  \______||| 
 *                 _______|                  ||| 
 *                                       ||
 *                                       |
 *
 *                  para habilitar os pull-ups da porta B: INTCON2bits.RBPU=0;
 *                  pagina 114, item 10.2 do datasheet do PIC18F4550:
 *                  
 *                  "Each of the PORTB pins has a weak internal pull-up. A
 *                  single control bit can turn on all the pull-ups. This is
 *                   performed by clearing bit, RBPU (INTCON2<7>). The
 *                  weak pull-up is automatically turned off when the port
 *                  pin is configured as an output. The pull-ups are
 *                  disabled on a Power-on Reset."               
 *                                       
 *                                                
 *****************************************************************************/
/*****************************************************************************/
//
//                       I N C L U D E S
//
//
/*****************************************************************************/

#include "Teclado.h"

/*****************************************************************************/
//
//                        V A R I � V E I S
//
//
/*****************************************************************************/

unsigned char Matriz_Teclado[3][4];      //Matriz de teclas pressionadas

int Teclado_Flag = 0;                //Flag, indica se o a Matriz_Teclado foi escrita
                              //pela interrup��o (Teclado_Flag = 1) e/ou se ja 
                              //foi lida pelo programa (Teclado_Flag = 0)
                                 
/*****************************************************************************/
//
//                       F U N � � E S
//
//
/*****************************************************************************/

/******************************************************************************
 * Funcao:           void Interrupcao_Teclado (void)
 * Entrada:        Nenhuma (void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao a ser executada quando uma interrupcao
 *               do teclado ocorrer. Determina as teclas pressionadas
 *               por meio de uma matriz: Matriz_Teclado[][] onde o primeiro 
 *               colchete representa as linhas e o segundo as colunas.
 *
 *               Essa fun��o deve ser chamada quando a interrup��o ocorrer.
 *               Ela apenas "l�" o teclado e armazena as teclas que foram
 *               pressionadas em uma matriz. A fun��o insere um '0' nas
 *               posi��es da matriz onde teclas foram pressionadas.
 *               
 *               A fun��o Interrup��o_Teclado, entretanto, n�o evita "bounce",
 *               ficando sob responsabilidade do usu�rio.
 *               
 *               Uma sugest�o consiste em, cada vez que uma interrup��o
 *               ocorrer, desabilitar as interrup��es do teclado e disparar
 *               um timer. Quando a iterrup��o do timer ocorrer, as
 *               interrup��es do teclado s�o novamente habilitadas.
 *
 *****************************************************************************/
 void Interrupcao_Teclado (void)
 {
    //   if (Teclado_Flag == 0)   //enquanto o buffer n�o for lido pelo programa,
    //   {                     //uma nova leitura n�o ser� feita.


             COLUNA_0 = 0;
             COLUNA_1 = 0;
             COLUNA_2 = 1;
             COLUNA_3 = 0;

             LINHA_0 = 0;
             LINHA_2 = 0;
             Matriz_Teclado[0][2] = LINHA_0;    // Botao 9
             Matriz_Teclado[1][2] = LINHA_1;    // Botao 6
             Matriz_Teclado[2][2] = LINHA_2;    // Botao 3


             COLUNA_0 = 1;
             COLUNA_1 = 0;                  //seta apenas uma das linhas de cada vez, e
             COLUNA_2 = 0;                  //testa as colunas, assim � possivel identificar
             COLUNA_3 = 0;                  //as teclas pressionadas

             LINHA_0 = 0;
             LINHA_2 = 0;
             Matriz_Teclado[0][0] = LINHA_0;    // Botao 7
             Matriz_Teclado[1][0] = LINHA_1;    // Botao 4
             Matriz_Teclado[2][0] = LINHA_2;    // Botao 1
                         
             COLUNA_0 = 0;
             COLUNA_1 = 1;
             COLUNA_2 = 0;
             COLUNA_3 = 0;

             LINHA_0 = 0;
             LINHA_2 = 0;
             Matriz_Teclado[0][1] = LINHA_0;    // Botao 8
             Matriz_Teclado[1][1] = LINHA_1;    // Botao 5
             Matriz_Teclado[2][1] = LINHA_2;    // Botao 2
             

             

             COLUNA_0 = 0;
             COLUNA_1 = 0;
             COLUNA_2 = 0;
             COLUNA_3 = 1;                  //as teclas pressionadas 
             
             Matriz_Teclado[0][3] = LINHA_0;    // Botao Cancela
             Matriz_Teclado[1][3] = LINHA_1;    // Botao Enter
             Matriz_Teclado[2][3] = LINHA_2;    // Botao 0(zero)
             
             COLUNA_0 = 1;            // todas as linhas s�o colocadas novamente
             COLUNA_1 = 1;            // em '1', dessa forma, quando uma nova tecla
             COLUNA_2 = 1;            // for pressionada haver� interrup��o.
             COLUNA_3 = 1;
             COLUNA_3 = 1;            // as teclas pressionadas
 
             
             Teclado_Flag = 1;      //seta o flag, indicando para o programa que
                                    //o teclado foi escrito, ele n�o ser� escrito
    //   }//fim if                  //de novo ate que seja lido pelo programa
 }//fim Interrupcao_Teclado
 
 /******************************************************************************
 * Funcao:           void Tecla_Pressionada (unsigned char Linha, unsigned char Coluna)
 *
 * Entrada:        unsigned char Linha  -> linha da matriz que se deseja acessar (de 0 at� 3)
 *               unsigned char Coluna -> coluna da matriz que se deseja acessar (de 0 at� 2 ou 3)
 *
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que retorna o bit binario invertido contido na 
 *               matriz do teclado. Se a tecla de coordendas indicadas
 *               pelas entradas da fun��o tiver sido pressionada, ser� 
 *               retornado o valor '1', se a tecla n�o tiver sido pressionada
 *               a fun��o retorna '0'
 *
 *****************************************************************************/
 unsigned int Tecla_Pressionada (unsigned char Linha, unsigned char Coluna)
  {
     return Matriz_Teclado[Linha][Coluna];       //retorna 1 se a tecla foi pressionada
                                      //e 0 se n�o foi.      
  }
 /*****************************************************************************/
 /******************************************************************************
 * Funcao:           void Teclado_Escrito (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que retorna o valor do flag do teclado (Teclado_Flag). 
 *               Se o valor retornado for 1, o a matriz do teclado foi escrita  
 *               pela rotina de interrup��o e portanto possui informa��es n�o 
 *               processadas pelo programa, se seu valor for '0', a matriz do
 *               teclado ja foi lida pelo programa e n�o contem informa��es 
 *               novas. 
 *
 *****************************************************************************/
 unsigned int Teclado_Escrito (void)
  {
     return (Teclado_Flag); //retorna 1 se teclado foi escrito
  }
 /*****************************************************************************/  
 /******************************************************************************
 * Funcao:           void Teclado_Lido (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que retorna zera o valor do flag do teclado (Teclado_Flag). 
 *               Dessa forma, o programa indica que a matriz do teclado j� foi lida,  
 *               habilitando a rotina de interrup��o a escrever na matriz caso uma
 *               nova tecla seja pressionada
 *
 *****************************************************************************/
  void Teclado_Lido (void)
  {
     Teclado_Flag = 0;
  }
 /*****************************************************************************/
 /******************************************************************************
 * Funcao:           unsigned int Posicao_Teclado (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que retorna a posi��o da primeira tecla encontrada
 *               na matriz de teclas. Se nenhuma tecla tiver sido pressionada,
 *               a fun��o retorna '99', um c�digo de erro.
 *
 *****************************************************************************/
  unsigned int Posicao_Teclado (void)
  {
        int i, j;
      
        for (i=0; i<=2; i++)
        {
           for(j=0; j<=3; j++)             
           {                           
              if (Matriz_Teclado[i][j] == 1)
              { 
                 Teclado_Flag = 0;
                 return ((i*10)+j);         //retorna a posi�ao da primeira tecla encontrada
              }
           }
        }   
        Teclado_Flag = 0;
        return 99;       //nenhuma tecla pressionada 'erro'
  }//fim fun��o
 /*****************************************************************************/   
 /******************************************************************************
 * Funcao:           void Limpa_Matriz_Teclado (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que 'limpa' todas as posi��es da matriz do teclado.
 *               A fun��o percorre todas as posi��es atribuido o bit '1'.
 *               Ou seja, que a tecla dessa posi��o n�o foi pressionada
 *
 *****************************************************************************/
void Limpa_Matriz_Teclado (void) 
{   
   char i,j;
   
   for(i=0; i<=2; i++)
   {
      for (j=0; j<=3; j++)          
      {                        
         Matriz_Teclado[i][j] = 0;
      }
   }      
}      
/*****************************************************************************/
/******************************************************************************
* Funcao:      void Inicializa_Teclado (void)
*
* Entrada:      Nenhuma(void)
* Sa�da:        Nenhuma (void)
* Descri��o:    Funcao que iniciliza o teclado, garantido que os valores
*            lidos seja corretos. A fun��o limpa a matriz do teclado, 
*            reseta o flag_do teclado, e coloca nas linhas (outputs) o
*            bit '0', para que qualquer tecla pressionada possa gerar
*            a primeira interrup��o
*
*****************************************************************************/
void Inicializa_Teclado (void)
{
   CONFIG_LINHA_0 = 1;
   CONFIG_LINHA_1 = 1;
   CONFIG_LINHA_2 = 1;
   
   CONFIG_COLUNA_0 = 0;
   CONFIG_COLUNA_1 = 0;
   CONFIG_COLUNA_2 = 0;
   CONFIG_COLUNA_3 = 0;
   
   Limpa_Matriz_Teclado(); 
   Teclado_Flag = 0;       //habilita teclado para a escrita
   
    COLUNA_0 = 1;            //seta as portas de output para detectar uma
    COLUNA_1 = 1;            //tecla pressionada.
    COLUNA_2 = 1;
    COLUNA_3 = 1;
}      

 /******************************************************************************
 * Funcao:           unsigned int Numero_Teclado (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que retorna o NUMERO da primeira tecla encontrada
 *               na matriz de teclas. Se nenhuma tecla tiver sido pressionada,
 *               a fun��o retorna '99', um c�digo de erro.
 *
 *****************************************************************************/
unsigned int Numero_Teclado (void)
{
     int i, j;
     
     for (i=0; i<=2; i++)
     {
        for(j=0; j<=2; j++)          
        {                           
        if (Matriz_Teclado[i][j] != 0)
        {
               //os caracteres da linha 3 sao uma excessao
                Teclado_Flag = 0;
                return ((3*i+1+j));
        }//fim if
	 }//fim for   	     
     }   

		if(Matriz_Teclado[0][3])
		{	
        	Teclado_Flag = 0;
            return 0;
  		}
  		else
  		{
			if(Matriz_Teclado[1][3])
			{	
        		Teclado_Flag = 0;
            	return 10;
  			}
  			else
  			{
				if(Matriz_Teclado[2][3])
				{	
        			Teclado_Flag = 0;
            		return 11;
  				}	  			
	  		}	
  		}         
   
   Teclado_Flag = 0;
   return 99;             //se nehuma tecla encontrada retorna         
                     //codigo de 'erro' 99
}//fim fun��o


//****************      F I M      D O    A R Q U I V O    *****************/
/*****************************************************************************/