
/*****************************************************************************/
//
//                       I N C L U D E S
//
//
/*****************************************************************************/

#include "MatrixButton.h"

/*****************************************************************************/
//
//                        V A R I Á V E I S
//
//
/*****************************************************************************/

unsigned char keyMatrix[3][4];      //Matriz de teclas pressionadas

int matrixFlag = 0;          //Flag, indica se o a keyMatrix foi escrita
                              //pela interrupção (matrixFlag = 1) e/ou se ja
                              //foi lida pelo programa (matrixFlag = 0)
                                 
/*****************************************************************************/
//
//                       F U N Ç Õ E S
//
//
/*****************************************************************************/

/******************************************************************************
 *Funcao: void MatrixScan (void)
 *****************************************************************************/

void MatrixScan(void)
 {

         COLUNA_0 = 0;
         COLUNA_1 = 0;
         COLUNA_2 = 1;
         COLUNA_3 = 0;

         keyMatrix[0][2] = LINHA_0;    // Botao 9
         keyMatrix[1][2] = LINHA_1;    // Botao 6
         keyMatrix[2][2] = LINHA_2;    // Botao 3

         COLUNA_0 = 1;
         COLUNA_1 = 0;                  //seta apenas uma das linhas de cada vez, e
         COLUNA_2 = 0;                  //testa as colunas, assim é possivel identificar
         COLUNA_3 = 0;                  //as teclas pressionadas


         keyMatrix[0][0] = LINHA_0;    // Botao 7
         keyMatrix[1][0] = LINHA_1;    // Botao 4
         keyMatrix[2][0] = LINHA_2;    // Botao 1

         COLUNA_0 = 0;
         COLUNA_1 = 1;
         COLUNA_2 = 0;
         COLUNA_3 = 0;


         keyMatrix[0][1] = LINHA_0;    // Botao 8
         keyMatrix[1][1] = LINHA_1;    // Botao 5
         keyMatrix[2][1] = LINHA_2;    // Botao 2

         COLUNA_0 = 0;
         COLUNA_1 = 0;
         COLUNA_2 = 0;
         COLUNA_3 = 1;

         keyMatrix[0][3] = LINHA_0;    // Botao Cancela
         keyMatrix[1][3] = LINHA_1;    // Botao Enter
         keyMatrix[2][3] = LINHA_2;    // Botao 0(zero)

         COLUNA_0 = 1;            // todas as linhas são colocadas novamente
         COLUNA_1 = 1;            // em '1', dessa forma, quando uma nova tecla
         COLUNA_2 = 1;            // for pressionada haverá interrupção.
         COLUNA_3 = 1;
         COLUNA_3 = 1;            // as teclas pressionadas


         matrixFlag = 1;      //seta o flag, indicando para o programa que
                                //o teclado foi escrito, ele não será escrito
                                //de novo ate que seja lido pelo programa
 }//fim MatrixScan
 
/******************************************************************************
 *Funcao: unsigned int KeyPressed (unsigned char Linha, unsigned char Coluna)
 *****************************************************************************/
 unsigned int KeyPressed (unsigned char Linha, unsigned char Coluna)
  {
     return keyMatrix[Linha][Coluna];       //retorna 1 se a tecla foi pressionada
                                                 //e 0 se não foi.
  }
/******************************************************************************
 *Funcao: unsigned int GetMatrixFlag (void)
 *****************************************************************************/
  unsigned int GetMatrixFlag (void)
  {
     return (matrixFlag); //retorna 1 se teclado foi escrito
  }
 /******************************************************************************
 *Funcao: void CleanMatrixFlag (void)
 *****************************************************************************/
  void CleanMatrixFlag (void)
  {
     matrixFlag = 0;
  }
 /******************************************************************************
 *Funcao: unsigned int MatrixPosition (void)
 *****************************************************************************/
  unsigned int MatrixPosition (void)
  {
        int i, j;
      
        for (i=0; i<=2; i++)
        {
           for(j=0; j<=3; j++)             
           {                           
              if (keyMatrix[i][j] == 1)
              { 
                 matrixFlag = 0;
                 return ((i*10)+j);         //retorna a posiçao da primeira tecla encontrada
              }
           }
        }   
        matrixFlag = 0;
        return 99;       //nenhuma tecla pressionada 'erro'
  }//fim função
 /******************************************************************************
 *Funcao: void MatrixClean (void)
 *****************************************************************************/
  void MatrixClean (void)
  {
     char i,j;

     for(i=0; i<=2; i++)
     {
        for (j=0; j<=3; j++)
        {
           keyMatrix[i][j] = 0;
        }
     }
  }
 /******************************************************************************
 *Funcao: void ButtonMatrixInit (void)
 *****************************************************************************/
void ButtonMatrixInit (void)
{
   CONFIG_LINHA_0 = 1;
   CONFIG_LINHA_1 = 1;
   CONFIG_LINHA_2 = 1;
   
   CONFIG_COLUNA_0 = 0;
   CONFIG_COLUNA_1 = 0;
   CONFIG_COLUNA_2 = 0;
   CONFIG_COLUNA_3 = 0;
   
   MatrixClean();
   matrixFlag = 0;       //habilita teclado para a escrita
   
    COLUNA_0 = 1;            //seta as portas de output para detectar uma
    COLUNA_1 = 1;            //tecla pressionada.
    COLUNA_2 = 1;
    COLUNA_3 = 1;
}      
/******************************************************************************
 *Funcao: unsigned int NumberPress (void)
 *****************************************************************************/
unsigned int NumberPress (void)
{
     int i, j;
     
     for (i=0; i<=2; i++)
     {
        for(j=0; j<=2; j++)          
        {                           
            if (keyMatrix[i][j] != 0)
            {
                   //os caracteres da linha 3 sao uma excessao
                    matrixFlag = 0;
                    return ((3*i+1+j));
            }//fim if
	}//fim for   	     
     }   

    if(keyMatrix[0][3])
    {
        matrixFlag = 0;
        return 0;
    }
    else
    {
        if(keyMatrix[1][3])
        {
            matrixFlag = 0;
            return 10;
        }
        else
        {
            if(keyMatrix[2][3])
            {
                matrixFlag = 0;
                return 11;
            }
        }
    }
   matrixFlag = 0;
   return 99;   //se nehuma tecla encontrada retorna         
                //codigo de 'erro' 99
}//fim função


//****************      F I M      D O    A R Q U I V O    *****************/
/*****************************************************************************/