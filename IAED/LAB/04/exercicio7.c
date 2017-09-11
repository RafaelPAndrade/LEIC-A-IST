# include <stdio.h>

# define TAXA 0.21
# define N 5

typedef struct {
	float dinheiro;
	float tan;
} deposito;


deposito leDeposito(void);
void leNDepositos(deposito [], int);
void mostraDepositosJuros(deposito [], int);

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


void mostraDepositosJuros(deposito buffer[], int n){

	int i;

	for(i=0; i<n; ++i)
		printf("No proximo ano, o deposito %d vai ter %.2f€\n", i,
		buffer[i].dinheiro*(1+buffer[i].tan*(1-TAXA)));



}



int main(){

	deposito buffer[N];

	leNDepositos(buffer, N);

	mostraDepositosJuros(buffer, N);

	return 0;
}




