# include <stdio.h>

# define VECMAX 80


void leVETOR(int [], int);
void escreveVETOR(int [], int);



void leVETOR(int vector[], int n){

	int c, i;

	for(i=0; (c=getchar())!=EOF && i<n; ++i)
		vector[i]=c;

}

void escreveVETOR(int vector[], int n){

	int i;

	for(i=0; i<n; ++i)
		putchar(vector[i]);

}



int main(){

	int vetor[VECMAX], n=0;
	do{
	printf("Introduza o n de caracteres a ler: ");
	scanf("%d", &n);
	} while(n<1 || n>=VECMAX);

	leVETOR(vetor, n);
	escreveVETOR(vetor, n);

	return 0;
}
