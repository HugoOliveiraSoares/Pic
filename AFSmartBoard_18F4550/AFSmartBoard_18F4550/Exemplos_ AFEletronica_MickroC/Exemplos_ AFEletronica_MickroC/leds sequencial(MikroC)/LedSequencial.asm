
_main:

;LedSequencial.c,29 :: 		void main (void)  org 0x1000
;LedSequencial.c,31 :: 		Board_Init();                // inicia placa
	CALL        _Board_Init+0, 0
;LedSequencial.c,33 :: 		PORTA = 1;                // acende todos - teste
	MOVLW       1
	MOVWF       PORTA+0 
;LedSequencial.c,34 :: 		PORTB = 1;
	MOVLW       1
	MOVWF       PORTB+0 
;LedSequencial.c,35 :: 		PORTC = 1;
	MOVLW       1
	MOVWF       PORTC+0 
;LedSequencial.c,36 :: 		PORTD = 1;
	MOVLW       1
	MOVWF       PORTD+0 
;LedSequencial.c,37 :: 		PORTE = 1;
	MOVLW       1
	MOVWF       PORTE+0 
;LedSequencial.c,38 :: 		Delay_LED ();
	CALL        _Delay_LED+0, 0
;LedSequencial.c,39 :: 		PORTA = 0;                // apaga todos
	CLRF        PORTA+0 
;LedSequencial.c,40 :: 		PORTB = 0;
	CLRF        PORTB+0 
;LedSequencial.c,41 :: 		PORTC = 0;
	CLRF        PORTC+0 
;LedSequencial.c,42 :: 		PORTD = 0;
	CLRF        PORTD+0 
;LedSequencial.c,43 :: 		PORTE = 0;
	CLRF        PORTE+0 
;LedSequencial.c,44 :: 		Delay_LED ();
	CALL        _Delay_LED+0, 0
;LedSequencial.c,47 :: 		while (1)
L_main0:
;LedSequencial.c,50 :: 		PORTA.RA0 = 1;                // Ativa LED
	BSF         PORTA+0, 0 
;LedSequencial.c,51 :: 		Delay_LED ();                        // Aguarda tempo aceso
	CALL        _Delay_LED+0, 0
;LedSequencial.c,52 :: 		PORTA.RA0 = 0;                // apaga LED
	BCF         PORTA+0, 0 
;LedSequencial.c,53 :: 		PORTA.RA1 = 1;                // e repete ...
	BSF         PORTA+0, 1 
;LedSequencial.c,54 :: 		PORTA.RA0 = 0;                // apaga LED
	BCF         PORTA+0, 0 
;LedSequencial.c,55 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,56 :: 		PORTA.RA1 = 0;                //
	BCF         PORTA+0, 1 
;LedSequencial.c,57 :: 		PORTA.RA2 = 1;                // e repete ...
	BSF         PORTA+0, 2 
;LedSequencial.c,58 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,59 :: 		PORTA.RA2 = 0;                //
	BCF         PORTA+0, 2 
;LedSequencial.c,60 :: 		PORTA.RA3 = 1;                // e repete ...
	BSF         PORTA+0, 3 
;LedSequencial.c,61 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,62 :: 		PORTA.RA3 = 0;                //
	BCF         PORTA+0, 3 
;LedSequencial.c,63 :: 		PORTA.RA4 = 1;                // e repete ...
	BSF         PORTA+0, 4 
;LedSequencial.c,64 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,65 :: 		PORTA.RA4 = 0;                //
	BCF         PORTA+0, 4 
;LedSequencial.c,66 :: 		PORTA.RA5 = 1;                // e repete ...
	BSF         PORTA+0, 5 
;LedSequencial.c,67 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,68 :: 		PORTA.RA5 = 0;                //
	BCF         PORTA+0, 5 
;LedSequencial.c,70 :: 		PORTE.RE0 = 1;                // e repete ... PORT E
	BSF         PORTE+0, 0 
;LedSequencial.c,71 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,72 :: 		PORTE.RE0 = 0;                //
	BCF         PORTE+0, 0 
;LedSequencial.c,73 :: 		PORTE.RE1 = 1;                // e repete ...
	BSF         PORTE+0, 1 
;LedSequencial.c,74 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,75 :: 		PORTE.RE1 = 0;                //
	BCF         PORTE+0, 1 
;LedSequencial.c,76 :: 		PORTE.RE2 = 1;                // e repete ...
	BSF         PORTE+0, 2 
;LedSequencial.c,77 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,78 :: 		PORTE.RE2 = 0;                //
	BCF         PORTE+0, 2 
;LedSequencial.c,80 :: 		PORTC.RC0 = 1;                // e repete ... PORT C
	BSF         PORTC+0, 0 
;LedSequencial.c,81 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,82 :: 		PORTC.RC0 = 0;                //
	BCF         PORTC+0, 0 
;LedSequencial.c,83 :: 		PORTC.RC1 = 1;                // e repete ...
	BSF         PORTC+0, 1 
;LedSequencial.c,84 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,85 :: 		PORTC.RC1 = 0;                //
	BCF         PORTC+0, 1 
;LedSequencial.c,86 :: 		PORTC.RC2 = 1;                // e repete ...
	BSF         PORTC+0, 2 
;LedSequencial.c,87 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,88 :: 		PORTC.RC2 = 0;                //
	BCF         PORTC+0, 2 
;LedSequencial.c,89 :: 		PORTC.RC6 = 1;                // e repete ...
	BSF         PORTC+0, 6 
;LedSequencial.c,90 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,91 :: 		PORTC.RC6 = 0;                //
	BCF         PORTC+0, 6 
;LedSequencial.c,92 :: 		PORTC.RC7 = 1;                // e repete ...
	BSF         PORTC+0, 7 
;LedSequencial.c,93 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,94 :: 		PORTC.RC7 = 0;                //
	BCF         PORTC+0, 7 
;LedSequencial.c,96 :: 		PORTD.RD0 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 0 
;LedSequencial.c,97 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,98 :: 		PORTD.RD0 = 0;                //
	BCF         PORTD+0, 0 
;LedSequencial.c,99 :: 		PORTD.RD1 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 1 
;LedSequencial.c,100 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,101 :: 		PORTD.RD1 = 0;                //
	BCF         PORTD+0, 1 
;LedSequencial.c,102 :: 		PORTD.RD2 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 2 
;LedSequencial.c,103 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,104 :: 		PORTD.RD2 = 0;                //
	BCF         PORTD+0, 2 
;LedSequencial.c,105 :: 		PORTD.RD3 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 3 
;LedSequencial.c,106 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,107 :: 		PORTD.RD3 = 0;                //
	BCF         PORTD+0, 3 
;LedSequencial.c,108 :: 		PORTD.RD4 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 4 
;LedSequencial.c,109 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,110 :: 		PORTD.RD4 = 0;                //
	BCF         PORTD+0, 4 
;LedSequencial.c,111 :: 		PORTD.RD5 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 5 
;LedSequencial.c,112 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,113 :: 		PORTD.RD5 = 0;                //
	BCF         PORTD+0, 5 
;LedSequencial.c,114 :: 		PORTD.RD6 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 6 
;LedSequencial.c,115 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,116 :: 		PORTD.RD6 = 0;                //
	BCF         PORTD+0, 6 
;LedSequencial.c,117 :: 		PORTD.RD7 = 1;                // e repete ... PORT D
	BSF         PORTD+0, 7 
;LedSequencial.c,118 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,119 :: 		PORTD.RD7 = 0;                //
	BCF         PORTD+0, 7 
;LedSequencial.c,121 :: 		PORTB.RB0 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 0 
;LedSequencial.c,122 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,123 :: 		PORTB.RB0 = 0;                //
	BCF         PORTB+0, 0 
;LedSequencial.c,124 :: 		PORTB.RB1 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 1 
;LedSequencial.c,125 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,126 :: 		PORTB.RB1 = 0;                //
	BCF         PORTB+0, 1 
;LedSequencial.c,127 :: 		PORTB.RB2 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 2 
;LedSequencial.c,128 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,129 :: 		PORTB.RB2 = 0;                //
	BCF         PORTB+0, 2 
;LedSequencial.c,130 :: 		PORTB.RB3 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 3 
;LedSequencial.c,131 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,132 :: 		PORTB.RB3 = 0;                //
	BCF         PORTB+0, 3 
;LedSequencial.c,133 :: 		PORTB.RB4 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 4 
;LedSequencial.c,134 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,135 :: 		PORTB.RB4 = 0;                //
	BCF         PORTB+0, 4 
;LedSequencial.c,136 :: 		PORTB.RB5 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 5 
;LedSequencial.c,137 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,138 :: 		PORTB.RB5 = 0;                //
	BCF         PORTB+0, 5 
;LedSequencial.c,139 :: 		PORTB.RB6 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 6 
;LedSequencial.c,140 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,141 :: 		PORTB.RB6 = 0;                //
	BCF         PORTB+0, 6 
;LedSequencial.c,142 :: 		PORTB.RB7 = 1;                // e repete ... PORT B
	BSF         PORTB+0, 7 
;LedSequencial.c,143 :: 		Delay_LED ();                        //
	CALL        _Delay_LED+0, 0
;LedSequencial.c,144 :: 		PORTB.RB7 = 0;                //
	BCF         PORTB+0, 7 
;LedSequencial.c,146 :: 		}
	GOTO        L_main0
;LedSequencial.c,149 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_Delay_LED:

;LedSequencial.c,151 :: 		void Delay_LED (void)
;LedSequencial.c,153 :: 		Delay_ms (40);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       4
	MOVWF       R12, 0
	MOVLW       186
	MOVWF       R13, 0
L_Delay_LED2:
	DECFSZ      R13, 1, 1
	BRA         L_Delay_LED2
	DECFSZ      R12, 1, 1
	BRA         L_Delay_LED2
	DECFSZ      R11, 1, 1
	BRA         L_Delay_LED2
	NOP
;LedSequencial.c,154 :: 		}
L_end_Delay_LED:
	RETURN      0
; end of _Delay_LED

_Board_Init:

;LedSequencial.c,156 :: 		void Board_Init (void)
;LedSequencial.c,158 :: 		RCON = 0X80;                                // LIMPA REGISTRO DE RESET
	MOVLW       128
	MOVWF       RCON+0 
;LedSequencial.c,159 :: 		ADCON1 = 0x0F;                                // CONFIGURA TODAS AS PORTAS ANALOGICAS COMO I/O
	MOVLW       15
	MOVWF       ADCON1+0 
;LedSequencial.c,161 :: 		CMCON = 0x0F;                                // DESABILITA COMPARADOR
	MOVLW       15
	MOVWF       CMCON+0 
;LedSequencial.c,163 :: 		T0CON = 0b11000101;                        // timer ativo, 8 bits,clock interno, preescale 1:64
	MOVLW       197
	MOVWF       T0CON+0 
;LedSequencial.c,165 :: 		TRISA = 0;
	CLRF        TRISA+0 
;LedSequencial.c,166 :: 		TRISB = 0;                        // todos Saida
	CLRF        TRISB+0 
;LedSequencial.c,167 :: 		TRISC = 0;
	CLRF        TRISC+0 
;LedSequencial.c,168 :: 		TRISD = 0;
	CLRF        TRISD+0 
;LedSequencial.c,169 :: 		TRISE = 0;
	CLRF        TRISE+0 
;LedSequencial.c,171 :: 		}
L_end_Board_Init:
	RETURN      0
; end of _Board_Init
