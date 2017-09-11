%---------------------------------------------------------------------
%             Definicao da dimensao do puzzle
%---------------------------------------------------------------------

dimensao(9).

%---------------------------------------------------------------------
%
%        Predicados sugeridos para a implementacao do projecto
%
%---------------------------------------------------------------------

%---------------------------------------------------------------------
%             1. Operacoes basicas sobre puzzles
%---------------------------------------------------------------------

%---------------------------------------------------------------------
% puzzle_ref(Puz, Pos, Cont): O conteudo da posicao Pos de Puz e' Cont
%---------------------------------------------------------------------

puzzle_ref(Puz, (L, C), Cont) :-
    nth1(L,Puz,Linha),
    nth1(C,Linha,Cont).

%---------------------------------------------------------------------
% puzzle_muda(Puz, Pos, Cont, N_Puz):
% N_Puz e' o resultado de substituir o conteudo da posicao Pos
% de Puz por Cont.
%---------------------------------------------------------------------

puzzle_muda(Puz, (L,C), Cont, N_Puz) :-
    nth1(L,Puz,Linha),
    lista_muda(Linha,C,Cont, N_Linha),
    lista_muda(Puz,L,N_Linha, N_Puz),!.

lista_muda([_|T], 1, X, [X|T]) :- !.
lista_muda([H|T], I, X, [H|R]):-
    I > 0,
    NI is I-1,
    lista_muda(T, NI, X, R), !.
%lista_muda(L, _, _, L).

%---------------------------------------------------------------------
%             2. Predicados relativos ao puzzle
%---------------------------------------------------------------------

%---------------------------------------------------------------------
% numeros(L): L e' a lista [1,2,3,4,...,Dim],
% em que Dim e' a dimensao do puzzle.
%---------------------------------------------------------------------

numeros(L) :- dimensao(Dim),gera_entre(1,L,Dim,[]).

%---------------------------------------------------------------------
% posicoes_relacionadas(Pos,Posicoes): Posicoes e' a lista de posicoes
% relacionadas com a posicao Pos, isto e', posicoes na mesma linha,
% coluna ou bloco.
%---------------------------------------------------------------------

posicoes_relacionadas(Pos,Posicoes):-
    posicoes_mesma_fila(Pos,Pos_linha,l),
    posicoes_mesma_fila(Pos,Pos_coluna,c),
    posicoes_mesmo_bloco(Pos,Pos_bloco),
    append([Pos_linha,Pos_coluna,Pos_bloco],Posicoes_temp),
    sort(Posicoes_temp,Posicoes).

%---------------------------------------------------------------------
% grupos(Gr): Gr e' uma lista de listas:
% cada lista contem as posicoes de uma linha, coluna ou bloco, isto e',
% de um grupo;
% ordenacao: linhas, seguidas de colunas e de blocos.
%---------------------------------------------------------------------

grupos(Gr) :-
    numeros(Nums),
    maplist(posicoes_fila(l),Nums,Linhas),
    maplist(posicoes_fila(c),Nums,Colunas),
    maplist(posicoes_bloco,Nums,Blocos),
    append([Linhas,Colunas,Blocos],Gr).

%---------------------------------------------------------------------
% todas_posicoes(Todas_Posicoes): Todas_Posicoes e' uma lista com todas
% as posicoes do puzzle; ordenacao: por linhas.
%---------------------------------------------------------------------

todas_posicoes(Todas_Posicoes) :-
    numeros(Todas_filas),
    combina(Todas_filas,Todas_filas,Todas_Posicoes).

%---------------------------------------------------------------------
% conteudos_posicoes(Puz,Posicoes,Conteudos):
% Conteudos e' a lista com os conteudos de Puz,
% nas posicoes de Posicoes.
%---------------------------------------------------------------------

conteudos_posicoes(Puz,Posicoes,Conteudos) :-
    maplist(puzzle_ref(Puz),Posicoes,Conteudos).

%---------------------------------------------------------------------
%             3. Funcional sobre listas
%---------------------------------------------------------------------

%---------------------------------------------------------------------
% percorre_muda_Puz(Puz,Accao,Lst,N_Puz):
% Puz e' um puzzle;
% Accao e' um predicado de argumentos
%      [Puz, <elemento de Lst>,N_Puz]
% N_Puz e' o puzzle resultante de aplicar
%      Accao(Puz, <elemento de Lst>,N_Puz)
% a cada elemento de Lst
%---------------------------------------------------------------------

percorre_muda_Puz(Puz,_,[],Puz) :- !.
percorre_muda_Puz(Puz,Accao,[P | R],N_Puz) :-
    Accao =.. Lst_Accao,
    append(Lst_Accao, [Puz,P,Res],Accao_com_argumentos),
    Lit =.. Accao_com_argumentos,
    call(Lit),
    percorre_muda_Puz(Res,Accao,R,N_Puz).

% Exemplos
% junta_numero_posicao(Num,Puz,Pos,N_Puz):
% N_Puz resulta de adicionar o numero Num
% ao conteudo da posicao Pos do puzzle Puz
junta_numero_posicao(Num,Puz,Pos,N_Puz) :-
    puzzle_ref(Puz,Pos,Cont_Pos),
    append(Cont_Pos,[Num],N_Cont_Pos),
    puzzle_muda(Puz,Pos,N_Cont_Pos,N_Puz).

% junta_numero_posicoes(Num,Puz,Posicoes,N_Puz):
% N_Puz resulta de adicionar o numero Num
% aos conteudos das posicoes da lista Posicoes do puzzle Puz

junta_numero_posicoes(Num,Puz,Posicoes,N_Puz) :-
    percorre_muda_Puz(Puz,junta_numero_posicao(Num),Posicoes,N_Puz).


% junta_num_linha_a_linha(Puz,Posicoes_linha,N_Puz):
% N_Puz resulta de adicionar o numero de linha a cada uma das
%  posicoes da lista Posicoes_linha do puzzle Puz

junta_num_linha_a_linha(Puz,Posicoes_linha,N_Puz) :-
    Posicoes_linha = [(Num_linha,_) | _], % obtem o numero da linha
    percorre_muda_Puz(Puz, junta_numero_posicao(Num_linha),
                      Posicoes_linha,N_Puz).

% junta_num_linha_a_linhas(Puz,Lista_linhas,N_Puz):
% N_Puz resulta de adicionar o numero de linha a cada uma das
%  linhas da lista Lista_linhas do puzzle Puz

junta_num_linha_a_linhas(Puz,Lista_linhas,N_Puz) :-
    percorre_muda_Puz(Puz,junta_num_linha_a_linha,Lista_linhas,N_Puz).


% ?- Puz =  [[[4], [], [], [3]], [[], [], [4], []],
%            [[2], [3], [], []], [[], [], [], []]],
%     Posicoes_linha3 = [ (3, 1), (3, 2), (3, 3), (3, 4)],
%     junta_numero_posicoes(100,Puz,Posicoes_linha3,Res1),
%     junta_num_linha_a_linha(Puz,Posicoes_linha3,Res2),
%     Lista_linhas = [[ (1, 1), (1, 2), (1, 3), (1, 4)],
%                     [ (2, 1), (2, 2), (2, 3), (2, 4)],
%                     [ (3, 1), (3, 2), (3, 3), (3, 4)],
%                     [ (4, 1), (4, 2), (4, 3), (4, 4)]],
%     junta_num_linha_a_linhas(Puz,Lista_linhas,Res3).
% Puz = [[[4], [], [], [3]], [[], [], [4], []],
%        [[2], [3], [], []], [[], [], [], []]],
% Posicoes_linha3 = [ (3, 1), (3, 2), (3, 3), (3, 4)],
% Res1 = [[[4], [], [], [3]], [[], [], [4], []],
%         [[2, 100], [3, 100], [100], [100]], [[][], [], []]],
% Res2 = [[[4], [], [], [3]], [[], [], [4], []],
%         [[2, 3], [3, 3], [3], [3]], [[], [], [], []]],
% Lista_linhas = [[ (1, 1), (1, 2), (1, 3), (1, 4)],
%                 [ (2, 1), (2, 2), (2, 3), (2, 4)],
%                 [ (3, 1), (3, 2), (3, 3), (3, 4)],
%                 [ (4, 1), (4, 2), (4, 3), (4, 4)]],
% Res3 = [[[4, 1], [1], [1], [3, 1]], [[2], [2], [4, 2], [2]],
%         [[2, 3], [3, 3], [3], [3]], [[4], [4], [4], [4]]].


%---------------------------------------------------------------------
%
%         Predicados sugeridos para a implementacao do projecto
%                                FIM
%---------------------------------------------------------------------

%---------------------------------------------------------------------
%
%                Outros Predicados relativos ao puzzle
%
%---------------------------------------------------------------------

%---------------------------------------------------------------------
% posicoes_fila(L_C,F,Posicoes): F e' o numero de uma fila;
% L_C e' l (linha) ou c (Coluna);
% Posicoes e' a lista das posicoes da fila F
%---------------------------------------------------------------------

posicoes_fila(L_C,F,Posicoes) :-
    numeros(Nums),
    maplist(acrescenta_linha_ou_coluna(F,L_C),Nums,Posicoes).

acrescenta_linha_ou_coluna(F,L_C,Acresc,Res) :-
    (L_C = l,!, Res = (F,Acresc)
                ;
    L_C = c,!, Res = (Acresc,F)).

%---------------------------------------------------------------------
% posicoes_mesma_fila((L,C),Lst_Pos,L_C): (L,C) e' uma posicao;
% L_C e' l (linha) ou c (Coluna);
% Posicoes e' a lista das posicoes na mesma fila que (L,C).
%---------------------------------------------------------------------

posicoes_mesma_fila((L,C),Lst_Pos,L_C) :-
    (L_C = l,!, Constante = L
                ;
    L_C = c,!, Constante = C),
    posicoes_fila(L_C,Constante,Posicoes),
    subtract(Posicoes,[(L,C)],Lst_Pos).

%---------------------------------------------------------------------
% combina(Lst1,Lst2,Res): Lst1 e Lst2 sao listas do mesmo comprimento;
% Res e' uma lista que contem todos os pares em que o 1o elemento
% pertence a Lst1 e o 2o elemento pertence a Lst2.
%---------------------------------------------------------------------

%combina([1,2,3],[4,5,6],
%        [(1,4),(1,5),(1,6),(2,4),(2,5),(2,6),(3,4),(3,5),(3,6)])
combina(Linhas,Colunas,Res) :-
    maplist(combina_uma(Colunas),Linhas,Temp),
    append(Temp,Res).

%combina_uma([1,2,3],1,[(1, 1), (1, 2), (1, 3)]).
combina_uma(Colunas,Linha,Res) :-
    maplist(acrescenta_linha_ou_coluna(Linha,l),Colunas,Res).

%---------------------------------------------------------------------
% num_bloco_posicao((L,C),Num_bloco): (L,C) e' uma posicao;
% Num_bloco e' o numero do bloco dessa posicao.
%---------------------------------------------------------------------

num_bloco_posicao((L,C),Num_bloco) :-
    dimensao(Dim),
    Dim_bloco is round(sqrt(Dim)),
    Num_bloco is (L - 1) // Dim_bloco * Dim_bloco + 1 +
                 (C - 1) // Dim_bloco.

%---------------------------------------------------------------------
% posicoes_bloco(N_bloco,Posicoes): Num_bloco e' um numero de bloco;
% Posicoes e' a lista das posicoes nesse bloco.
%---------------------------------------------------------------------

posicoes_bloco(N_bloco,Posicoes) :-
    primeiras_linha_coluna_bloco(N_bloco,Prim_linha,Prim_coluna,
                                 Ultima_linha,Ultima_coluna),
    gera_entre(Prim_linha,Ultima_linha,Linhas),
    gera_entre(Prim_coluna,Ultima_coluna,Colunas),
    combina(Linhas,Colunas,Posicoes).

primeiras_linha_coluna_bloco(N_bloco,PL,PC,UL,UC) :-
    dimensao(Dim),
    Dim_bloco is round(sqrt(Dim)),
    PL is (N_bloco -1) // Dim_bloco  * Dim_bloco + 1,
    PC is (N_bloco -1) mod Dim_bloco  * Dim_bloco + 1,
    UL is PL + Dim_bloco - 1,
    UC is PC + Dim_bloco - 1.

%---------------------------------------------------------------------
% posicoes_mesmo_bloco((L,C), Posicoes): (L,C) e' uma posicao;
% Posicoes e' a lista das posicoes no mesmo bloco que (L,C).
%---------------------------------------------------------------------

posicoes_mesmo_bloco((L,C), Posicoes) :-
    num_bloco_posicao((L,C),Num_bloco),
    posicoes_bloco(Num_bloco,Temp),
    subtract(Temp,[(L,C)],Posicoes).

%---------------------------------------------------------------------
% gera_entre(N1,N2,Res): L e' a lista [N1, N1 + 1, ..., N2]
%---------------------------------------------------------------------

gera_entre(N1,N2,L) :- gera_entre(N1,L,N2,[]).
gera_entre(N1,Res,I,Res) :- I < N1,!.
gera_entre(N1,L,I,Res) :-
    N_Res = [I | Res],
    N_I is I - 1,
    gera_entre(N1,L,N_I,N_Res).


%---------------------------------------------------------------------
%               escreve(Puz): escreve Puz por linhas
%---------------------------------------------------------------------

escreve(Puz) :-
    write('['),
    escreve_aux(Puz).
escreve_aux([H]) :- write(H),writeln(']'),!.
escreve_aux([H|T]) :-
    write(H),writeln(','),
    escreve_aux(T).
