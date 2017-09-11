;Rafael Pestana de Andrade
;lab1 de assembly
;Nota: a demarcação feita do espaço de memória/espaço de programa é
;completamente arbitrária (acho eu)
;por uma questão de predefinição do simulador, usar:
;	-8000h
;	-fd00h



;progr 1: Soma de 2 números de 32 bits

Num	EQU	2 ;adaptação para poder extender para números maiores

;Espaço de memória:8800h até FF00h(à programador)

	ORIG	8000h
Num1	STR	1111h,1110h ;Num1=8800h
;corresponde ao número 11101111h
Num2	STR	2222h,2220h ;Num2=8802h
;corresponde ao número 22202222h
Res	TAB	Num


;Espaço do programa: 0000h até 8800h
	ORIG	0000h
;1º-Ter referências para Num1, Num2, Res-"Indices..."
inicio:	MOV	R1,Num1	;Indice numero1
	MOV	R2,Num2	;Indice numero2
	MOV	R7,Res	;Indice	resultado
	MOV	R6,R0

soma:	MOV	R3,M[R1]
	MOV	R4,M[R2]
	ADDC	R3,R4
	MOV	M[R7],R3
	INC	R1
	INC	R2
	INC	R7
	INC	R6

Verify:	CMP	R6,Num
	JMP.NZ	soma

Fim:	BR	Fim
;vá se lá saber porquê, adora-se pôr loops no final
;mas evita overwrite de valores
		
