# include <stdio.h>
# include <stdlib.h>

void le_n_numeros(int, int []);
void mostra_positivos(int, int []);



void le_n_numeros(int n, int vector[]){

	int i;

	printf("A ler inteiros...\n");

	for (i=0; i < n; ++i)
		scanf("%d", &vector[i]);

}

void mostra_positivos(int n, int vector[]){

	int i;

	printf("A imprimir positivos...\n");

	for (i=0; i<n; ++i)
		if (vector[i]>0)
			printf("%d\n", vector[i]);
}


int main(){

	int n, *v;

	printf("Quantos inteiros?\n");
	scanf("%d", &n);

	if (n>0) {
		v = (int *) malloc( sizeof(int)*n );
		le_n_numeros(n, v);
		mostra_positivos(n, v);
		free(v);
	}

	return 0;
}
