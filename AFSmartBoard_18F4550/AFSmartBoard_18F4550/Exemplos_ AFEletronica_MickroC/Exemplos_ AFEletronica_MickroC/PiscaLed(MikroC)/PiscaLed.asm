
_main:

;PiscaLed.c,3 :: 		void main (void) org 0x1000
;PiscaLed.c,5 :: 		AFSmartBoard_Init(); // função que inicializa a placa AFSmartBoard
	CALL        _AFSmartBoard_Init+0, 0
;PiscaLed.c,7 :: 		PORTA.RA5 = 1;
	BSF         PORTA+0, 5 
;PiscaLed.c,8 :: 		while (1)
L_main0:
;PiscaLed.c,11 :: 		PORTA.RA5 ^= 1;
	BTG         PORTA+0, 5 
;PiscaLed.c,12 :: 		PORTA.RA4 ^= 1;
	BTG         PORTA+0, 4 
;PiscaLed.c,14 :: 		Delay_ms(2000);
	MOVLW       51
	MOVWF       R11, 0
	MOVLW       187
	MOVWF       R12, 0
	MOVLW       223
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
	NOP
	NOP
;PiscaLed.c,15 :: 		}
	GOTO        L_main0
;PiscaLed.c,16 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_AFSmartBoard_Init:

;PiscaLed.c,17 :: 		void AFSmartBoard_Init (void)
;PiscaLed.c,19 :: 		RCON = 0X80; // Limpa o Registro de Reset
	MOVLW       128
	MOVWF       RCON+0 
;PiscaLed.c,20 :: 		ADCON1 = 0x0F; // Configura todas a portas como Portas Analogicas exeto A0
	MOVLW       15
	MOVWF       ADCON1+0 
;PiscaLed.c,21 :: 		CMCON = 0x0F; // Desabilita o Comparador
	MOVLW       15
	MOVWF       CMCON+0 
;PiscaLed.c,22 :: 		LATA = 0;
	CLRF        LATA+0 
;PiscaLed.c,23 :: 		TRISA = 0b11001111;
	MOVLW       207
	MOVWF       TRISA+0 
;PiscaLed.c,24 :: 		T0CON = 0b11000101; // Habilita Timer , 8 bits,clock interno, preescale 1:64
	MOVLW       197
	MOVWF       T0CON+0 
;PiscaLed.c,25 :: 		LATB = 0; // Limpa Latch PortB
	CLRF        LATB+0 
;PiscaLed.c,26 :: 		TRISB = 0; // Coloca todos como tudo Saida
	CLRF        TRISB+0 
;PiscaLed.c,27 :: 		LATD = 0;
	CLRF        LATD+0 
;PiscaLed.c,28 :: 		TRISD = 0x00; // Colocar PORTD como saída
	CLRF        TRISD+0 
;PiscaLed.c,29 :: 		LATE = 0;
	CLRF        LATE+0 
;PiscaLed.c,30 :: 		}
L_end_AFSmartBoard_Init:
	RETURN      0
; end of _AFSmartBoard_Init
