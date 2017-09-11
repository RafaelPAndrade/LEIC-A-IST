/*****************************************************************\
|IAED 2016/17 Projeto 2 - entradas/saidas de produtos num armazem
|Ficheiro: ADT.h
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*****************************************************************/

/*
Estrutura escolhida: encadeamento externo
link armazem[DIM_TABLE];
*/

# ifndef _ADT_
# define _ADT_

# include "Item.h"


# define DIM_TABLE 0x1000

/*Numero de digitos da chave que queremos considerar*/
# define DIVISOR_HASH 0x100000

typedef struct node{
	Item item;
	struct node * next;
} * link;

int n_chaves_dif;

/*Ponteiro para o item com o maior numero de unidades*/
Item item_max_unidades;


/**************************************\
|Prototipos
\**************************************/

void Init(link ** armazem);

void Insert(link armazem[DIM_TABLE], Key chave, int unidades);

void Delete(link armazem[DIM_TABLE], Key chave);

void TraverseSorted(link armazem[DIM_TABLE], void (*func)(Item));
void MaiorProduto(Item a);

void FreeAll(link armazem[DIM_TABLE]);

# endif
