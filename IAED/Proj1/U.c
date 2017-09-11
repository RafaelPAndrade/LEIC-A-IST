/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: U.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

# include <stdio.h>
# include "header.c"

/************************************************************************************\
 Funcao funcao_U (Listar mensagens de um certo utilizador):
    -imprime as mensagens referentes ao utilizador em questao

	|Argumentos:
	|	-forum: lista de Mensagens (vide header.c)
	|	-n_mensagens: numero de mensagens no <forum>
	|	-mensagem_por_user: contador de mensagens que cada utilizador tem em <forum>
	|
	|Input:
	|	-user: numero do utilizador a procurar as mensagens
	|
	|Output:
	|	-Todas as frases de <user> no <forum>
	|
	|Return:
	|	-void
	|
\***********************************************************************************/

void funcao_U(const Mensagem forum[], const int n_mensagens, const int mensagens_por_user[])
{

	int user, i;
	int n_mensagens_user;


	//Elimina o espaco em branco antes do user id
	getchar();

	//Le o user id
	scanf("%d", &user);


	printf("*MESSAGES FROM USER:%d\n", user);

	n_mensagens_user=mensagens_por_user[user];


	for (i=0; n_mensagens_user>0; ++i)
		if (forum[i].user_id==user) {
			printf("%s\n", forum[i].frase);
			--n_mensagens_user;
		}

}