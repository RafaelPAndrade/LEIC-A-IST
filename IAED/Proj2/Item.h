/*****************************************************************\
|IAED 2016/17 Projeto 2 - entradas/saidas de produtos num armazem
|Ficheiro: Item.h
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*****************************************************************/

# ifndef _ITEM_
# define _ITEM_

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

# define key(a)    ( a != NULL ? a->chave : 0 )
# define units(a)  ( a != NULL ? a->unidades : -1 )
# define less(a,b) ( a <  b )
# define eq(a,b)   ( a == b )

typedef uint32_t Key;

typedef struct produto{
	Key chave;
	int unidades;
} * Item;


/*********************************\
|Prototipos
\*********************************/

Item NewItem(Key chave, int unidades);
void ShowItem(Item a);
Item UpdateItem(Item a, int variacao);
void freeItem(Item a);

#endif