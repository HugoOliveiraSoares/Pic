/*******************************************************************************
 *                  SEMPRA  E-P32 Bibliotece Delays     		       *
 *									       *
 *******************************************************************************
 * Nome do Arquivo:     delays.h                                               *
 * Dependencias:    	Veja a se��o INCLUDES abaixo                           *
 * Microcontrolador:    PIC32MX775F512L					       *
 * Op��o de Clock:	HS 8MHz (externo) - CPU 80MHz                          *
 * Compilador:        	C32						       *
 * Empresa:         	SEMPRA						       *
 * Plataforma:		Placa E-P32	V1.0                                   *
 *									       *
 * Autor:		Bruno Avelar                                           *
 * Vers�o:		v1.0                                                   *
 * Descri��o:        	Conjunto de fun��es para fazer delays atrav�s de       *
 * 			espera ocupada. Estas fun��es foram desenvolvidas para *
 *                      o microcntrolador PIC32MX e funcionam em um clock      *
 *                      de 80MHz.                                              *
 *                                                                             *
 *******************************************************************************
 * *****************************************************************************
 * Log de modifica��es:							       *
 * Rev   Data         Descri��o						       *
 * 1.0   31/01/2012 	 Vers�o inicial - Bruno S. Avelar		       *
 ******************************************************************************/

#ifndef __DELAYS_H
#define __DELAYS_H

#include <plib.h> // Biblioteca para uso dos perif�ricos do PIC32.


/******************************************************************************
 * Funcao:         void DelayMsx (unsigned int ms)
 * Entrada:        unsigned int ms - Tempo em milesegundos de delay
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Esta fun��o faz espera ocupada com a CPU por ms milesegundos.
 *		   Em que ms � recebido como parametro da fun��o.
 *****************************************************************************/
void DelayMsx(unsigned int ms);

/*******************************************************************************
 * Funcao:         void DelayUsx(unsigned int us);
 * Entrada:        unsigned int us - Tempo em microsegundos de delay
 * Sa�da:          Nenhuma (void)
 * Descri��o:      Esta fun��o faz espera ocupada com a CPU por us
 *                 microsegundos. Em que us � recebido como parametro da fun��o.
 *		   Para valores pequenos passados como parametro a precis�o
 *                 da fun�ao ser� baixa. Caso voc� precise de precis�o de poucos
 *                 microsegundos considere o n�o uso desta fun��o.
 *****************************************************************************/
 void DelayUsx(unsigned int us);

#endif

