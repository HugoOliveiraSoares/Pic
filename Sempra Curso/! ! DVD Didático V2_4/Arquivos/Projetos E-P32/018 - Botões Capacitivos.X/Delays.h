/*******************************************************************************
 *                  SEMPRA  E-P32 Bibliotece Delays     		       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     delays.h                                               *
 * Dependencias:    	Veja a seção INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Opção de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Versão:		v1.0                                                   *
 * Descrição:        	Conjunto de funções para fazer delays através de       *
 * 			espera ocupada. Estas funções foram desenvolvidas para *
 *                      o microcntrolador PIC32MX e funcionam em um clock      *
 *                      de 80MHz.                                              *
 *                                                                             *
 *******************************************************************************
 * *****************************************************************************
 * Log de modificações:							       *
 * Rev   Data         Descrição						       *
 * 1.0   31/01/2012 	 Versão inicial - Bruno S. Avelar		       *
 ******************************************************************************/

#ifndef __DELAYS_H
#define __DELAYS_H

#include <plib.h> // Biblioteca para uso dos periféricos do PIC32.


/******************************************************************************
 * Funcao:         void DelayMsx (unsigned int ms)
 * Entrada:        unsigned int ms - Tempo em milesegundos de delay
 * Saída:          Nenhuma (void)
 * Descrição:      Esta função faz espera ocupada com a CPU por ms milesegundos.
 *		   Em que ms é recebido como parametro da função.
 *****************************************************************************/
void DelayMsx(unsigned int ms);

/*******************************************************************************
 * Funcao:         void DelayUsx(unsigned int us);
 * Entrada:        unsigned int us - Tempo em microsegundos de delay
 * Saída:          Nenhuma (void)
 * Descrição:      Esta função faz espera ocupada com a CPU por us
 *                 microsegundos. Em que us é recebido como parametro da função.
 *		   Para valores pequenos passados como parametro a precisão
 *                 da funçao será baixa. Caso você precise de precisão de poucos
 *                 microsegundos considere o não uso desta função.
 *****************************************************************************/
 void DelayUsx(unsigned int us);

#endif

