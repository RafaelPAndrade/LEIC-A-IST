/*****************************************************************\
|IAED 2016/17 Projeto 2 - entradas/saidas de produtos num armazem
|Ficheiro: Item.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*****************************************************************/

# include "Item.h"

Item NewItem(Key new_chave, int new_unidades){
/*Cria um novo item cuja chave e <new_chave> e
 unidades sao <new_unidades>.*/

	Item res=(Item)malloc( sizeof(struct produto) );
	res->chave=new_chave;
	res->unidades= (new_unidades > 0) ? new_unidades : 0;

	return res;
}

void ShowItem(Item a){
/*Imprime a chave e as unidades de <a>.*/

	printf("%.8x %d\n", key(a), units(a));
}

Item UpdateItem(Item a, int variacao){
/*Actualiza as unidades de <a>, somando <variacao>.*/

	int aux = units(a) + variacao;
	a->unidades = (aux > 0) ? aux : 0;

	return a;
}

void freeItem(Item a){
/*Apaga <a>, libertando a memoria alocada.*/
	free(a);
}
