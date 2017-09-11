/********************************************************************\
|Projeto de LP: Sudoku solver
|
|Rafael P. Andrade
|n. 86503
|LEIC-A 2017
\********************************************************************/

:- include('SUDOKU').

/*************************************\
|Prologo
|
|Predicados auxiliares
\*************************************/

%---------------------------------------------------------------------
%tira_nao_unitarios(Lst, N_Lst)

%Lst:   Lista de listas inicial
%N_Lst: Lista de listas resultante de retirar a Lst todas as listas
%       cujo tamanho e' diferente de 1 (nao unitarias).

%Predicados usados: 
%	-\+/1                    (sistema Prolog)
%	-length/2                (sistema Prolog)
%---------------------------------------------------------------------


tira_nao_unitarios([], []):-!.

tira_nao_unitarios([P|R], [P|R1]):-
	length(P,1), !,
	tira_nao_unitarios(R, R1).

tira_nao_unitarios([_|R], R1):-
	tira_nao_unitarios(R, R1).



/*************************************\
|1a parte
|
|Predicados de propagacao de mudancas
\*************************************/


%---------------------------------------------------------------------
%tira_num_aux(Num, Puz, Pos, N_Puz)

%Num:   (possivel) elemento de celula de sudoku
%Puz:   O puzzle em causa
%Pos:   Posicao em causa
%N_Puz: O puzzle resultante de retirar <Num> a <Puz> em <Pos>

%Predicados usados: 
%	-puzzle_ref/3            (SUDOKU.pl)
%	-memberchk/3             (sistema Prolog)
%	-\+/1                    (sistema Prolog)
%	-subtract/3              (sistema Prolog)
%	-puzzle_muda_propaga/4   (ficheiro local)
%---------------------------------------------------------------------

%Se <Num> nao pertencer aos conteudos de <Pos>, nao muda nada.
tira_num_aux(Num, Puz, Pos, Puz):-
	puzzle_ref(Puz, Pos, Cont),
	\+ memberchk(Num, Cont), !.
	

tira_num_aux(Num, Puz, Pos, N_Puz):- 
	puzzle_ref(Puz, Pos, Cont),
	subtract(Cont, [Num], Res),
	puzzle_muda_propaga(Puz, Pos, Res, N_Puz).

%---------------------------------------------------------------------
%tira_num(Num, Puz, Pos, N_Puz)

%Num:       (possivel) elemento de celula de sudoku
%Puz:       O puzzle em causa
%Posicoes:  Lista de posicoes em causa
%N_Puz:     O puzzle resultante de retirar <Num> a todas as <Pos>

%Predicados usados:
%	-percorre_muda_Puz/4     (SUDOKU.pl)
%	-tira_num_aux/3          (ficheiro local)	
%---------------------------------------------------------------------


tira_num(Num, Puz, Posicoes, N_Puz):-
	percorre_muda_Puz(Puz, tira_num_aux(Num), Posicoes, N_Puz).


%---------------------------------------------------------------------
%puzzle_muda_propaga(Puz, Pos, Cont, N_Puz)

%Puz:   O puzzle em causa
%Pos:   Posicao em causa
%Cont:  Lista com o conteudo a colocar na celula
%N_Puz: O puzzle resultante de colocar <Cont> em <Pos>
%       Se <Cont> for uma lista unitaria, retira esse numero a 
%       celulas que estao em linha, coluna e bloco

%Predicados usados: 
%	-puzzle_muda/3           (SUDOKU.pl)
%	-posicoes_relacionadas/2 (SUDOKU.pl)
%	-tira_num/4              (ficheiro local)
%---------------------------------------------------------------------


puzzle_muda_propaga(Puz, Pos, [Num], N_Puz):-
	puzzle_muda(Puz, Pos, [Num], Aux_Puz),
	posicoes_relacionadas(Pos, Aux_Posicoes),
	tira_num(Num, Aux_Puz, Aux_Posicoes, N_Puz),!.


puzzle_muda_propaga(Puz, Pos, Cont, N_Puz):-
	puzzle_muda(Puz, Pos, Cont, N_Puz).


/**************************************\
|2a parte
|
|Predicados de inicializacao de puzzles
\**************************************/

%---------------------------------------------------------------------
%possibilidades(Pos, Puz, Poss)

%Pos:   A posicao em causa
%Puz:   O puzzle em causa
%Poss:  A lista de numeros possiveis para a posicao <Pos>.

%Nota:  Este predicado pode ser utilizado num puzzle 
%       com posicoes (diferentes de <Pos>) em que tenham sido postas 
%       as suas possibilidades.

%Predicados usados:
%	-numeros/1               (SUDOKU.pl)
%	-posicoes_relacionadas/2 (SUDOKU.pl)
%	-conteudos_posicoes/3    (SUDOKU.pl)
%	-tira_nao_unitarios/2    (ficheiro local)
%	-append/2                (sistema Prolog)
%	-subtract/2              (sistema Prolog)
%---------------------------------------------------------------------

possibilidades(Pos, Puz, Poss):-
	numeros(Aux_Poss),
		
	posicoes_relacionadas(Pos, Posicoes),
	conteudos_posicoes(Puz, Posicoes, Aux_Cont),
	%filtra os conteudos das posicoes relacionadas, para apenas
	%considerar posicoes efetivamente ocupadas
	tira_nao_unitarios(Aux_Cont, Aux2_Cont),
	append(Aux2_Cont, Cont_Posicoes),

	subtract(Aux_Poss, Cont_Posicoes, Poss).
		

%---------------------------------------------------------------------
%inicializa_aux(Puz, Pos, N_Puz)

%Puz:   O puzzle em causa
%Pos:   A posicao em causa
%N_Puz: O puzzle resultante de colocar as possibilidades de <Pos> na
%       propria posicao <Pos>

%Predicados usados:
%	-puzzle_ref/3            (SUDOKU.pl)
%	-length/2                (sistema Prolog)
%	-possibilidades/3        (ficheiro local)
%	-puzzle_muda_propaga/4   (ficheiro local)
%---------------------------------------------------------------------

%Se <Pos> ja tiver apenas 1 numero, nao altera nada
inicializa_aux(Puz, Pos, Puz):-
	puzzle_ref(Puz, Pos, Cont),
	length(Cont,1),!.	
	
inicializa_aux(Puz, Pos, N_Puz):-
	possibilidades(Pos, Puz, Poss),
	puzzle_muda_propaga(Puz, Pos, Poss, N_Puz).
	

%---------------------------------------------------------------------
%inicializa(Puz, N_Puz)

%Puz:   O puzzle em causa, no seu estado inicial
%N_Puz: O puzzle resultante da inicializacao de <Puz> em todas as
%       posicoes

%Predicados usados:
%	-todas_posicoes/1        (SUDOKU.pl)
%	-percorre_muda_Puz/4     (SUDOKU.pl)
%	-inicializa_aux/3        (ficheiro local)	
%---------------------------------------------------------------------


inicializa(Puz, N_Puz):-
	todas_posicoes(Posicoes),
	percorre_muda_Puz(Puz, inicializa_aux, Posicoes, N_Puz).


/*************************************\
|3a parte
|
|Predicados de inspecao de puzzles
\*************************************/


%---------------------------------------------------------------------
%so_aparece_uma_vez(Puz, Num, Posicoes, Pos_Num)

%Puz:       O puzzle em causa
%Num:       Numero que se procura
%Posicoes:  Lista de posicoes, onde apenas uma contem <Num>
%Pos_Num:   A unica posicao pertencente a <Posicoes> que contem <Num>

%Predicados usados:
%	-puzzle_ref/3            (SUDOKU.pl)
%	-memberchk/2             (sistema Prolog) 
%	-conteudos_posicoes/3    (SUDOKU.pl)
%	-append/2                (sistema Prolog)
%	-\+/1                    (sistema Prolog)
%---------------------------------------------------------------------


so_aparece_uma_vez(Puz, Num, [Pos_Num|R], Pos_Num):-
	%A primeira posicao das listas contem o numero
	puzzle_ref(Puz, Pos_Num, Cont_Pos_Num),
	memberchk(Num, Cont_Pos_Num), !,


	%<Num> nao pertence 'as outras posicoes
	conteudos_posicoes(Puz, R, Outros_Conteudos),
	append(Outros_Conteudos, Lst_Outros_Conteudos),
	\+ memberchk(Num, Lst_Outros_Conteudos) .
	

so_aparece_uma_vez(Puz, Num, [_|R], Pos_Num):-
	%Descarta a primeira posicao, nao contem Num
	so_aparece_uma_vez(Puz, Num, R, Pos_Num).


%---------------------------------------------------------------------
%inspeciona_num(Posicoes, Puz, Num, N_Puz)

%Posicoes:  Lista de posicoes
%Puz:       O puzzle em causa
%Num:       Numero alvo de inspecao
%N_Puz:     O puzzle resultante de verificar que <Num> esta'
%           apenas numa das posicoes de <Posicoes>; se sim, coloca-se 
%           <Num> nessa casa, e retira-se das outras posicoes(propaga)

%Predicados usados:
%	-so_aparece_uma_vez/4   (ficheiro local)
%	-puzzle_ref/3           (SUDOKU.pl)
%	-\+/1                   (sistema Prolog)
%	-length/2               (sistema Prolog)
%	-puzzle_muda_propaga/4  (ficheiro local)

%---------------------------------------------------------------------

inspecciona_num(Posicoes, Puz, Num, N_Puz):-
	so_aparece_uma_vez(Puz, Num, Posicoes, Pos_Num),
	puzzle_ref(Puz, Pos_Num, Cont),
	\+ length(Cont,1), !,
	puzzle_muda_propaga(Puz, Pos_Num, [Num], N_Puz).
	
inspecciona_num(_, Puz, _, Puz).



%---------------------------------------------------------------------
%inspecciona_grupo(Puz, Gr, N_Puz)

%Puz:   O puzzle em causa
%Gr:    Lista de posicoes, potencialmente um grupo
%N_Puz: O puzzle resultante de inspeccionar todos os numeros
%       possiveis a todas as casa de <Gr>
			

%Predicados usados:
%	-numeros/1               (SUDOKU.pl)
%	-inspecciona_num/4       (ficheiro local)
%---------------------------------------------------------------------


inspecciona_grupo(Puz, Gr, N_Puz):-
	numeros(Num_Lst),
	inspecciona_grupo_aux(Puz, Gr, Num_Lst, N_Puz).


inspecciona_grupo_aux(Puz, _, [], Puz):-!.

inspecciona_grupo_aux(Puz, Gr, [P|R], N_Puz):-
	inspecciona_num(Gr, Puz, P, Aux_Puz),
	inspecciona_grupo_aux(Aux_Puz, Gr, R, N_Puz).


%---------------------------------------------------------------------
%inspecciona(Puz, N_Puz)

%Puz:   O puzzle em causa
%N_Puz: O puzzle resultante de inspeccionar todos os numeros possiveis 
%       em todos os grupos existentes em <Puz>
			

%Predicados usados:
%	-grupos/1                (SUDOKU.pl)
%	-inspecciona_grupo/3     (ficheiro local)
%---------------------------------------------------------------------


inspecciona(Puz, N_Puz):-
	grupos(Gr_Lst),
	inspecciona_aux(Puz, Gr_Lst, N_Puz).
	
inspecciona_aux(Puz, [], Puz):-!.

inspecciona_aux(Puz, [P|R], N_Puz):-
	inspecciona_grupo(Puz, P, Aux_Puz),
	inspecciona_aux(Aux_Puz, R, N_Puz).


/*************************************\
|4a parte
|
|Predicados de verificacao de solucoes
\*************************************/

%---------------------------------------------------------------------
%grupo_correcto(Puz, Nums, Gr)

%Puz:   O puzzle em causa
%Nums:  Lista de numeros, potencialmente de 1 a dimensao de <Puz>
%Gr:    Conjunto de posicoes, cujo conteudo se vai verificar correto,
%       ou seja, sem repeticoes de numeros e contendo todos os
%		elementos de <Nums>

%Predicados usados:
%	-conteudos_posicoes/3    (SUDOKU.pl)
%	-append/2                (sistema Prolog)
%	-msort/2                 (sistema Prolog)
%---------------------------------------------------------------------


grupo_correcto(Puz, Nums, Gr):-
	conteudos_posicoes(Puz, Gr, Conteudos),
	append(Conteudos, Conteudos_unificados),
	%Assumindo que <Nums> esta ordenado;
	msort(Conteudos_unificados, Nums).


%---------------------------------------------------------------------
%solucao(Puz)

%Puz: Um puzzle que cumpre todas as regras do Sudoku, ou seja,
%     cujas linhas, colunas e blocos contem todos os numeros entre
%     1 e a dimensao do puzzle, sem repeticoes (grupos correctos).

%Predicados usados:
%	-grupos/1                (SUDOKU.pl)
%	-numeros/1               (SUDOKU.pl)
%	-grupo_correcto/3        (ficheiro local)
%---------------------------------------------------------------------


solucao(Puz):-
	grupos(Lst_Gr),
	numeros(Lst_Nums),
	solucao_aux(Puz, Lst_Nums, Lst_Gr).
	
solucao_aux(_, _, []):-!.

solucao_aux(Puz, Lst_Nums, [P|R]):-
	grupo_correcto(Puz, Lst_Nums, P),
	solucao_aux(Puz, Lst_Nums, R).

%---------------------------------------------------------------------
%resolve(Puz, Sol)

%Puz: O puzzle em causa
%Sol: Uma solucao para <Puz>.

%Predicados usados:
%	-inicializa/3            (ficheiro local)
%	-inspecciona/3           (ficheiro local)
%	-resolve_aux/5           (ficheiro local)
%---------------------------------------------------------------------



resolve(Puz, Sol):-
	inicializa(Puz, Aux1_Puz),
	inspecciona(Aux1_Puz, Aux2_Puz),
	resolve_aux(Aux2_Puz, Sol),!.


%---------------------------------------------------------------------
%resolve_aux(Puz, Sol)

%Puz: Puzzle a resolver, ja inicializado
%Sol: Solucao do puzzle <Puz>

%Predicados usados:
%	-solucao/1               (ficheiro local)
%	-puzzle_ref/2            (SUDOKU.pl)
%	-length/2                (sistema Prolog) 
%	-member/2                (sistema Prolog) 
%	-puzzle_muda_propaga/4   (ficheiro local)
%---------------------------------------------------------------------

	
resolve_aux(Puz, Puz):-
	solucao(Puz), !.

resolve_aux(Puz, Sol):-
	puzzle_ref(Puz, Pos, Cont),
	length(Cont, X),
	X > 1, !,
	member(Num, Cont),
	puzzle_muda_propaga(Puz, Pos, [Num], Tentativa),
	resolve_aux(Tentativa, Sol).
