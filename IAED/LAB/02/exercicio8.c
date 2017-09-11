# include <stdio.h>


float proximaApolice(float, int, int);


float proximaApolice(float apolice, int idade, int n_acidentes){

	if (idade >=25){
		if (n_acidentes<2){
			if (n_acidentes==1)
				return apolice;
			else if (n_acidentes==0)
				return apolice*0.8;
			}
		else if (n_acidentes<5)
			return apolice*1.3;
	}

	else if (idade < 25){
		if (n_acidentes<2){
			if (n_acidentes==1)
				return apolice*1.05;
			else if (n_acidentes==0)
				return apolice*0.85;
			}
		else if (n_acidentes<5)
			return apolice*1.5;
	}

	return 0;
}



int main(){

	int idade, n_acidentes;
	float apolice, apolice_futura;

	printf("Idade: ");
	scanf("%d", &idade);

	printf("N de acidentes: ");
	scanf("%d", &n_acidentes);

	printf("Apolice: ");
	scanf("%f", &apolice);

	apolice_futura=proximaApolice(apolice, idade, n_acidentes);

	if (apolice_futura>=0.01)
		printf("\nA sua próxima apólice é: %.2f\n", apolice_futura);
	else
		printf("\nA sua apolice foi recusada\n");
	return 0;
}
