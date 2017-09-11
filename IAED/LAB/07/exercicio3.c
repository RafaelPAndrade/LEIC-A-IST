# include <stdio.h>
# include <stdlib.h>

typedef struct {
	float real;
	float imag;
} complexo ;


complexo leComplexo(void);
void mostraComplexo(complexo);
complexo* soma(complexo*, complexo*);



complexo leComplexo(void){

	complexo res;
	char sinal, i;

	scanf("%f%c%f%c", &res.real, &sinal, &res.imag, &i);
	if (sinal!='+')
		res.imag*=-1;

	return res;
}

void mostraComplexo(complexo a){
	if (a.imag>=0)
		printf("%f+%fi\n", a.real, a.imag);
	else
		printf("%f%fi\n", a.real, a.imag);

}

complexo* soma(complexo *a, complexo *b){

	complexo *res= (complexo*) malloc(sizeof(complexo));

	res->real= a->real+b->real;
	res->imag= a->imag+b->imag;

	return res;
}



int main(){

	complexo a, b, *r;

	a=leComplexo();
	b=leComplexo();
	r=soma(&a, &b);

	mostraComplexo(*r);

	free(r);
	return 0;
}
