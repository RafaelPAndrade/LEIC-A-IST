# include <stdio.h>

# define N 5

typedef struct {
	float dinheiro;
	float tan;
} deposito;


deposito leDeposito(void);
void leNDepositos(deposito [], int);
float calculaMediaTAN(deposito [], int);

deposito leDeposito(void){

	deposito res;

	printf("Quanto dinheiro: ");
	scanf("%f", &res.dinheiro);
	printf("A sua TAN: ");
	scanf("%f", &res.tan);

	return res;
}

void leNDepositos(deposito buffer[], int n){

	for(n=n-1; n>=0; --n)
		buffer[n]=leDeposito();

}


float calculaMediaTAN(deposito buffer[], int n){

	float somaTAN;
	int i;

	for(i=0; i<n; ++i)
		somaTAN+=buffer[i].tan;

	return somaTAN/i;

}



int main(){

	deposito buffer[N];

	leNDepositos(buffer, N);

	printf("A média das TAN é %f\n",calculaMediaTAN(buffer, N) );

	return 0;
}




