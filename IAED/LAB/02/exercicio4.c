# include <stdio.h>



float media(int);



float media(int n){

	float res, temp;
	int i;

	for (i=n; i>0; --i){
		scanf("%f", &temp);
		res+=temp;
	}


	return res/n;
}
int main(){

	int a;
	float res;
	printf("Quantos floats irão ser dados? ");
	scanf("%d", &a);
	res=media(a);

	printf("A média é: %.2f\n", res);
	return 0;
}
