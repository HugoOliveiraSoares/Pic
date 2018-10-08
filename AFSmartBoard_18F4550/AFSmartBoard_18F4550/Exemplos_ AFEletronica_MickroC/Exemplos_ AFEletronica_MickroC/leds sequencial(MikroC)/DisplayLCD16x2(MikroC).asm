
_main:

;DisplayLCD16x2(MikroC).c,62 :: 		void main (void) org 0x1000
;DisplayLCD16x2(MikroC).c,65 :: 		AFSmartBoard_Init();                // inicia placa
	CALL        _AFSmartBoard_Init+0, 0
;DisplayLCD16x2(MikroC).c,67 :: 		lcd_init ( );
	CALL        _Lcd_Init+0, 0
;DisplayLCD16x2(MikroC).c,68 :: 		lcd_cmd (_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;DisplayLCD16x2(MikroC).c,69 :: 		lcd_cmd (_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;DisplayLCD16x2(MikroC).c,73 :: 		AFSmartBoard_str (1,1, MsgWelcome3 );
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _MsgWelcome3+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_MsgWelcome3+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;DisplayLCD16x2(MikroC).c,74 :: 		DELAY_MS (500);
	MOVLW       13
	MOVWF       R11, 0
	MOVLW       175
	MOVWF       R12, 0
	MOVLW       182
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
	NOP
;DisplayLCD16x2(MikroC).c,75 :: 		AFSmartBoard_str (2,1, MsgWelcome4 ) ;
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _MsgWelcome4+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_MsgWelcome4+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;DisplayLCD16x2(MikroC).c,76 :: 		Delay_ms (500);
	MOVLW       13
	MOVWF       R11, 0
	MOVLW       175
	MOVWF       R12, 0
	MOVLW       182
	MOVWF       R13, 0
L_main3:
	DECFSZ      R13, 1, 1
	BRA         L_main3
	DECFSZ      R12, 1, 1
	BRA         L_main3
	DECFSZ      R11, 1, 1
	BRA         L_main3
	NOP
;DisplayLCD16x2(MikroC).c,77 :: 		LCD_cmd (_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;DisplayLCD16x2(MikroC).c,79 :: 		AFSmartBoard_str (1,1, MsgWelcome1 );
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _MsgWelcome1+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_MsgWelcome1+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;DisplayLCD16x2(MikroC).c,80 :: 		DELAY_MS (500);
	MOVLW       13
	MOVWF       R11, 0
	MOVLW       175
	MOVWF       R12, 0
	MOVLW       182
	MOVWF       R13, 0
L_main4:
	DECFSZ      R13, 1, 1
	BRA         L_main4
	DECFSZ      R12, 1, 1
	BRA         L_main4
	DECFSZ      R11, 1, 1
	BRA         L_main4
	NOP
;DisplayLCD16x2(MikroC).c,81 :: 		AFSmartBoard_str (2,1, MsgWelcome2 ) ;
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _MsgWelcome2+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_MsgWelcome2+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;DisplayLCD16x2(MikroC).c,82 :: 		Delay_ms (500);
	MOVLW       13
	MOVWF       R11, 0
	MOVLW       175
	MOVWF       R12, 0
	MOVLW       182
	MOVWF       R13, 0
L_main5:
	DECFSZ      R13, 1, 1
	BRA         L_main5
	DECFSZ      R12, 1, 1
	BRA         L_main5
	DECFSZ      R11, 1, 1
	BRA         L_main5
	NOP
;DisplayLCD16x2(MikroC).c,86 :: 		PORTA.RA4 = 1;
	BSF         PORTA+0, 4 
;DisplayLCD16x2(MikroC).c,88 :: 		for (i=0;i<15;i++)
	CLRF        _i+0 
	CLRF        _i+1 
L_main6:
	MOVLW       128
	XORWF       _i+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main14
	MOVLW       15
	SUBWF       _i+0, 0 
L__main14:
	BTFSC       STATUS+0, 0 
	GOTO        L_main7
;DisplayLCD16x2(MikroC).c,91 :: 		PORTA.RA4 ^= 1;
	BTG         PORTA+0, 4 
;DisplayLCD16x2(MikroC).c,92 :: 		PORTA.RA5 ^= 1;
	BTG         PORTA+0, 5 
;DisplayLCD16x2(MikroC).c,93 :: 		Delay_ms (120);
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       12
	MOVWF       R12, 0
	MOVLW       51
	MOVWF       R13, 0
L_main9:
	DECFSZ      R13, 1, 1
	BRA         L_main9
	DECFSZ      R12, 1, 1
	BRA         L_main9
	DECFSZ      R11, 1, 1
	BRA         L_main9
	NOP
	NOP
;DisplayLCD16x2(MikroC).c,88 :: 		for (i=0;i<15;i++)
	INFSNZ      _i+0, 1 
	INCF        _i+1, 1 
;DisplayLCD16x2(MikroC).c,94 :: 		}
	GOTO        L_main6
L_main7:
;DisplayLCD16x2(MikroC).c,96 :: 		while (1)
L_main10:
;DisplayLCD16x2(MikroC).c,99 :: 		PORTA.RA4 ^= 1;
	BTG         PORTA+0, 4 
;DisplayLCD16x2(MikroC).c,100 :: 		PORTA.RA5 ^= 1;
	BTG         PORTA+0, 5 
;DisplayLCD16x2(MikroC).c,101 :: 		Delay_ms (120);
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       12
	MOVWF       R12, 0
	MOVLW       51
	MOVWF       R13, 0
L_main12:
	DECFSZ      R13, 1, 1
	BRA         L_main12
	DECFSZ      R12, 1, 1
	BRA         L_main12
	DECFSZ      R11, 1, 1
	BRA         L_main12
	NOP
	NOP
;DisplayLCD16x2(MikroC).c,103 :: 		}
	GOTO        L_main10
;DisplayLCD16x2(MikroC).c,108 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_AFSmartBoard_Init:

;DisplayLCD16x2(MikroC).c,110 :: 		void AFSmartBoard_Init (void)
;DisplayLCD16x2(MikroC).c,112 :: 		RCON = 0X80;                                // LIMPA REGISTRO DE RESET
	MOVLW       128
	MOVWF       RCON+0 
;DisplayLCD16x2(MikroC).c,113 :: 		ADCON1 = 0x0F;                                // CONFIGURA TODAS AS PORTAS ANALOGICAS COMO I/O
	MOVLW       15
	MOVWF       ADCON1+0 
;DisplayLCD16x2(MikroC).c,115 :: 		CMCON = 0x0F;                                // DESABILITA COMPARADOR
	MOVLW       15
	MOVWF       CMCON+0 
;DisplayLCD16x2(MikroC).c,117 :: 		T0CON = 0b11000101;                        // timer ativo, 8 bits,clock interno, preescale 1:64
	MOVLW       197
	MOVWF       T0CON+0 
;DisplayLCD16x2(MikroC).c,119 :: 		TRISA = 0;
	CLRF        TRISA+0 
;DisplayLCD16x2(MikroC).c,120 :: 		TRISB = 0;                        // todos Saida
	CLRF        TRISB+0 
;DisplayLCD16x2(MikroC).c,121 :: 		TRISC = 0;
	CLRF        TRISC+0 
;DisplayLCD16x2(MikroC).c,122 :: 		TRISD = 0;
	CLRF        TRISD+0 
;DisplayLCD16x2(MikroC).c,123 :: 		TRISE = 0;
	CLRF        TRISE+0 
;DisplayLCD16x2(MikroC).c,125 :: 		PORTA = 0;                                // nível 0 saída
	CLRF        PORTA+0 
;DisplayLCD16x2(MikroC).c,126 :: 		PORTB = 0;
	CLRF        PORTB+0 
;DisplayLCD16x2(MikroC).c,127 :: 		PORTC = 0;
	CLRF        PORTC+0 
;DisplayLCD16x2(MikroC).c,128 :: 		PORTD = 0;
	CLRF        PORTD+0 
;DisplayLCD16x2(MikroC).c,129 :: 		PORTE = 0;
	CLRF        PORTE+0 
;DisplayLCD16x2(MikroC).c,132 :: 		}
L_end_AFSmartBoard_Init:
	RETURN      0
; end of _AFSmartBoard_Init
