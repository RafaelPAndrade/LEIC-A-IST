# include <stdio.h>


int main(){

	int num=-1, count, n_digit=0, sum_digit=0, c;
	count=0;


	printf("Insira um número inteiro positivo: ");


	while ( ( !(c = scanf("%d", &num)) || num<=0 ) && count< 10 ) {
		printf("%d %d Número inválido! Tente outra vez: ",num, c);
		++count;
	}



	while(num>0){
		++n_digit;
		sum_digit+= num%10;
		num=num/10;
	}


	printf("Número de dígitos: %d\nSoma de dígitos: %d\n", n_digit, sum_digit);
	return 0;
}
