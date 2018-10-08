
/******************************************************************************
 *
 *            Biblioteca SEMPRA (PIC32MX775F512L)
 *
 ******************************************************************************
 * Nome do Arquivo:     teclado.h
 * Dependencias:        Veja seção INCLUDES
 * Processador:         PIC32MX775F512L
 * Opção de Clock:      HS 8MHz (externo) - CPU: 80MHz
 * Compilador:          C32 v.1.01 ou superior
 * Empresa:             SEMPRA - Axoon
 *
 * Plataforma:          Kit SEMPRA E-P32
 *
 * Autores:            James Hamilton Oliveira Junior
 *					   Bruno S. Avelar
 * Data:      	       v1 - 24/Jan/2010
 *                     v2 - 25/Jan/2010
 *                     v3 - 26/Jan/2010
 *                     v4 - 28/Jan/2010
 *					   v5 - 13/Jul/2011
 *
 * Descrição:        Biblioteca de funções para ler de um teclado de 12 teclas
 *                  (4x3) através de interrupções. 
 *                  
 *                  Sempre que uma tecla é pressionada, a linha a coluna são conectas. 
 *					Por exemplo,
 *                  pressionada, a linha 2 ficará com nivel logico 1 também. 
 *                  
 *                  No uso desse teclado com o microcontrolador, conectamos suas linhas
 *                  em portas de output, e suas colunas em portas de input. As colunas 
 *                  são conectas am pinos de input do microcontrolador e assume nivel
 *                  logico 1. Colocando nivel logico 0 nas linhas, podemos saber quando
 *                  uma tecla é pressionada pela variação de uma coluna. Para indentificar
 *                  a tecla, basta fazer uma busca pelo teclado, alternando o bit '0'
 *                  entre as linhas e verificando qual coluna permanece em '0'.
 *                  
 *                  As coluna do teclado devem ser conectas as portas com interrupções
 *                  ,inputs, enquanto as linhas devem ser conectas a portas configuras
 *                  como outpus. O esquema abaixo demonstra as ligações
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

#include <p32xxxx.h>
#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.
#include "HardwareProfile.h"

/*****************************************************************************/
//
//                    P R O T O T I P O S
//
//
/*****************************************************************************/   

/******************************************************************************
 * Funcao:           void Interrupcao_Teclado (void)
 * Entrada:        Nenhuma (void)
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao a ser executada quando uma interrupcao
 *               do teclado ocorrer. Determina as teclas pressionadas
 *               por meio de uma matriz: Matriz_Teclado[][] onde o primeiro 
 *               colchete representa as linhas e o segundo as colunas.
 *
 *               Essa função deve ser chamada quando a interrupção ocorrer.
 *               Ela apenas "lê" o teclado e armazena as teclas que foram
 *               pressionadas em uma matriz. A função insere um '0' nas
 *               posições da matriz onde teclas foram pressionadas.
 *               
 *               A função Interrupção_Teclado, entretanto, não evita "bounce",
 *               ficando sob responsabilidade do usuário.
 *               
 *               Uma sugestão consiste em, cada vez que uma interrupção
 *               ocorrer, desabilitar as interrupções do teclado e disparar
 *               um timer. Quando a iterrupção do timer ocorrer, as
 *               interrupções do teclado são novamente habilitadas.
 *
 *****************************************************************************/
 extern void Interrupcao_Teclado (void);
 
 /******************************************************************************
 * Funcao:           void Tecla_Pressionada (unsigned char Linha, unsigned char Coluna)
 *
 * Entrada:        unsigned char Linha  -> linha da matriz que se deseja acessar
 *               unsigned char Coluna -> coluna da matriz que se deseja acessar
 *
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao que retorna o bit binario invertido contido na 
 *               matriz do teclado. Se a tecla de coordendas indicadas
 *               pelas entradas da função tiver sido pressionada, será 
 *               retornado o valor '1', se a tecla não tiver sido pressionada
 *               a função retorna '0'
 *
 *****************************************************************************/
 extern unsigned int Tecla_Pressionada (unsigned char Linha, unsigned char Coluna);

 /*****************************************************************************/
 /******************************************************************************
 * Funcao:           void Teclado_Escrito (void)
 *
 * Entrada:        Nenhuma(void)
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao que retorna o valor do flag do teclado (Teclado_Flag). 
 *               Se o valor retornado for 1, o a matriz do teclado foi escrita  
 *               pela rotina de interrupção e portanto possui informações não 
 *               processadas pelo programa, se seu valor for '0', a matriz do
 *               teclado ja foi lida pelo programa e não contem informações 
 *               novas. 
 *
 *****************************************************************************/
 extern unsigned int Teclado_Escrito (void);

 /*****************************************************************************/  
 /******************************************************************************
 * Funcao:           void Teclado_Lido (void)
 *
 * Entrada:        Nenhuma(void)
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao que zera o valor do flag do teclado (Teclado_Flag). 
 *               Dessa forma, o programa indica que a matriz do teclado já foi lida,  
 *               habilitando a rotina de interrupção a escrever na matriz caso uma
 *               nova tecla seja pressionada
 *
 *****************************************************************************/
 extern void Teclado_Lido (void);

 /*****************************************************************************/
 /******************************************************************************
 * Funcao:           unsigned int Posicao_Teclado (void)
 *
 * Entrada:        Nenhuma(void)
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao que retorna a posição da primeira tecla encontrada
 *               na matriz de teclas. Se nenhuma tecla tiver sido pressionada,
 *               a função retorna '99', um código de erro.
 *
 *****************************************************************************/
 extern unsigned int Posicao_Teclado (void);

 /*****************************************************************************/   
 /******************************************************************************
 * Funcao:           void Limpa_Matriz_Teclado (void)
 *
 * Entrada:        Nenhuma(void)
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao que 'limpa' todas as posições da matriz do teclado.
\ *               A função percorre todas as posições atribuido o bit '1'.
 *               Ou seja, que a tecla dessa posição não foi pressionada
 *
 *****************************************************************************/
 extern void Limpa_Matriz_Teclado (void);

/*****************************************************************************/
/******************************************************************************
* Funcao:      void Inicializa_Teclado (void)
*
* Entrada:      Nenhuma(void)
* Saída:        Nenhuma (void)
* Descrição:    Funcao que iniciliza o teclado, garantido que os valores
*            lidos sejam corretos. A função limpa a matriz do teclado, 
*            reseta o flag_do teclado, e coloca nas linhas (outputs) o
*            bit '1', para que qualquer tecla pressionada possa gerar
*            a primeira interrupção
*
*****************************************************************************/
extern void Inicializa_Teclado (void);

 /******************************************************************************
 * Funcao:           unsigned int Numero_Teclado (void)
 *
 * Entrada:        Nenhuma(void)
 * Saída:             Nenhuma (void)
 * Descrição:      Funcao que retorna o NUMERO da primeira tecla encontrada
 *               na matriz de teclas. Se nenhuma tecla tiver sido pressionada,
 *               a função retorna '99', um código de erro.
 *
 *****************************************************************************/
extern unsigned int Numero_Teclado (void);


/****************      F I M      D O    A R Q U I V O    *****************/
/****************************************************************************/