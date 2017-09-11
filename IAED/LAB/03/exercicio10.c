# include <stdio.h>
# define MAX 80

/*Exercicio nao compreendido
Apagar!=por espaco em branco*/

int leLinha(char []);
void apagaCaracter(char [], char);

int leLinha(char buffer[]){

	int c, i=0;
	while((c=getchar())!='\n' && c!=EOF){
		buffer[i++]=c;
	}

	buffer[i]='\0';
	return i;

}

void apagaCaracter(char buffer[], char c){

	int i, j;

	for(i=j=0; buffer[i]!='\0'; ++i)
		if (buffer[i]!=c) {
			buffer[j++]=buffer[i];
		}
	buffer[j]='\0';
}



int main(){

	char buffer[MAX], c;

	leLinha(buffer);
	scanf("%c", &c);
	apagaCaracter(buffer, c);
	printf("%s\n", buffer);
	return 0;

}

