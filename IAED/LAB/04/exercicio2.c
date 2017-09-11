# include <stdio.h>

# define DIM 2

typedef struct {
	float real;
	float imag;
} complexo ;


complexo leComplexo(void);
void leNComplexo(complexo [], int);


complexo leComplexo(void){

	complexo res;
	char sinal, i;

	scanf("%f%c%f%c", &res.real, &sinal, &res.imag, &i);
	if (sinal!='+')
		res.imag*=-1;

	return res;
}


void leNComplexo(complexo lista[], int n){

	for(n=n-1; n>=0; --n)
		lista[n]=leComplexo();

}


int main(){

	complexo lista[DIM];
	leNComplexo(lista, DIM);


	return 0;
}
