# include <stdio.h>
# define MAX 80

int get_palavra(char [], int);
int e_palindromo(char [], int);


int get_palavra(char buffer[], int n){

	int c, i=0;
	while((c=getchar())!='\n' && c!='\t' && c!=' ' && c!=EOF && i<n-1){
		buffer[i]=c;
		++i;
	}

	buffer[i]='\0';
	return i;

}


int e_palindromo(char buffer[], int n){

	int i;

	for(--n, i=0; i<n && buffer[i++]==buffer[n--]; );
	/*Anda na lista; operacoes   ^  pospostas ^ tratam de deslocar-se*/

	return (i>=n);
}


int main(){

	char buffer[MAX];
	int length, a;

	length=get_palavra(buffer, MAX);
	a=e_palindromo(buffer, length);
	if (a)
		printf("A palavra %s é um palíndromo\n", buffer);
	else
		printf("A palavra %s não é um palíndromo\n", buffer);
	return 0;

}

