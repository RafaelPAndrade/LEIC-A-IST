/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: O.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

# include <stdio.h>
# include <string.h>
# include "header.c"

/*******************************************************\
 Funcao funcao_O (Listar qual/quais a(s) mensagem(s) mais longa(s)):
    -imprime a(s) frase(s) mais longa(s)

	|Argumentos:
	|	-forum: lista de Mensagens (vide header.c)
	|	-n_mensagens: numero de mensagens no <forum>
	|	-comprimento_max: maior comprimento registado
	|
	|Input:
	|	-void
	|
	|Output:
	|	-A maior mensagem de <forum> (ou as maiores)
	|
	|Return:
	|	-void
	|
\*******************************************************/

void funcao_O(const Mensagem forum[], const int n_mensagens, const int comprimento_max)
{

	int i;

	for (i=0; i<n_mensagens; ++i)
		if ( strlen(forum[i].frase) == comprimento_max )
			printf("*LONGEST SENTENCE:%d:%s\n", forum[i].user_id, forum[i].frase);

}