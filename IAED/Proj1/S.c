/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: S.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

#include <stdio.h>
#include <string.h>
#include "header.c"

/*****************************************************************************************\
 Funcao funcao_S :
    -Lista as mensagens de <forum> por ordem alfabetica (e por numero de utilizador),
    utilizando uma implemetacao de mergesort

	|Argumentos:
	|	-forum: lista de Mensagens (vide header.c)
	|	-n_mensagens: numero de mensagens no <forum>
	|	-index: lista de indices do <forum>
	|
	|Input:
	|	-void
	|
	|Output:
	|	-todas as mensagens de <forum>, ordenadas alfabeticamente, e com o numero de user
	|
	|Return:
	|	-void
	|
\*****************************************************************************************/



void funcao_S(const Mensagem forum[],const int n_mensagens,int index[])
{

	int i;

	//Ordenar a lista de indices
	mergesort(index, 0, n_mensagens-1, forum);

	printf("*SORTED MESSAGES:%d\n",n_mensagens);

	for(i=0; i<n_mensagens; i++)
		printf("%d:%s\n", forum[index[i]].user_id, forum[index[i]].frase);
}




int msgm_abaixo(const Mensagem msg1, const Mensagem msg2)
{
	//Retorna positivo se <msg1> estiver alfabeticamente abaixo de msg2;
	//ou seja, se der positivo, <msg1> aparece na lista DEPOIS de <msg2>
	int res;

	res=strcmp(msg1.frase,msg2.frase);

	//Criterio de desempate: user_id
	if(!res)
		res=msg1.user_id-msg2.user_id;

	return res>0;
}


//Vetor auxiliar para o algoritmo mergesort
int aux[MAX_MSGS];

void merge(int index[], int l, int m, int r, const Mensagem forum[])
{

	int i, j, k;
	//copia de l a m, para o aux;
	for (i=m+1; i>l; --i)
		aux[i-1]=index[i-1];
	for (j=m; j < r; ++j)
		aux[r+m-j]=index[j+1];
	for (k=l; k<=r; ++k)
	  //Se a condicao for verdadeira, devemos colocar primeiro o <aux[j]>.
		if ( msgm_abaixo(forum[aux[i]], forum[aux[j]]) )
			index[k]=aux[j--];
		else
			index[k]=aux[i++];
}


void mergesort(int index[], int l, int r, const Mensagem forum[])
{

	int m=(r+l)/2;
	if (r<=l) return;
	mergesort(index, l, m, forum);
	mergesort(index, m+1, r, forum);
	merge(index, l, m, r, forum);
}
