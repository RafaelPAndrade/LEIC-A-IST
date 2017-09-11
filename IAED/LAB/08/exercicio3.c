# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_LEN_CODE 10
# define MAX_NOTA 20


typedef struct {
	int num_aluno;
	char *cod_disc;
	int nota;
} Inscricao;


void freeInscricao(Inscricao);
void mostraInscricao(Inscricao);
Inscricao * lerInscricoes(int n);
int * distribuicaoNotas(Inscricao * ins, int n, char * disc);


void mostraInscricao(Inscricao n){
	printf("%d:%s:%d\n", n.num_aluno, n.cod_disc, n.nota);
}




void freeInscricao(Inscricao n){
	free(n.cod_disc);
}


Inscricao* lerInscricoes(int n){

	int i;
	Inscricao * res = (Inscricao *) malloc(sizeof(Inscricao)*n);

	for (i=0; i<n; ++i) {
		printf("A ler o %d-esimo:\n", i+1);
		scanf("%d", &res[i].num_aluno);

		getchar();	//Tirar o \n antes
		res[i].cod_disc = (char *) malloc( sizeof(char)*(MAX_LEN_CODE+1) );
		scanf("%s", res[i].cod_disc);

		do {
		printf("Nota: ");
		scanf("%d", &res[i].nota);
		} while( res[i].nota<0 || res[i].nota>MAX_NOTA);

	}

	return res;
}



int * distribuicaoNotas(Inscricao * ins, int n, char * disc){

	int i, *distr;

	distr= (int *) calloc(MAX_NOTA+1, sizeof(int));

	for (i=0; i<n; ++i)
		if ( !strcmp(disc, ins[i].cod_disc) ){
			printf("A match with %d\n", i);
			++distr[ins[i].nota];
		}

	printf("Fim das matches!\n");
	return distr;

}


int main(){

	int n, i, *distr;
	char buffer[MAX_LEN_CODE+1];
	Inscricao * ins;

	printf("Quantas inscricoes?\n");
	scanf("%d", &n);

	ins= lerInscricoes(n);

	printf("Insira o nome de uma cadeira: ");
	scanf("%s", buffer);


	distr= distribuicaoNotas(ins, n, buffer);

	for (i=0; i<=MAX_NOTA; ++i)
		printf("%d:\t%d\n", i, distr[i]);


	//Freeing stuff
	for (i=0; i<n; ++i)
		freeInscricao(ins[i]);

	free(distr);
	free(ins);
	return 0;
}
