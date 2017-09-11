# include <stdlib.h>


int main(void){

	int a;
	int *b=&a;
	int **c=&b;
	int *v[20];
	int* (*func)(int, int);
	void *(*func2[10])();

	return 0;
}

