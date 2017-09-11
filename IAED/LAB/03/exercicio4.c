# include <stdio.h>

# define VECMAX 80


void leVETOR(int [], int);
int encontrakVETOR(int [], int, int);


void leVETOR(int vector[], int n){

	int i;

	for(i=0; i<n; ++i)
		scanf("%d", &vector[i]);

}


int encontrakVETOR(int vector[], int n, int k){

	for(;--n>=0;)
		if (vector[n]==k)
			return n;
	return -1;
}


int main(){

	int vetor[VECMAX], n=0, k;

	do{
	printf("Introduza o n de inteiros a ler: ");
	scanf("%d", &n);
	} while(n<1 || n>=VECMAX);


	printf("Introduza o k a procurar: ");
	scanf("%d", &k);


	leVETOR(vetor, n);

	printf("Existe %d na posicao %d\n", k, encontrakVETOR(vetor, n, k));

	return 0;
}

