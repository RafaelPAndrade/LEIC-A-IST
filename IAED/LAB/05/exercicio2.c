# include <stdio.h>
# include "header.h"

int main(void){

	Livro biblioteca[NUMEROLIVROS];
	int n_livros=0, opcao=0;
	int return_value;

	do {
		mostraMenu();
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		getchar();
		putchar('\n');

		switch(opcao){
			case 1:
				insereLivroBiblioteca(biblioteca, n_livros);
				n_livros++;
				break;
			case 2:
				listaLivros(biblioteca, n_livros);
				break;
			case 3:
				return_value=procuraLivroIsbn(biblioteca, n_livros);
				if( return_value >=0 )
					mostraLivro(biblioteca[return_value]);
				break;
			case 4:
				return_value=procuraLivroTitulo(biblioteca, n_livros);
				if( return_value >=0 )
					mostraLivro(biblioteca[return_value]);
				break;
			case 5:
				return_value=procuraLivroTitulo(biblioteca, n_livros);
				if( return_value >=0 )
					alteraTituloBiblioteca(biblioteca, return_value);
				break;
			case 6:
				return_value=procuraLivroIsbn(biblioteca, n_livros);
				if( return_value >=0 ){
					apagaLivro(biblioteca, n_livros, return_value);
					--n_livros;
				}
				break;
			case 7:
				return_value=procuraLivroIsbn(biblioteca, n_livros);
				if( return_value >=0 )
					insereEmprestimoBib(biblioteca, return_value);
				break;
			case 8:
				return_value=procuraLivroIsbn(biblioteca, n_livros);
				if( return_value >=0 )
					insereDevolucaoBib(biblioteca, return_value);
				break;
			default:
				opcao=0;
		}
		printf("\n\n");

	} while(opcao!=0);

	return 0;
}
