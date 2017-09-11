# include "header.h"
# include <stdio.h>
# include <string.h>

void mostraMenu(void){

	printf("****BIBLIOTECA DO IST****\n");
	printf("1 - Inserir novo livro\n");
	printf("2 - Listar livros\n");
	printf("3 - Procurar livro por isbn\n");
	printf("4 - Procurar livro por título\n");
	printf("5 - Alterar título do livro\n");
	printf("6 - Apagar livro pelo isbn\n");
	printf("7 - Registar data de empréstimo de um livro pelo isbn\n");
	printf("8 - Registar data de retorno de um livro pelo isbn\n");
	printf("0 - Sair\n");
	printf("*************************\n");
}


/**********************************************\
*Funcoes de datas                              *
\**********************************************/
Data insereData(void){

	Data res;
	printf("Dia: ");
	scanf("%d", &res.dia);
	printf("Mes: ");
	scanf("%d", &res.mes);
	printf("Ano: ");
	scanf("%d", &res.ano);

	return res;
}

void mostraData(const Data d){

	printf("%02d-%02d-%d", d.dia, d.mes, d.ano);
}


/**********************************************\
*Funcoes de Livros                             *
\**********************************************/

void mostraLivro(const Livro l){

	printf("Nome do livro: %s\b", l.titulo);

	printf("Autor do livro: %s", l.autor);

	printf("Codigo ISBN: %ld\n", l.isbn);

	printf("Ano de publicacao: %d\n", l.anoPublicacao);

	printf("Numero da copia: %d\n", l.numeroDaCopia);

	printf("Data do emprestimo: ");
	mostraData(l.dataEmprestimo);
	putchar('\n');

	printf("Data de retorno: ");
	mostraData(l.dataRetorno);
	putchar('\n');
}


/**********************************************\
*Funcoes de bibliotecas                        *
\**********************************************/

void insereLivroBiblioteca(Livro b[], const int i){

	printf("\nNovo livro:\n");

	printf("Nome do livro: ");
	fgets(b[i].titulo, MAXTITULO+1, stdin);

	printf("Autor do livro: ");
	fgets(b[i].autor, MAXNOME+1, stdin);

	printf("Codigo ISBN: ");
	scanf("%ld", &b[i].isbn);

	printf("Ano de publicacao: ");
	scanf("%d", &b[i].anoPublicacao);

	printf("Numero da cópia: ");
	scanf("%d", &b[i].numeroDaCopia);

	b[i].dataEmprestimo.dia=0;
	b[i].dataEmprestimo.mes=0;
	b[i].dataEmprestimo.ano=0;

	b[i].dataRetorno.dia=0;
	b[i].dataRetorno.mes=0;
	b[i].dataRetorno.ano=0;
}

void listaLivros(const Livro biblioteca[], const int n_livros){

	int i;
	if (n_livros<=0)
		printf("Biblioteca vazia");
	else
		for(i=0; i<n_livros; ++i) {
			printf("------------------------------------------------------\n");
			printf("%02d: %sautor: %sisbn: %ld\n", i+1, biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].isbn);
		}

		printf("------------------------------------------------------\n");
}



void alteraTituloBiblioteca(Livro b[], const int index){

	printf("Escreva um novo titulo para substituir \"%s\": ", b[index].titulo);
	fgets(b[index].titulo, MAXTITULO+1, stdin);
	printf("\nTitulo alterado!\n");
}

void apagaLivro(Livro biblioteca[], const int n_livros, const int index){
	/*Apaga um livro ao escrever por cima dele com o ultimo
	Deve-se decrementar manualmente o n_livros fora desta funcao*/

	printf("A apagar o livro %s", biblioteca[index].titulo);
	biblioteca[index]=biblioteca[n_livros-1];
}

void insereEmprestimoBib(Livro biblioteca[], const int index){

	printf("Data do emprestimo: \n");
	biblioteca[index].dataEmprestimo=insereData();
}

void insereDevolucaoBib(Livro biblioteca[], const int index){

	printf("Data de retorno: \n");
	biblioteca[index].dataRetorno=insereData();
}

/*******************\
|Funcoes procura    |
\*******************/

int procuraLivroIsbn(const Livro biblioteca[], int n_livros){
	/*Devolve o indice de biblioteca[] que primeiro tem um isbn
	*igual a isbn_alvo
	*n_livros ser o numero de livros, nao o ultimo indice
	*retorna -1 se nao existir livro com o ISBN, retorna indice*/

	long isbn_alvo;

	printf("Insira um ISBN: ");
	scanf("%ld", &isbn_alvo);
	putchar('\n');

	for(n_livros-=1; n_livros>=0; --n_livros)
		if (biblioteca[n_livros].isbn==isbn_alvo){
			printf("Livro encontrado!\n");
			return n_livros;
		}

	Erro(404); /*Se nao encontrar*/
	return -1;
}

int procuraLivroTitulo(const Livro biblioteca[], int n_livros){
	/*Devolve o indice de biblioteca[] que primeiro tem um titulo
	*igual a titulo_alvo
	*n_livros ser o numero de livros, nao o ultimo indice
	*retorna -1 se nao existir livro com o titulo, indice se nao*/

	char titulo_alvo[MAXTITULO+1];

	printf("Insira um Titulo: ");
	fgets(titulo_alvo, MAXTITULO+1, stdin);

	for(n_livros-=1; n_livros>=0; --n_livros)
		if (!strcmp(biblioteca[n_livros].titulo,titulo_alvo)){
			printf("Livro encontrado!\n");
			return n_livros;
		}

	Erro(404); /*Se nao encontrar*/
	return -1;
}




/************************************\
|Mensagens de Erro                   |
\************************************/
void Erro(int error_code){
	if (error_code==404)
		printf("Erro 404- Livro nao encontrado\n");
	else
		printf("Erro nao especificado!\n");
}
