# include <stdio.h>

# define VECMAX 80


void leVETOR(int [], int);
int somaVETOR(int [], int);


void leVETOR(int vector[], int n){

	int i;

	for(i=0; i<n; ++i)
		scanf("%d", &vector[i]);

}


int somaVETOR(int vector[], int n){
	int res, i;
	for(i=0; i<n; ++i)
		res+=vector[i];

	return res;
}



int main(){

	int vetor[VECMAX], n=0;
	do{
	printf("Introduza o n de inteiros a ler: ");
	scanf("%d", &n);
	} while(n<1 || n>=VECMAX);

	leVETOR(vetor, n);
	printf("A soma dos números inteiros é: %d\n", somaVETOR(vetor, n));

	return 0;
}
