/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: main.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

#include <stdio.h>
#include "header.c"

int main()
{

	//Inicializacao de variaveis

	//Forum: lista de mensagens (vide header.c)
	Mensagem forum[MAX_MSGS];
	
	//numero de mensagens no forum
	int n_mensagens=0;

	//Inteiro que guarda o comprimento da maior frase
	int max_cmp_frase=0;

	//Contador de mensagens que cada user postou no <forum>
	int mensagens_por_user[MAX_USERS]={};

	//Inteiro que guarda o numero de posts do user mais ativo
	int n_msgs_user_mais_ativo=0;

	//Lista de indices de <forum>
	int index[MAX_MSGS];
	int i;

	for(i=0; i<MAX_MSGS; i++)
		index[i]=i;


	//Caractere que representa o comando a executar
	char op;

	do {
		op=getchar();
		switch(op)
		{
			case 'A':
				//Adiciona uma mensagem ao forum (vide A.c)
				funcao_A(forum, n_mensagens++, mensagens_por_user, &max_cmp_frase, &n_msgs_user_mais_ativo);
				break;
			case 'L':
				//Lista todas as mensagens de forum (vide L.c)
				funcao_L(forum, n_mensagens);
				break;
			case 'U':
				//Lista todas mensagens de um user especifico (vide U.c)
				funcao_U(forum, n_mensagens, mensagens_por_user);
				break;
			case 'O':
				//Escreve a mensagem mais longa do forum (vide O.c)
				funcao_O(forum, n_mensagens, max_cmp_frase);
				break;
			case 'T':
				//Apresenta o utilizador mais ativo do forum (vide T.c)
				funcao_T(mensagens_por_user, n_msgs_user_mais_ativo);
				break;
			case 'S':
				//Lista as frase do forum por ordem alfabetica (vide S.c)
				funcao_S(forum,n_mensagens,index);
				break;
			case 'C':
				//Imprime o numero de ocorrencias de determinada palavra
				funcao_C(forum,n_mensagens);
				break;
		}

	} while(op!='X');


	//Ao sair, apresenta o numero de mensagens do forum;
	printf("%d\n", n_mensagens);
	return 0;
}
