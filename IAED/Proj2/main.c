/*****************************************************************\
|IAED 2016/17 Projeto 2 - entradas/saidas de produtos num armazem
|Ficheiro: main.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*****************************************************************/

# include "ADT.h"

void funcao_a(link armazem[DIM_TABLE]);
void funcao_r(link armazem[DIM_TABLE]);
void funcao_m(link armazem[DIM_TABLE]);

void funcao_a(link armazem[DIM_TABLE]) {
/*Le uma chave e unidades, e actualiza <armazem>
 consoante o input.*/

	Key chave_input;
	int unidades_input;

	getchar();
	scanf("%x",&chave_input);
	getchar();
	scanf("%d",&unidades_input);

	Insert(armazem, chave_input, unidades_input);

}

void funcao_r(link armazem[DIM_TABLE]) {
/*Le uma chave e remove o item cuja chave e igual
 a lida.*/

	Key chave_input;

	getchar();
	scanf("%x",&chave_input);

	Delete(armazem, chave_input);
}


void funcao_m(link armazem[DIM_TABLE]) {
/*Imprime o item que contem o maior numero de unidades.
 Caso seja necessario, procura esse item.*/

	if(n_chaves_dif!=0) {
		if (item_max_unidades == NULL) TraverseSorted(armazem, MaiorProduto);

		ShowItem(item_max_unidades);
	}
}



int main()
{
	char op;

	link * armazem = NULL;
	Init(&armazem);

	do {
		op=getchar();
		switch(op)
		{
			case 'a':
				funcao_a(armazem);
				break;
			case 'l':
				TraverseSorted(armazem, ShowItem);
				break;
			case 'm':
				funcao_m(armazem);
				break;
			case 'r':
				funcao_r(armazem);
				break;
		}

	} while(op!='x');


	/*Ao sair, apresenta o numero de chaves diferentes.*/
	printf("%d\n", n_chaves_dif);
	FreeAll(armazem);

	return 0;
}


