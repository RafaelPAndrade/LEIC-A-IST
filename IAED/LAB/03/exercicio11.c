# include <stdio.h>
# define MAX 80
# define N_ALG 10

int leLinha(char []);
void contaAlgarismos(char [], int []);

int leLinha(char buffer[]){

	int c, i=0;
	while((c=getchar())!='\n' && c!=EOF){
		buffer[i]=c;
		++i;
	}

	buffer[i]='\0';
	return i;

}

void contaAlgarismos(char buffer[], int res[]){

	int i;

	for(i=0; buffer[i]!='\0'; ++i)
		if (buffer[i]>='0' && buffer[i]<='9')
			++res[buffer[i]-'0'];

}



int main(){

	char buffer[MAX];
	int i, res[N_ALG]={0};

	leLinha(buffer);
	contaAlgarismos(buffer, res);

	printf("Número de algarismos: \n");
	for(i=0; i<N_ALG; ++i)
		printf("%d:\t%d\n", i, res[i]);
	return 0;

}

