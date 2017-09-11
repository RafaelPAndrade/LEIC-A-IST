;     Programa aula5.as

SP_INICIAL      EQU     FDFFh
INT_MASK_ADDR   EQU     FFFAh
INT_MASK        EQU     0000000000000001b
IO_DISPLAY      EQU     FFF0h
DELAY_COUNT     EQU     0200h
NIBBLE_MASK     EQU     000fh
NUM_NIBBLES     EQU     4
BITS_PER_NIBBLE EQU     4

; Palavra de memoria que contem a variavel de contagem
                ORIG    8000h
Contador        WORD    0000h


; Tabela de interrupcoes
                ORIG    FE00h
INT0            WORD    ResetCont


; Codigo
                ORIG    0000h
                JMP     Inicio

; ResetCont: Rotina que faz o reset do contador
;       Entradas: --- 
;       Saidas: --- 
;       Efeitos: alteracao do conteudo da posicao de memoria M[Contador]
ResetCont:      MOV     M[Contador], R0
                RTI

; ContHex: Rotina que incrementa o contador
;       Entradas: M[Contador] - contador
;       Saidas: --- 
;       Efeitos: alteracao do conteudo da posicao de memoria  M[Contador] 
ContHex:        INC     M[Contador]
                RET

; EscCont: Rotina que efectua a escrita do contador
;       Entradas: ---
;       Saidas: ---
;       Efeitos: ---
EscCont:        PUSH    R1
                PUSH    R2
                PUSH    R3
                DSI
                MOV     R2, NUM_NIBBLES
                MOV     R3, IO_DISPLAY
Ciclo:          MOV     R1, M[Contador]
                AND     R1, NIBBLE_MASK
                MOV     M[R3], R1
                ROR     M[Contador], BITS_PER_NIBBLE
                INC     R3
                DEC     R2
                BR.NZ   Ciclo
                ENI
                POP     R3
                POP     R2
                POP     R1
                RET

; Delay: Rotina que provoca um atraso
;       Entradas: ---
;       Saidas: ----
;       Efeitos: ---
Delay:          PUSH    R1
                MOV     R1, DELAY_COUNT
Delay_L1:       DEC     R1
                BR.NZ   Delay_L1
                POP     R1
                RET

Inicio:         MOV     R7, SP_INICIAL
                MOV     SP, R7
                MOV     R7, INT_MASK
                MOV     M[INT_MASK_ADDR], R7
                ENI
CicloCont:      CALL    EscCont
                CALL    Delay
                CALL    ContHex
                BR      CicloCont
