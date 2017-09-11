# include <stdio.h>

# define VECMAX 80


void leVETOR(int [], int);
void quadradoVETOR(int [], int);


void leVETOR(int vector[], int n){

	int i;

	for(i=0; i<n; ++i)
		scanf("%d", &vector[i]);

}


void quadradoVETOR(int vector[], int n){

	for(n--; n>=0; --n)
		vector[n]=vector[n]*vector[n];

}




int main(){

	int vetor[VECMAX], n=0;

	do{
	printf("Introduza o n de inteiros a ler: ");
	scanf("%d", &n);
	} while(n<1 || n>=VECMAX);


	leVETOR(vetor, n);

	quadradoVETOR(vetor, n);

	printf("%d\n", vetor[n-1]);

	return 0;
}

