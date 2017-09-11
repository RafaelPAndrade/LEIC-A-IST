# include <stdio.h>


typedef struct {
	float dinheiro;
	float tan;
} deposito;



deposito leDeposito(void);
void mostraDeposito(deposito);


deposito leDeposito(void){

	deposito res;

	printf("Quanto dinheiro: ");
	scanf("%f", &res.dinheiro);
	printf("A sua TAN: ");
	scanf("%f", &res.tan);

	return res;
}


void mostraDeposito(deposito d){

	printf("O deposito tem %.2f€ e a TAN é %f\n", d.dinheiro, d.tan);

}

int main(){

	mostraDeposito(leDeposito());

	return 0;
}
