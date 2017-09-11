# include <stdio.h>

float pesoMinimo(float);
float pesoMaximo(float);
float imc(float, float);
void escreveCategoria(float);

float pesoMinimo(float altura){
	return 19*altura*altura;
}

float pesoMaximo(float altura){
	return 25*altura*altura;
}



float imc(float peso, float altura){
	return peso/(altura*altura);
}


void escreveCategoria(float indice){

	printf("Categoria: ");
	if (indice<=30){
		if (indice>=19){
			if (indice>=25) printf("Excesso de peso\n");
			else printf("Normal\n");
		}
		else printf("Magro\n");
	}
	else if (indice <= 40) printf("Obeso I\n");
	else printf("Obeso II\n");

}

int main(){
	float altura, peso, valor_imc;

	printf("Altura: ");
	scanf("%f", &altura);
	printf("Peso: ");
	scanf("%f", &peso);
	valor_imc=imc(peso, altura);

	printf("\nO seu peso mínimo (para IMC normal) é: %.2f\n", pesoMinimo(altura));
	printf("O seu peso máximo (para IMC normal) é: %.2f\n", pesoMaximo(altura));
	printf("O seu IMC atual  é: %.2f\n", valor_imc);
	escreveCategoria(valor_imc);

	return 0;

}
