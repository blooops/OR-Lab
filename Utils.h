#include <stdio.h>
#include <stdlib.h>

// Problem types
#define MIN -1
#define MAX 1

// Offsets in tableau
#define COLOFF 1
#define ROWOFF 0

// Algorithm types
#define SIMPLEX 1
#define BIGM 2
#define TWOPHASE 3
#define DUALSIMPLEX 4

float** Simplex_Standard(float** simplex, int m, int n, int flag);
float** Simplex_Big_M(float** simplex, int m, int n, int flag);
float** Simplex_Two_Phase(float** simplex, int m, int n, int flag);
float** Simplex_Dual(float** simplex, int m, int n, int flag);
void Gauss_Eliminate(float** matrix, int nrows, int ncols, int prow, int pcol);
void Print_Tableau(float** simplex, int m, int n);
float** Prepare_Simplex_Table();
int Validate_Algorithm(float** simplex, int m, int n, int algorithm);
