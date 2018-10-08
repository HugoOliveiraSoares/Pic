/* 
 * File:   Display7seg.h
 * Author: Hugo
 *
 * Created on 1 de Abril de 2017, 12:39
 */

#ifndef DISPLAY7SEG_H
#define	DISPLAY7SEG_H

#include <p18cxxx.h>
// DIFINES
#define Led_A  LATBbits.LATB0
#define Led_B  LATBbits.LATB1
#define Led_C  LATBbits.LATB2
#define Led_D  LATBbits.LATB3
#define Led_E  LATBbits.LATB4
#define Led_F  LATBbits.LATB5
#define Led_G  LATBbits.LATB6
// PROTOTIPO DA FUNÇÃO
void numero(int);
void ConfiguraDisplay(void);

#endif	/* DISPLAY7SEG_H */

