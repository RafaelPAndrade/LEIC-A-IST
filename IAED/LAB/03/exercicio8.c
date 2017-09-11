# include <stdio.h>
# define MAX 80

int leLinha(char []);

int leLinha(char buffer[]){

	int c, i=0;
	while((c=getchar())!='\n' && c!=EOF){
		buffer[i]=c;
		++i;
	}

	buffer[i]='\0';
	return i;

}


int main(){

	char buffer[MAX];
	int length;

	length=leLinha(buffer);
	if (length>0)
		printf("%s\n", buffer);
	else
		printf("A string estava vazia\n");
	return 0;

}

