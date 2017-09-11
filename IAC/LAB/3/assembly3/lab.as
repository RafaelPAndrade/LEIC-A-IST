;2.3 da 3a ficha de lab
;Rafael Pestana de Andrade feat. Diogo Ramalho



	ORIG	8000h ;sítio onde vou guardar dados
Dados	STR	F0F1h
NumBits	TAB	1


	ORIG	0000h
start:	MOV	R1,M[Dados]
	MOV	R3,R0
	MOV	R5,R0

shift:	CLC
	SHL	R1,1
	JMP.C	add1	 ;se houver carry,ponho 1 nessa entrada de memória
	JMP	next

add1:	INC	R5
	JMP	next

next:	CMP	R3,15	;siga ver se já fiz isto 16(15+0) vezes
	JMP.Z	fim
	INC	R3
	JMP	shift

fim:	MOV	M[NumBits],R5
halt:	JMP	halt

