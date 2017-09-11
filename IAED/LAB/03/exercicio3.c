# include <stdio.h>

# define VECMAX 80


void leVETOR(int [], int);
int maximoVETOR(int [], int);
int minimoVETOR(int [], int);


void leVETOR(int vector[], int n){

	int i;

	for(i=0; i<n; ++i)
		scanf("%d", &vector[i]);

}


int maximoVETOR(int vector[], int n){

	int res;
	--n;
	res=vector[n];
	for(--n; n>=0; --n)
		if (vector[n]>res)
			res=vector[n];

	return res;
}

int minimoVETOR(int vector[], int n){

	int res;
	--n;
	res=vector[n];
	for(--n; n>=0; --n)
		if (vector[n]<res)
			res=vector[n];

	return res;
}


int main(){

	int vetor[VECMAX], n=0;
	do{
	printf("Introduza o n de inteiros a ler: ");
	scanf("%d", &n);
	} while(n<1 || n>=VECMAX);

	leVETOR(vetor, n);

	printf("Maximo elemento: %d\n", maximoVETOR(vetor, n));
	printf("Minimo elemento: %d\n", minimoVETOR(vetor, n));

	return 0;
}

