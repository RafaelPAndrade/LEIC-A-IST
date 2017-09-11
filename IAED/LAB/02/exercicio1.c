#include <stdio.h>

#define N_OF_INT 3


int char_to_int(char a[]);
int maior_int(int a[], int n);

int char_to_int(char a[]){
	int i,res;
	res = 0;
	for(i=0;'0'<=a[i] && a[i]<='9'; ++i ){
		res=res*10+(a[i]-'0');
		}

	return res;

}

int maior_int(int a[], int n){
	int res;
	res=a[n];
	for(n=n-1; n>=0; --n){
		if (a[n]>res){
			res=a[n];
		}
	}
	return res;
}





int main(){

	int i, j, num[N_OF_INT-1];
	char a[10],c;
	for(j=0; j<N_OF_INT; ++j){
		i=0;
		while( (c=getchar())!= EOF && c!='\n' ){
			a[i]=c;
			++i;
		}
		num[j]=char_to_int(a);
		printf("%d\n", num[j]);
	}

	printf("O maior número era: %d\n", maior_int(num, N_OF_INT-1));

	return 0;


}
