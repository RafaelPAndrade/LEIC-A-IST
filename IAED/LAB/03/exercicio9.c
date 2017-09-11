# include <stdio.h>
# define MAX 80

int leLinha(char []);
void maiusculas(char []);

int leLinha(char buffer[]){

	int c, i=0;
	while((c=getchar())!='\n' && c!=EOF){
		buffer[i]=c;
		++i;
	}

	buffer[i]='\0';
	return i;

}

void maiusculas(char buffer[]){

	int i;

	for(i=0; buffer[i]!='\0'; ++i)
		if (buffer[i]>='A' && buffer[i]<='Z')
			buffer[i]+='a'-'A';

}



int main(){

	char buffer[MAX];

	leLinha(buffer);
	maiusculas(buffer);
	printf("%s\n", buffer);
	return 0;

}

