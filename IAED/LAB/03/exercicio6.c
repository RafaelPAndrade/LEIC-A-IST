# include <stdio.h>

# define VECMAX 80


void leVETOR(int [], int);
void inverteVETOR(int [], int);


void leVETOR(int vector[], int n){

	int i;

	for(i=0; i<n; ++i)
		scanf("%d", &vector[i]);

}


void inverteVETOR(int vector[], int n){

	int a,c;

	for(c=0; c<=n/2 - 1; ++c){
		a=vector[c];
		vector[c]=vector[n-1-c];
		vector[n-1-c]=a;
	}
}




int main(){

	int vetor[VECMAX], n=0, c;

	do{
	printf("Introduza o n de inteiros a ler: ");
	scanf("%d", &n);
	} while(n<1 || n>=VECMAX);


	leVETOR(vetor, n);

	inverteVETOR(vetor, n);

	printf("%d\n\n", n/2);
	for(c=0; c<n; ++c)
		printf("%d\n", vetor[c]);
	return 0;
}

