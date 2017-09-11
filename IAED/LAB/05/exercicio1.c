# include <stdio.h>

#define NUMEROLIVROS 100
#define MAXTITULO 40
#define MAXNOME 20


typedef struct {
	int dia;
	int mes;
	int ano;
} Data;


typedef struct {
	char titulo[MAXTITULO+1];
	char autor[MAXNOME+1];
	long int isbn;
	int anoPublicacao;
	int numeroDaCopia;
	Data dataEmprestimo;
	Data dataRetorno;
} Livro;

void mostraMenu(void);

void mostraMenu(void){

	printf("****BIBLIOTECA DO IST****\n");
	printf("1 - Inserir novo livro\n");
	printf("2 - Listar livros\n");
	printf("3 - Procurar livro por isbn\n");
	printf("4 - Procurar livro por título\n");
	printf("5 - Alterar título do livro\n");
	printf("6 - Apagar livro pelo isbn\n");
	printf("7 - Registar data de empréstimo de um livro pelo isbn");
	printf("8 - Registar data de retorno de um livro pelo isbn");
	printf("0 - Sair\n");
	printf("*************************\n");
}

int main(){

	mostraMenu();

	return 0;
}
