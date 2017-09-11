#include <stdio.h>


int maior_int(int a, int b, int c);


int maior_int(int a, int b, int c){
	int res;
	res=a;
	if (b>res) res=b;
	if (c>res) res=c;

	return res;
}





int main(){

	int a,b,c;
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	printf("O maior número era: %d\n", maior_int(a,b,c));

	return 0;


}
