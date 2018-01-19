/*
// Biblioteca de matrizes 2D alocadas dinamicamente, versao 4
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
*/

#include "matrix2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*--------------------------------------------------------------------
| Function: dm2dNew
---------------------------------------------------------------------*/

DoubleMatrix2D* dm2dNew(int lines, int columns) {
  int i, j;
  DoubleMatrix2D* matrix = malloc(sizeof(DoubleMatrix2D));

  if (matrix == NULL)
    return NULL;

  matrix->n_l = lines;
  matrix->n_c = columns;
  matrix->data = (double*) malloc(sizeof(double)*lines*columns);
  if (matrix->data == NULL) {
    free (matrix);
    return NULL;
  }

  for (i=0; i<lines; i++)
    for (j=0; j<columns; j++)
      dm2dSetEntry(matrix, i, j, 0);

  return matrix;
}

/*--------------------------------------------------------------------
| Function: dm2dFree
---------------------------------------------------------------------*/

void dm2dFree (DoubleMatrix2D *matrix) {
    free (matrix->data);
    free (matrix);
}

/*--------------------------------------------------------------------
| Function: dm2dGetLine
---------------------------------------------------------------------*/

double* dm2dGetLine (DoubleMatrix2D *matrix, int line_nb) {
  return &(matrix->data[line_nb*matrix->n_c]);
}

/*--------------------------------------------------------------------
| Function: dm2dSetLine
---------------------------------------------------------------------*/

void dm2dSetLine (DoubleMatrix2D *matrix, int line_nb, double* line_values) {
    memcpy ((char*) &(matrix->data[line_nb*matrix->n_c]), line_values, matrix->n_c*sizeof(double));
}

/*--------------------------------------------------------------------
| Function: dm2dSetLineTo
---------------------------------------------------------------------*/

void dm2dSetLineTo (DoubleMatrix2D *matrix, int line, double value) {
  int i;

  for (i=0; i<matrix->n_c; i++)
    dm2dSetEntry(matrix, line, i, value);
}


/*--------------------------------------------------------------------
| Function: dm2dSetColumnTo
---------------------------------------------------------------------*/

void dm2dSetColumnTo (DoubleMatrix2D *matrix, int column, double value) {
  int i;

  for (i=0; i<matrix->n_l; i++)
    dm2dSetEntry(matrix, i, column, value);
}

/*--------------------------------------------------------------------
| Function: dm2dCopy
---------------------------------------------------------------------*/

void dm2dCopy (DoubleMatrix2D *to, DoubleMatrix2D *from) {
  memcpy (to->data, from->data, sizeof(double)*to->n_l*to->n_c);
}


/*--------------------------------------------------------------------
| Function: dm2dPrint
---------------------------------------------------------------------*/

void dm2dPrint (DoubleMatrix2D *matrix) {
  int i, j;

  printf ("\n");
  for (i=0; i<matrix->n_l; i++) {
    for (j=0; j<matrix->n_c; j++)
      printf(" %8.4f", dm2dGetEntry(matrix, i, j));
    printf ("\n");
  }
}


/*--------------------------------------------------------------------
| Function: dm2dPrintToFile
---------------------------------------------------------------------*/
void dm2dPrintToFile(DoubleMatrix2D *matrix, FILE *file) {
  int i, j;

  for (i=0; i<matrix->n_l; i++) {
    for (j=0; j<matrix->n_c; j++)
      fprintf(file, " %8.4lf", dm2dGetEntry(matrix, i, j));
    fprintf (file, "\n");
  }
  int fflush(FILE *stream);
}

/*--------------------------------------------------------------------
| Function: readMatrix2dFromFile
---------------------------------------------------------------------*/
DoubleMatrix2D *readMatrix2dFromFile(FILE *f, int l, int c) {
  int i, j;
  double v;
  DoubleMatrix2D *m;

  if (f == NULL || l<1 || c<1)
    return NULL;

  m = dm2dNew(l, c);
  if (m==NULL)
    return NULL;

  //Ler pontos da matriz
  //Nesta implementacao, ignora a existencia e posicionamento
  //de quebras de linha
  for (i = 0; i < l; i++) {
    for (j = 0; j < c; j++) {
      if (fscanf(f, "%lf", &v) != 1) {
				dm2dFree(m);
				return NULL;
      }
      dm2dSetEntry(m, i, j, v);
    }
  }
  return m;
}
