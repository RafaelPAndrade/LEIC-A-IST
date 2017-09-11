# include <stdio.h>

int soma_impares(int,int);
int produto_pares(int,int);




int soma_impares(int a, int b){

	int maior, menor, i, res;
	if (a>b){maior=a; menor=b;}
	else {maior=b; menor=a;}
	res=0;
	for (i=menor+(menor%2==0); i<=maior; i=i+2){
		res+=i;
	}

	return res;

}

int produto_pares(int a, int b){

	int maior, menor, i, res;
	if (a>b){maior=a; menor=b;}
	else {maior=b; menor=a;}
	res=1;
	for (i=menor+(menor%2!=0); i<=maior; i=i+2){
		res=res*i;
	}

	return res;
}

int main(){

	int a, b;

	printf("Diga 2 números: ");
	scanf("%d", &a);
	scanf("%d", &b);


	printf("Soma de todos os impares entre %d e %d: %d\n",a,b,soma_impares(a,b));
	printf("Produto de todos os pares entre %d e %d: %d\n",a,b,produto_pares(a,b));


	return 0;
}
