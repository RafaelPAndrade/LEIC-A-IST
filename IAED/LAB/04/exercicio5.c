# include <stdio.h>

# define IMPOSTO 0.21

typedef struct {
	float dinheiro;
	float tan;
} deposito;



deposito leDeposito(void);
void mostraDeposito(deposito);
void calculaJuros(deposito, float []);

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

void calculaJuros(deposito d, float res[]){

	res[0]=d.dinheiro*d.tan;
	res[1]=res[0]*(1-IMPOSTO);

}




int main(){

	float juros[2];	/*res[0]-juro bruto; res[1]-juro liquido*/

	calculaJuros(leDeposito(), juros);

	printf("Juros brutos: %f€\nJuros líquidos: %.2f€\n", juros[0], juros[1]);
	return 0;
}




