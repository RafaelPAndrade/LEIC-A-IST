# include <stdio.h>
# define ERROR_CODE -1

int getchar_inteiros(void);



int getchar_inteiros(){
	int c, res=0;

	while((c=getchar())!=EOF && c!='\n' && c!=' ' && c!='\t'){
		if (c>='0' && c<='9'){
			res=res*10+(c-'0');
		}
		else{
		for(;(c=getchar())!=EOF && c!='\n';);
		return ERROR_CODE;
		}
	}
	return res;
}

int main(){

	int num=-2, n_digit=0, sum_digit=0;


	do{
		printf("Insira um número inteiro positivo: ");
		num=getchar_inteiros();
		putchar('\n');
	}
	while ( num<=0 );


	while(num>0){
		++n_digit;
		sum_digit+= num%10;
		num=num/10;
	}


	printf("Número de dígitos: %d\nSoma de dígitos: %d\n", n_digit, sum_digit);
	return 0;
}


