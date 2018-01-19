/*
// Projeto SO - main3.c
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "error_handling.h"
#include "../lib/matrix2d.h"
#include "simul.h"

/*--------------------------------------------------------------------
| Function: parse_integer_or_exit
---------------------------------------------------------------------*/

int parse_integer_or_exit(char const *str, char const *name);
double parse_double_or_exit(char const *str, char const *name);


/*--------------------------------------------------------------------
| Function: main
---------------------------------------------------------------------*/

int main (int argc, char** argv) {

	DoubleMatrix2D *matrix, *result;

	if(argc < 7) {
		fprintf(stderr, "\nNumero invalido de argumentos.\n");
		fprintf(stderr, "Uso: heatSim N tEsq tSup tDir tInf iteracoes [trab] [maxD] [fichS] [periodoS]\n\n");
		exit(EXIT_WRONG_ARGS);
	}

	/* argv[0] = program name */
	int N = parse_integer_or_exit(argv[1], "N");
	double tEsq = parse_double_or_exit(argv[2], "tEsq");
	double tSup = parse_double_or_exit(argv[3], "tSup");
	double tDir = parse_double_or_exit(argv[4], "tDir");
	double tInf = parse_double_or_exit(argv[5], "tInf");
	int iteracoes = parse_integer_or_exit(argv[6], "iteracoes");
	int trab = (argc >= 8 ) ? parse_integer_or_exit(argv[7], "trab") : 1 ;
	double maxD = (argc >= 9 ) ? parse_double_or_exit(argv[8], "maxD") : 0 ;
	char* fichS  = (argc >= 10) ? argv[9] : "NULL";
	int periodoS = (argc>=11)? parse_integer_or_exit(argv[10],"periodoS"):0;

	fprintf(stderr, "\nArgumentos:\n"
	" N=%d tEsq=%.1f tSup=%.1f tDir=%.1f tInf=%.1f iteracoes=%d trab=%d maxD=%f fichS=%s periodoS=%d",
	N, tEsq, tSup, tDir, tInf, iteracoes, trab, maxD, fichS, periodoS);

	// Error checking
	if(N < 1 || tEsq < 0 || tSup < 0 || tDir < 0 || tInf < 0 || iteracoes < 1||\
	   trab < 1 || maxD < 0 || periodoS < 0 ) {
		fprintf(stderr, "\nErro: Argumentos invalidos.\nLembrar que N >= 1, "
		        "temperaturas >= 0, iteracoes >= 1, trab >= 1, maxD >= 0 e periodoS >= 0\n\n");
		exit(EXIT_WRONG_ARGS);
	}

	if(N%trab) {
		fprintf(stderr, "\nErro: Numero de trabalhadores invalido.\n"
		        "Numero de threads tem de ser divisor de N\n");
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

	// - Threaded version (with shared memory and save to file)
	result = simul_t_s_f(matrix, N+2, N+2, iteracoes, trab, maxD, fichS, periodoS);

	if (result == NULL) {
		printf("\nErro na simulacao.\n\n");
		exit(EXIT_SIMUL);
	}

	dm2dPrint(result);
	dm2dFree(result);

	int retVal = unlink(fichS);
	if(retVal && errno != ENOENT) {
		errFileSystem(errno, fichS);
	}

	return 0;
}
