# include <stdio.h>


void quadrado(int);


void quadrado(int N){

	int i, j;
	char cell='0';

	for(i=0; i<N; ++i){
		for(j=1; j<=N; ++j){
			putchar(cell+j%10+i%10);
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');
	}

}


int main(){

	int N=0;

	while(N<2){
		printf("Número maior do que 2: ");
		scanf("%d", &N);
	}

	quadrado(N);

	return 0;
}
