/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: T.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

# include <stdio.h>
# include "header.c"

/*********************************************************************\
 Funcao funcao_T (Listar qual/quais o(s)utilizador(es) mais activo(s)):
    -imprime o(s) utilizador(es) mais activo(s)

	|Argumentos:
	|	-mensagens_por_user: contador de mensagens de cada user
	|	-n_mensagens_mais_ativo: n. de mensagens
	|
	|Input:
	|	-void
	|
	|Output:
	|	- User com mais mensagens postadas no <forum>
	|
	|Return:
	|	-void
	|
\*********************************************************************/

void funcao_T(const int mensagens_por_user[MAX_USERS], const int n_mensagens_mais_ativo)
{

	int i;

	for(i=0; i<MAX_USERS; ++i)
		if (mensagens_por_user[i]==n_mensagens_mais_ativo)
			printf("*MOST ACTIVE USER:%d:%d\n", i, n_mensagens_mais_ativo);
}
