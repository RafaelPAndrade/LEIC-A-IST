/*
// Projeto SO - main0.c
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
*/

#include <stdio.h>
#include <stdlib.h>
#include "error_handling.h"
#include "../lib/matrix2d.h"
#include "simul.h"


int parse_integer_or_exit(char const *str, char const *name);
double parse_double_or_exit(char const *str, char const *name);


/*--------------------------------------------------------------------
| Function: main
---------------------------------------------------------------------*/

int main (int argc, char** argv) {

	DoubleMatrix2D *matrix, *result;

	if(argc < 6) {
		fprintf(stderr, "\nNumero invalido de argumentos.\n");
		fprintf(stderr, "Uso: heatSim N tEsq tSup tDir tInf iteracoes\n\n");
		exit(EXIT_WRONG_ARGS);
	}

	/* argv[0] = program name */
	int N = parse_integer_or_exit(argv[1], "N");
	double tEsq = parse_double_or_exit(argv[2], "tEsq");
	double tSup = parse_double_or_exit(argv[3], "tSup");
	double tDir = parse_double_or_exit(argv[4], "tDir");
	double tInf = parse_double_or_exit(argv[5], "tInf");
	int iteracoes = parse_integer_or_exit(argv[6], "iteracoes");


	fprintf(stderr, "\nArgumentos:\n"
	" N=%d tEsq=%.1f tSup=%.1f tDir=%.1f tInf=%.1f iteracoes=%d",
	N, tEsq, tSup, tDir, tInf, iteracoes);

	// Error checking
	if(N < 1 || tEsq < 0 || tSup < 0 || tDir < 0 || tInf < 0 || iteracoes < 1 ) {
		fprintf(stderr, "\nErro: Argumentos invalidos.\nLembrar que N >= 1, temperaturas >= 0, iteracoes >= 1\n\n");
		exit(EXIT_WRONG_ARGS);
	}

	matrix = dm2dNew(N+2, N+2);
	if (matrix == NULL) {
		fprintf(stderr, "\nErro: Nao foi possivel alocar memoria para as matrizes.\n\n");
		exit(EXIT_MEM_ALLOC);
	}


	dm2dSetLineTo (matrix, 0, tSup);
	dm2dSetLineTo (matrix, N+1, tInf);
	dm2dSetColumnTo (matrix, 0, tEsq);
	dm2dSetColumnTo (matrix, N+1, tDir);


	// - Sequential version
	result = simul_seq(matrix, N+2, N+2, iteracoes);

	dm2dPrint(result);
	dm2dFree(result);
	return 0;
}
