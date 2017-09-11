#include <stdio.h>

#define MEM_SIZE 1000

float maior_float(float a[], int n);
float menor_float(float a[], int n);


float maior_float(float a[], int n){
	float res;
	int i;
	res=a[0];
	for (i=1; i<n; ++i)
		if (a[i]>res) res=a[i];
	return res;
}

float menor_float(float a[], int n){
	float res;
	int i;
	res=a[0];
	for (i=1; i<n; ++i)
		if (a[i]<res) res=a[i];
	return res;
}


int main(){

	float a[MEM_SIZE];
	int i, N;
	printf("Quantos números no imput? \n");
	scanf("%d", &N);

	for (i=0; i<=N-1 && i< MEM_SIZE; ++i){
		scanf("%f", &a[i]);
	}


	printf("O maior número era: %.3f\n", maior_float(a, N));
	printf("O menor número era: %.3f\n", menor_float(a, N));

	return 0;


}
