;LAB 5, IAC, 2016/17, LEIC-Al

;Rafael PAndrade, 86503


;Constantes
S1		EQU	8000h	;Endereço de memória que contém os segundos	
S2		EQU	8001h	;dezenas de segundo
M1		EQU	8002h	;unidades de minuto
M2		EQU	8003h	;dezenas de minutos


MASCARA		EQU	8001h	;mascara de interrupçoes
RECETOR_MAS	EQU	FFFAh	;respetivo recetor
DISPLAY		EQU	FFF0h	;endereço de memoria do display de 7 segmentos, até FFF0h
LEDS		EQU	FFF8h	;endereço de memoria dos leds
SP_INICIAL      EQU     FDFFh	;Stack tem de ser inicializado (RET e RTI)

TEMPO_UN	EQU	000ah	;Nº 100's de milisegundos por interrupt
TEMPO_EN	EQU	FFF6h	;Endereço do relógio
TEMPO_ON	EQU	FFF7h	;Relógio on se bit - significativo =1

;Tabela de Interrupções
		ORIG	FE00h
INT0		WORD	ticktack

		ORIG	FE0fh
INT15		WORD	ticktack


ticktack:	INC	M[S1]	;Aumenta um segundo
		RTI


;formataçao decimal em mod 60, não formata M2;
;deve ser em seguida chamada a rotina escrita
;registos usados:5,6

format:		NOP
u_segundo:	CMP	R5, M[S1]
		JMP.P	saida
		MOV	M[S1], R0
		INC	M[S2]
d_segundo:	CMP	R6, M[S2]
		JMP.P	saida
		MOV	M[S2],R0
		INC	M[M1]
u_minuto:	CMP	R5, M[M1]
		JMP.P	saida
		MOV	M[M1],R0
		INC	M[M2]
saida:		RET


;Escrita para os displays de 7 segmentos
;registos usados:1-4

escrita:	MOV	R1,DISPLAY
		MOV	R2,S1
		MOV	R4,4
escrevendo:	MOV	R3,M[R2]
		MOV	M[R1],R3
		INC	R1
		INC	R2
		DEC	R4
		BR.NN	escrevendo
		NOP
		RET



		ORIG	0000h
inicio:		MOV	R7, SP_INICIAL	;inicio da stack
		MOV	SP, R7

		MOV	R7, MASCARA	;inicio da mascara
		MOV	M[RECETOR_MAS], R7


		MOV	R5, 000ah	;unidades para a formatação
		MOV	R6, 6

relogio:	MOV	R7, TEMPO_UN	;set do timer a 1s
		MOV	M[TEMPO_EN], R7
		MOV	R7,0001h
		MOV	M[TEMPO_ON], R7	;começa o relogio
		ENI

espera:		NOP
		CMP	M[TEMPO_EN],R0	;quando a interrupção é despoletada, é preciso voltar
		BR.Z	relogio		;a reiniciar o relógio-bug
		CALL	format
		CALL	escrita
		BR	espera




