# include <stdio.h>
# include <stdlib.h>

typedef struct {
	int x;
	int y;
} Ponto;

typedef struct {
	Ponto se;
	Ponto id;
} Rectangulo;


Ponto * lePontos(int n);
void escrevePontos(Ponto *, int);
Rectangulo * defineRectangulo(Ponto *, int);



Ponto * lePontos(int n){

	int i;

	Ponto *res = (Ponto *) malloc( sizeof(Ponto)*n );

	for (i=0; i<n; ++i)
		scanf("%d %d", &res[i].x, &res[i].y);

	return res;
}


void escrevePontos(Ponto *vector , int n){

	int i;

	for (i=0; i<n; ++i)
		printf("(%d,%d)\n", vector[i].x, vector[i].y);
}



Rectangulo * defineRectangulo(Ponto *vector, int n){

	int i;
	Rectangulo *res = (Rectangulo *) malloc(sizeof(Rectangulo));

	int min_x= vector[0].x;
	int max_x= vector[0].x;
	int min_y= vector[0].y;
	int max_y= vector[0].y;

	for (i=1; i < n; ++i){
		if (vector[i].x < min_x)
			min_x=vector[i].x;
		else if (vector[i].x > max_x)
			max_x=vector[i].x;

		if (vector[i].y < min_y)
			min_y=vector[i].y;
		else if (vector[i].y > max_y)
			max_y=vector[i].y;
	}

	res->se.x= min_x;
	res->id.x= max_x;
	res->se.y= max_y;
	res->id.y= min_y;

	return res;

}



int main(){

	int n;
	Ponto *vector;
	Rectangulo *maior;


	printf("Quantos pontos?\n");
	scanf("%d", &n);

	vector= lePontos(n);
	escrevePontos(vector, n);
	maior= defineRectangulo(vector, n);

	printf("(%d, %d) e (%d, %d)\n", maior->se.x, maior->se.y, maior->id.x, maior->id.y);


	free(vector);
	free(maior);
	return 0;
}
