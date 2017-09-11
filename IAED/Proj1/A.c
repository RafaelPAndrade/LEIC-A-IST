/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: A.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

#include <stdio.h>
#include <string.h>
#include "header.c"


/***********************************************************************************************************\
 Funcao funcao_A (Adicionar uma nova mensagem):
    -Le o user e uma frase, adicionando-os a <forum>
    -incrementa numero de mensagens do utilizador (<user_id>) (lista mensagens_por_user[])
    -altera <*p_max_cmp_frase>, se a frase a ser postada e a maior do forum
    -altera <*p_n_msgs_user_mais_ativo>, se o utilizador postou o maior numero de mensagens de todo o forum

	|Argumentos:
	|	-forum: lista de Mensagens (vide header.c)
	|	-n_mensagens: numero de mensagens no <forum>
	|	-mensagens_por_user: contador de mensagens de todos os users
	|	-p_max_cmp_frase: ponteiro para o numero de chars da maior frase no <forum>
	|	-p_n_msgs_user_mais_ativo: ponteiro para o numero de posts do user mais ativo de <forum>
	|
	|
	|Input:
	|	-msg: frase a adicionar a <forum>
	|	-user_id: utilizador que postou <msg>
	|
	|Output:
	|	-void
	|
	|Return:
	|	-void
	|
\***********************************************************************************************************/

void funcao_A(Mensagem forum[], const int n_mensagem, int mensagens_por_user[], int *p_max_cmp_frase, int *p_n_msgs_user_mais_ativo)
{

	int i=0, c;

	//Elimina o espaco em branco antes do user id
	getchar();

	//Le o user id
	scanf("%d", &forum[n_mensagem].user_id);

	//Elimina o espaco em branco antes da frase
	getchar();

	//Le a frase
	while ( (c=getchar())!='\n' && c!=EOF && i<MAX_LEN_FRASE )
		forum[n_mensagem].frase[i++]=c;

	forum[n_mensagem].frase[i]='\0';

	//Incrementa o contador de mensagens
	mensagens_por_user[forum[n_mensagem].user_id]++;

  //Compara o comprimento da frase a ser postada com a maior do forum, atualizando se for o caso
	if( i > *p_max_cmp_frase)
		*p_max_cmp_frase=i;
		
  //Compara o numero de mensagens do user que postou, atualizando se for o mais ativo
	if ( mensagens_por_user[forum[n_mensagem].user_id] > *p_n_msgs_user_mais_ativo )
		*p_n_msgs_user_mais_ativo=mensagens_por_user[forum[n_mensagem].user_id];
}