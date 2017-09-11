# define SIZE 140

# include <stdio.h>


int my_strlen_index(char string[]);
int my_strlen_ptr(char *string);


int my_strlen_index(char string[]){

	int i;

	for (i=0; string[i]!='\0'; ++i);

	return i;
}


int my_strlen_ptr(char *string){

	int i;

	for (i=0; *(string+i)!='\0'; ++i);

	return i;

}


int main(void){

	char v[SIZE];

	fgets(v, SIZE, stdin);

	/*Take away one, because of \n*/
	printf("Thru index: %d\n", my_strlen_index(v)-1);
	printf("Thru pointer arithmetic: %d\n", my_strlen_ptr(v)-1);

	return 0;
}
