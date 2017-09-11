# include <stdio.h>

# define DIM1 5
# define DIM2 7

void leMatriz(float [][DIM2], int, int);
void escreveMediaColunas(float [][DIM2], int, int);
void escreveMinimoLinhas(float [][DIM2], int, int);


void leMatriz(float tempos[][DIM2], int n_atletas, int n_sessoes){

	int i, j;

	for(i=0; i<n_atletas; ++i){
		printf("Tempos do atleta n. %d: ",i);
		for(j=0; j<n_sessoes;++j)
			scanf("%f", &tempos[i][j]);
	}


}


void escreveMediaColunas(float tempos[][DIM2], int n_atletas, int n_sessoes){

	float res;
	int i,j;
	for(i=0; i<n_sessoes; ++i){
		for(j=res=0; j<n_atletas; ++j)
			res+=tempos[j][i];
		printf("Média da sessão %d: %.2f\n", i, res/n_atletas);
	}

}


void escreveMinimoLinhas(float tempos[][DIM2], int n_atletas, int n_sessoes){

	float res;
	int i,j;
	for(i=0; i<n_atletas; ++i){
		res=tempos[i][0];
		for(j=1; j<n_sessoes; ++j)
			if (tempos[i][j]< res)
				res=tempos[i][j];
		printf("Melhor tempo do atleta %d: %.2f\n", i, res);
	}


}

int main(){

	float tempos[DIM1][DIM2];

	leMatriz(tempos, DIM1, DIM2);
	escreveMediaColunas(tempos, DIM1, DIM2);
	putchar('\n');
	escreveMinimoLinhas(tempos, DIM1, DIM2);

	return 0;
}
