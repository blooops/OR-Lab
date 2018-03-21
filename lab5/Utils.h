#include <stdio.h>
#include <stdlib.h>

#define MIN -1
#define MAX 1
#define COLOFF 1
#define ROWOFF 0

float** Simplex_standard(float** simplex, int m, int n, int flag);
float** Simplex_Big_M(float** simplex, int m, int n, int flag);
float** Simplex_Two_Phase(float** simplex, int m, int n, int flag);
float** Simplex_Dual(float** simplex, int m, int n, int flag);
void Gauss_Eliminate(float** matrix, int nrows, int ncols, int prow, int pcol);
void Print_Tableau(float** simplex, int m, int n);
