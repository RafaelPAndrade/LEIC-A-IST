/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: L.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

# include <stdio.h>
# include "header.c"

/**************************************************\
 Funcao funcao_L:
    -imprime  todas as mensagens que estao no forum
   
	|Argumentos:
	|	-forum: lista de Mensagens (vide header.c)
	|	-n_mensagens: numero de mensagens em <forum>
	|
	|Input:
	|	-void
	|
	|Output:
	|	-Todas as frases de <forum>
	|
	|Return:
	|	-void
	|
\**************************************************/

void funcao_L(const Mensagem forum[], const int n_mensagens)
{

	int i;

	printf("*TOTAL MESSAGES:%d\n", n_mensagens);


	for (i=0; i<n_mensagens; ++i)
		printf("%d:%s\n", forum[i].user_id, forum[i].frase);

}
