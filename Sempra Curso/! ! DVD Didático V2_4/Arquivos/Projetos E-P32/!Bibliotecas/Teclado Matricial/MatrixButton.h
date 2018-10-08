
/******************************************************************************
 *
 *            Biblioteca SEMPRA (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     teclado.h
 * Dependencias:        Veja se��o INCLUDES
 * Processador:         PIC32MX775F512L
 * Op��o de Clock:      HS 8MHz (externo) - CPU: 80MHz
 * Compilador:          C32 v.1.01 ou superior
 * Empresa:             SEMPRA - Axoon
 *
 * Plataforma:          Kit SEMPRA E-P32
 *
 * Autores:            James Hamilton Oliveira Junior
 *                     Bruno S. Avelar
 * Data:      	       v1 - 24/Jan/2010
 *                     v2 - 25/Jan/2010
 *                     v3 - 26/Jan/2010
 *                     v4 - 28/Jan/2010
 *		       v5 - 13/Jul/2011
 *                     v6 - 11/Mai/2012
 *
 * Descri��o:        Biblioteca de fun��es para ler de um teclado de 12 teclas
 *                  (4x3) atrav�s de interrup��es. 
 *                  
 *                  Sempre que uma tecla � pressionada, a linha a coluna s�o conectas. 
 *                  
 *                  No uso desse teclado com o microcontrolador, conectamos suas linhas
 *                  em portas de saida digital, e suas colunas em portas de saida digital
 *                  Para indentificar a tecla, basta fazer uma busca pelo teclado, alternando o bit '0'
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
 *                                 :     :     :     :
 *                                 :     :     :     :
 *                               __:   __:   __:   __:
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
 *****************************************************************************/
/*****************************************************************************/
//
//                       I N C L U D E S
//
//
/*****************************************************************************/

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.
#include "HardwareProfile.h"
/*****************************************************************************/
//
//                       D E F I N E S
//
//
/*****************************************************************************/                  
//  Define os pinos onde ser� conectado o teclado.

#define LINHA_0      PORTAbits.RA14
#define LINHA_1      PORTEbits.RE9
#define LINHA_2      PORTEbits.RE8

#define COLUNA_0     LATDbits.LATD3
#define COLUNA_1     LATDbits.LATD12
#define COLUNA_2     LATAbits.LATA9
#define COLUNA_3     LATDbits.LATD8

#define CONFIG_LINHA_0 TRISEbits.TRISE8
#define CONFIG_LINHA_1 TRISEbits.TRISE9
#define CONFIG_LINHA_2 TRISAbits.TRISA14

#define CONFIG_COLUNA_0 TRISDbits.TRISD3
#define CONFIG_COLUNA_1 TRISDbits.TRISD12
#define CONFIG_COLUNA_2 TRISAbits.TRISA9
#define CONFIG_COLUNA_3 TRISDbits.TRISD8

/*****************************************************************************/
//
//                    P R O T O T I P O S
//
//
/*****************************************************************************/   


/******************************************************************************
* Funcao:      void ButtonMatrixInit (void)
*
* Entrada:      Nenhuma(void)
* Sa�da:        Nenhuma (void)
* Descri��o:    Funcao que iniciliza o teclado, garantido que os valores
*               lidos sejam corretos. A fun��o limpa a matriz do teclado,
*               reseta o flag_do teclado, e coloca nas linhas (outputs) o
*               bit '1', para que qualquer tecla pressionada possa gerar
*               a primeira interrup��o
*
*****************************************************************************/
extern void ButtonMatrixInit(void);


/******************************************************************************
 * Funcao:         void MatrixScan (void)
 * Entrada:        Nenhuma (void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Funcao a ser executada quando uma interrupcao
 *                 do teclado ocorrer. Determina as teclas pressionadas
 *                 por meio de uma matriz: keyMatrix[][] onde o primeiro
 *                 colchete representa as linhas e o segundo as colunas.
 *
 *                  A fun��o Interrup��o_Teclado, entretanto, n�o evita "bounce",
 *                  ficando sob responsabilidade do usu�rio.
 *               
 *                  Uma sugest�o consiste em, cada vez que uma interrup��o
 *                  ocorrer, desabilitar as interrup��es do teclado e disparar
 *                  um timer. Quando a iterrup��o do timer ocorrer, as
 *                  interrup��es do teclado s�o novamente habilitadas.
 *
 *****************************************************************************/
 extern void MatrixScan(void);


 /******************************************************************************
 * Funcao:           unsigned int NumberPress (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:             Nenhuma (void)
 * Descri��o:      Funcao que retorna o NUMERO da primeira tecla encontrada
 *                 na matriz de teclas. Se nenhuma tecla tiver sido pressionada,
 *                  a fun��o retorna '99', um c�digo de erro.
 *
 *****************************************************************************/
 extern unsigned int NumberPress (void);

 /******************************************************************************
 * Funcao:         unsigned int MatrixPosition (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Funcao que retorna a posi��o da primeira tecla encontrada
 *                 na matriz de teclas. Se nenhuma tecla tiver sido pressionada,
 *                 a fun��o retorna '99', um c�digo de erro.
 *
 *****************************************************************************/
 extern unsigned int MatrixPosition (void);

 /******************************************************************************
 * Funcao:       void KeyPressed (unsigned char Linha, unsigned char Coluna)
 *
 * Entrada:      unsigned char Linha  -> linha da matriz que se deseja acessar
 *               unsigned char Coluna -> coluna da matriz que se deseja acessar
 *
 * Sa�da:        Nenhuma (void)
 * Descri��o:    Funcao que retorna o estado do bot�o indicado nos parametros
  *              linha e coluna. Se a tecla de coordendas indicadas
 *               pelas entradas da fun��o tiver sido pressionada, ser� 
 *               retornado o valor '1', se a tecla n�o tiver sido pressionada
 *               a fun��o retorna '0'
 *
 *****************************************************************************/
 extern unsigned int KeyPressed (unsigned char Linha, unsigned char Coluna);

 /******************************************************************************
 * Funcao:         void MatrixClean (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Funcao que 'limpa' todas as posi��es da matriz do teclado.
 *                A fun��o percorre todas as posi��es atribuido o bit '1'.
 *                 Ou seja, que a tecla dessa posi��o n�o foi pressionada
 *
 *****************************************************************************/
 extern void MatrixClean (void);

 /******************************************************************************
 * Funcao:       int GetMatrixFlag (void)
 *
 * Entrada:      Nenhuma(void)
 * Sa�da:        Nenhuma (void)
 * Descri��o:    Funcao que retorna o valor do flag do teclado (matrixFlag).
 *               Se o valor retornado for 1, o a matriz do teclado foi escrita
 *               pela rotina de interrup��o e portanto possui informa��es n�o
 *               processadas pelo programa, se seu valor for '0', a matriz do
 *               teclado ja foi lida pelo programa e n�o contem informa��es
 *               novas.
 *
 *****************************************************************************/
 extern unsigned int GetMatrixFlag (void);

 /******************************************************************************
 * Funcao:         void CleanMatrixFlag (void)
 *
 * Entrada:        Nenhuma(void)
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Funcao que zera o valor do flag do teclado (matrixFlag).
 *                 Dessa forma, o programa indica que a matriz do teclado j� foi lida,
 *                 habilitando a rotina de interrup��o a escrever na matriz caso uma
 *                 nova tecla seja pressionada
 *
 *****************************************************************************/
 extern void CleanMatrixFlag (void);




/****************      F I M      D O    A R Q U I V O    *****************/
/****************************************************************************/