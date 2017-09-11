#define NUMEROLIVROS 100
#define MAXTITULO 40
#define MAXNOME 20


/*Estruturas de dados*/
	/*Data*/
typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

	/*Livro*/
typedef struct {
	char titulo[MAXTITULO+1];
	char autor[MAXNOME+1];
	long int isbn;
	int anoPublicacao;
	int numeroDaCopia;
	Data dataEmprestimo;
	Data dataRetorno;
} Livro;


/*Funcoes*/
void mostraMenu(void);					/*Apresenta um menu*/

Data insereData(void);					/*Retorna uma data*/
void mostraData(const Data);			/*Mostra uma data*/

/*Funcoes de livro (obsoletas)*/
void mostraLivro(const Livro);			/*Apresenta os dados do livro*/

/*Funcoes procura*/
int procuraLivroIsbn(const Livro [], int);				/*Procura livro pelo numero isbn*/
int procuraLivroTitulo(const Livro [], int);			/*Procura livro pelo seu titulo*/

/*Funcoes biblioteca*/
void insereLivroBiblioteca(Livro [], const int);
void listaLivros(const Livro [], const int);
void alteraTituloBiblioteca(Livro [], const int);		/*Retorna um livro com o titulo alterado*/
void insereEmprestimoBib(Livro [], const int);			/*Altera a data de emprestimo de um livro dentro de uma biblioteca*/
void insereDevolucaoBib(Livro [], const int);			/*Retorna um livro com a data do devolucao alterada  */

void apagaLivro(Livro [], const int, const int);					/*apaga um livro, segundo o index */


void Erro(int);											/*Mostra uma mensagem de erro*/
