/*****************************************************************\
|IAED 2016/17 Projeto 2 - entradas/saidas de produtos num armazem
|Ficheiro: ADT.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*****************************************************************/

# include "ADT.h"

/**************************************\
|Funcoes Auxiliares
\**************************************/
int hash(const Key chave);
link * searchNode(link armazem[DIM_TABLE], const Key chave);
void newNode(link * previous, Item prod);


int hash(const Key chave){
/*Retorna o indice da tabela ao qual <chave> pertence.
 Nesta implementacao, corresponde aos primeiros 3 digitos
 (Numero de zeros de DIM_TABLE, escrito em hexadecimal).*/

	return chave / DIVISOR_HASH;
}

link * searchNode(link armazem[DIM_TABLE], const Key chave) {
/*Retorna o ponteiro para o primeiro link (que aponta para um item)
 cuja chave seja maior ou igual a <chave> (pertencente a mesma lista).*/

	link * res = armazem + hash(chave);
	for( ; (*res) != NULL && less(key((*res)->item), chave); res = &(*res)->next );

	return res;
}


void newNode(link * previous, Item prod) {
/*Cria um novo node na lista, tratando de alocar o espaco
 necessario.*/

	link aux = *previous;
	*previous = (link) malloc(sizeof(struct node));
	(*previous)->item=prod;
	(*previous)->next=aux;
}



void Init(link ** armazem) {
/*Inicializa a estrutura, alocando espaco para a tabela
 e tambem inicializa o para o item que contem mais unidades
 a NULL.*/
	item_max_unidades = NULL;
	*armazem = (link*) calloc(DIM_TABLE, sizeof(link));
}


void Insert(link armazem[DIM_TABLE], Key chave, int unidades){
/*Esta funcao pode atuar de duas maneiras:
	-se <chave> nao existe na estrutura, cria um novo node;
	-se existir, atualiza o item correspondente.*/

	link * cand;
	link aux;

	cand = searchNode(armazem, chave);

	if ( (*cand)==NULL || less(chave, key((*cand)->item)) ) {
	/*Primeiro caso: inserir novo node*/

		aux = *cand;
		newNode(cand, NewItem(chave, unidades));
		(*cand)->next = aux;

		/*Incremento do numero de nodes no <armazem>*/
		n_chaves_dif+=1;

		if  ( item_max_unidades != NULL) {
			if ( unidades > units(item_max_unidades) ||
			   (unidades == units(item_max_unidades) && less(chave, key(item_max_unidades)) ) ){
				/*Mudanca do item que contem mais unidades*/
				item_max_unidades = (*cand)->item;
			}
		}
	}

	else if ( eq(key((*cand)->item), chave) ){
	/*Segundo caso: update a um node*/
		(*cand)->item = UpdateItem((*cand)->item, unidades);

		if ( item_max_unidades != NULL ) {
			if ( eq (chave, key(item_max_unidades)) ){
			/*Houve um update no item que continha mais unidades*/
				if (unidades < 0 )
				/*Reduzimos unidades do maximo. Nao sabemos se ainda e o maximo*/
					item_max_unidades = NULL;
			}

			else if ( units((*cand)->item) > units(item_max_unidades) ||
			        ( units((*cand)->item) == units(item_max_unidades) && less(key((*cand)->item), key(item_max_unidades)) ) ) {
				/*Houve um update num item que fez com que este se tenha tornado no que tem mais unidades*/
				item_max_unidades = (*cand)->item;
			}
		}
	}
}



void Delete(link armazem[DIM_TABLE], Key chave) {
/*Apaga o node (libertando a memoria correspondente)
 cuja chave (do item) == <chave> (se existir).*/

	link aux;
	link * candidato_apagar = searchNode(armazem, chave);

	if ( eq(chave, key(item_max_unidades)) ){
	/*Vai apagar-se o item que contem mais unidades*/
		item_max_unidades = NULL;
	}

	/*Confirma que a chave do candidato == chave que queremos apagar*/
	if( (*candidato_apagar)!=NULL && eq(key((*candidato_apagar)->item), chave) ) {
		aux = *candidato_apagar;
		*candidato_apagar = aux->next;
		freeItem(aux->item);
		free(aux);
		/*Decremento do numero total de items em <armazem>*/
		n_chaves_dif-=1;
	}
}


void TraverseSorted(link armazem[DIM_TABLE] , void(*func)(Item)) {
/*Aplica <func> a todos os items de <armazem>, por ordem de chave.*/

	int i;
	link ptr;
	for( i=0; i<DIM_TABLE; ++i )
		for( ptr=armazem[i]; ptr!=NULL; ptr=ptr->next )
			func(ptr->item);
}

void MaiorProduto(Item a) {
/*Usada em TraverseSorted, actualiza o ponteiro para o node
 que contem mais unidades.*/

	if ( units(a) > units(item_max_unidades) )
		item_max_unidades = a;
}


void FreeAll(link armazem[DIM_TABLE]) {
/*Liberta toda a memoria alocada para os nodes e
 para o <armazem>.*/

	int i;
	link aux, next;
	for ( i=0;i<DIM_TABLE;i++ ){
		aux=armazem[i];
		for( aux = armazem[i]; aux != NULL; aux=next ) {
			next=aux->next;
			freeItem(aux->item);
			free(aux);
		}
	}
	free(armazem);
}
