# include <stdio.h>


void converte(int, int []);


void converte(int sec, int res[]){
	res[0]= sec%60;
	res[1]=	sec%3600/60;
	res[2]= sec/(60*60);
}





int main(){
	int n, tempo[3];


	printf("Quantos segundos? ");
	scanf("%d",&n);
	converte(n, tempo);
	printf("%d:%02d:%02d\n", tempo[2], tempo[1], tempo[0]);


	return 0;
}
