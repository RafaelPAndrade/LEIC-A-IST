; Programa aula4.as

; ZONA I: Definicao de constantes
;        Pseudo-instrucao : EQU
CR              EQU     0Ah
FIM_TEXTO       EQU     '@'
IO_READ         EQU     FFFFh
IO_WRITE        EQU     FFFEh
IO_STATUS       EQU     FFFDh
SP_INICIAL      EQU     FDFFh


; ZONA II: definicao de variaveis
;         Pseudo-instrucoes : WORD - palavra (16 bits)
;                             STR  - sequencia de caracteres.
;         Cada caracter ocupa 1 palavra
                ORIG    8000h
VarTexto1       STR     'Pressione uma tecla entre 0 e 9: ', FIM_TEXTO
VarTexto2       STR     'Numero de bits a 1 = ', FIM_TEXTO
VarErro1        STR     'ERRO: Tecla Invalida', FIM_TEXTO



; ZONA III: codigo
;        conjunto de instrucoes Assembly, ordenadas de forma a realizar
;        as funcoes pretendidas

                ORIG    0000h
                JMP     Inicio

; LeCar: Rotina que efectua a leitura de um caracter proveniente do teclado.
;               Entradas: ---
;               Saidas: R1 - caracter lido
;               Efeitos: alteracao do registo R1

LeCar:          CMP     R0, M[IO_STATUS]
                BR.Z    LeCar
                MOV     R1, M[IO_READ]
                RET


; EscCar: Rotina que efectua a escrita de um caracter para o ecra.
;       O caracter pode ser visualizado na janela de texto.
;               Entradas: pilha - caracter a escrever
;               Saidas: ---
;                       Efeitos: alteracao do registo R1
;                       alteracao da posicao de memoria M[IO]

EscCar:         PUSH    R1
                MOV     R1, M[SP+3]
                MOV     M[IO_WRITE], R1
                POP     R1
                RETN    1


; MudaLinha: Rotina que efectua a escrita de um caracter de mudanca de linha.
;               Entradas: ---
;               Saidas: ---
;               Efeitos: ---

MudaLinha:      PUSH    R1
                PUSH    CR
                CALL    EscCar
                POP     R1
                RET


; EscString: Rotina que efectua a escrita de uma cadeia de caracter, terminada
;          pelo caracter FIM_TEXTO. Pode-se definir como terminador qualquer
;          caracter ASCII.
;               Entradas: R2 - apontador para o inicio da cadeia de caracteres
;               Saidas: ---
;               Efeitos: ---

EscString:      PUSH    R1
                PUSH    R2
Ciclo:          MOV     R1, M[R2]
                CMP     R1, FIM_TEXTO
                BR.Z    FimEsc
                PUSH    R1
                CALL    EscCar
                INC     R2
                BR      Ciclo
FimEsc:         POP     R2
                POP     R1
                RET

; EscNum: Rotina que efectua a escrita de um algarismo, fazendo a conversao
;         necessaria para ASCII.
;               Entradas: R1 - numero a escrever
;               Saidas: ---
;               Efeitos: ---

EscNum:         PUSH    R1
                ADD     R1,'0'
                PUSH    R1
                CALL    EscCar
                POP     R1
                RET


; PrintBits: Rotina que efectua a escrita da representacao em binario no ecra
;               de uma palavra de 16 bits.
;               Entradas: R1 palavra a imprimir
;               Saidas: ---
;               Efeitos: ---
PrintBits:      PUSH    R1
                PUSH    R2
                PUSH    R3
                PUSH    ' '
                CALL    EscCar
                PUSH    '('
                CALL    EscCar
                MOV     R2, 15
procbit:        SHL     R1, 1
                MOV     R3, '0'
                ADDC    R3, R0
                PUSH    R3
                CALL    EscCar
                DEC     R2
                BR.NN   procbit
                PUSH    ')'
                CALL    EscCar
                POP     R3
                POP     R2
                POP     R1
                RET


; CountBits: Rotina de calculo do numero de bits a '1' numa palavra de 16 bits.
;               Entradas: R1 - palavra a processar
;               Saidas: R1 - resultado
;               Efeitos: altera R2

CountBits:      MOV	R1, M[SP+2]
		MOV     R2, R0
continua:       SHR     R1, 1
                ADDC    R2, R0
                CMP     R1, R0
                BR.NZ   continua
                MOV     M[SP+2], R2
                RET


; Programa Principal: programa que recebe um algarismo do teclado,
;       retornando o numero de bits a '1' da correspondente representacao
;       em binario. Caso receba um caracter invalido, retorna uma
;       mensagem de erro.

Inicio:         MOV     R7, SP_INICIAL
                MOV     SP, R7

ProcWord:       CALL    MudaLinha
                MOV     R2, VarTexto1
                CALL    EscString
                CALL    LeCar           ; Devolve em R1 o caracter lido (simbolo ASCII)
                SUB     R1,'0'          ; Conversao do simbolo ASCII

                CMP     R1,0            ; Deteccao de condicao de erro
                BR.N    Erro
                CMP     R1,9
                BR.P    Erro

                CALL    EscNum          ; Escrita do numero lido (R1)

                CALL    PrintBits       ; Escrita da representacao em binario
		                        ; do numero lido
                CALL    MudaLinha

		PUSH	R1
                CALL    CountBits       ; Contagem do numero de bits a '1'
		POP	R1

                MOV     R2, VarTexto2   ; Escrita do valor calculado no ecra
                CALL    EscString
                CALL    EscNum

                CALL    MudaLinha
                JMP     ProcWord

Erro:           CALL    MudaLinha
                MOV     R2, VarErro1
                CALL    EscString
                JMP     ProcWord

Fim:            BR      Fim
