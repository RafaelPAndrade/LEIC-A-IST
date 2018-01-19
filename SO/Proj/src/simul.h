/*
// Projeto SO - exercicio 1, version 03
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
// Ficheiro simul.h
*/

# ifndef __SIMUL__
# define __SIMUL__


# include "../lib/matrix2d.h"
# include "error_handling.h"


# define next_value(m, i, j)  (dm2dGetEntry(m, i-1, j) + dm2dGetEntry(m, i+1, j) + \
                               dm2dGetEntry(m, i, j-1) + dm2dGetEntry(m, i, j+1) ) / 4.0;


DoubleMatrix2D * simul_seq(DoubleMatrix2D * matrix, int linhas, int colunas, int nIter);

DoubleMatrix2D * simul_t_m(DoubleMatrix2D * matrix, int linhas, int colunas, int nIter, int trab, int csz);

DoubleMatrix2D * simul_t_s(DoubleMatrix2D * matrix, int linhas, int colunas, int nIter, int trab, double maxD);

DoubleMatrix2D * simul_t_s_f(DoubleMatrix2D * matrix, int linhas, int colunas, int nIter, int trab, double maxD, char* fichS, int periodoS);


# endif
