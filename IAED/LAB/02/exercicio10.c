# include <stdio.h>

void escreveCaracter(char, int);
void escreveNumerosAsc(int, int);
void escreveNumerosDesc(int, int);
void piramide(int);



void escreveCaracter(char c, int n){

	for(n=n; n>0; --n){
		putchar(c);
	}
}


void escreveNumerosAsc(int a, int b){

	for(a=a; a<=b; ++a){
		printf("%d\t", a);
	}
}

void escreveNumerosDesc(int a, int b){

	for(a=a; a>=b; --a){
		printf("%d\t", a);
	}
}



void piramide(int N){

	int i;

	for(i=1; i<=N; ++i){
		escreveCaracter('\t',(N-i));
		escreveNumerosAsc(1,i);
		escreveNumerosDesc(i-1,1); /*i-1 para nao repetir numeros no meio da piramide*/
		putchar('\n');
	}

}




int main(){

	int n=0;
	while(n<2){
		printf("Escreva um número, senhor Lívio: ");
		scanf("%d", &n);
	}
	piramide(n);
	return 0;
}
