/*
// Projeto SO - exercicio 1, version 03
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
// Ficheiro: sequential.c
*/

# include <stdlib.h>
# include "simul.h"
# include "../lib/matrix2d.h"


/*--------------------------------------------------------------------
| Function: simul_seq
---------------------------------------------------------------------*/

DoubleMatrix2D *simul_seq(DoubleMatrix2D *matrix, int linhas, int colunas, int nIter) {

	DoubleMatrix2D *m, *aux, *tmp;
	int	 i, j;

	if(linhas < 2 || colunas < 2)
		exit(EXIT_WRONG_ARGS);

	m = matrix;
	aux = dm2dNew(linhas, colunas);
	dm2dCopy(aux, m);

	for (; nIter >= 0; nIter--) {

		for (i = 1; i < linhas - 1; i++)
			for (j = 1; j < colunas - 1; j++) {
				dm2dSetEntry(aux, i, j, next_value(m, i, j));
			}

		tmp = aux;
		aux = m;
		m = tmp;
	}

	dm2dFree(m);
	return aux;
}
