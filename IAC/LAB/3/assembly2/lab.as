;Rafael Pestana de Andrade
;2a opção
;Descompactação da sequência


Um	EQU	1


	ORIG	8000h ;sítio onde vou guardar dados
Dados	STR	F0F1h
Destino	TAB	16

	ORIG	0000h
start:	MOV	R1,M[Dados]
	MOV	R2,Destino
	MOV	R3,R0
	MOV	R7,Um

shift:	CLC
	SHL	R1,1
	JMP.C	add1	 ;se houver carry,ponho 1 nessa entrada de memória
	MOV	M[R2],R0 ;else, ponho 0
	JMP	next

add1:	MOV	M[R2],R7
	JMP	next

next:	CMP	R3,15	;siga ver se já fiz isto 16(15+0) vezes
	JMP.Z	fim
	INC	R2
	INC	R3
	JMP	shift

fim:	BR	fim

