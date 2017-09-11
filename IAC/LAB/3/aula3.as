; Programa aula3.as
; NOTA: Este programa nao esta' comentado INTENCIONALMENTE !!

FIM_STR         EQU     '@'

                ORIG    8000h
VarStrOrigem    STR     'Arquitectura de Computadores @'
VarStrDestino   TAB     30

                ORIG    0000h
Inicio:         MOV     R1, VarStrDestino
                MOV     R2, VarStrOrigem
Ciclo:          MOV     R3, M[R2]
                CMP     R3, FIM_STR
                BR.Z    Meio
                MOV     M[R1], R0
                INC     R1
                INC     R2
                BR      Ciclo

Meio:           MOV     R3, M[R2]
                MOV     M[R1], R3
                DEC     R2
                DEC     R1
                CMP     R1, VarStrDestino
                BR.NN   Meio
Fim:            BR      Fim



