#include "Utils.h"

float** Simplex_standard(float** simplex, int m, int n, int flag) {
    /*
     * Assumes the following:
     *      Simplex initial table has been prepared
     *      Initial BFS has been generated in tableau
     *      m = no. of neqs; n = no. of variables (including slack)
     */

     int i, j, k;
     float max_Del; int max_Del_index;
     float min_Ratio; int min_Ratio_index; int unbounded;

     // Calculating Zj's in row m+1 (Zj stored in  simplex[m+1][j])
     for(i = 1; i <= m; i++) {
         for(j = 1; j <= n; j ++) {
             simplex[m + 1 + ROWOFF][j + COLOFF] += simplex[i + ROWOFF][j + COLOFF];
         }
     }

     // Finding entering variable (most positive Cj - Zj)
     max_Del = 0; max_Del_index = -1;
     for(j = 1; j <= n; j++) {
         simplex[m + 1 + ROWOFF][j + COLOFF] = simplex[0][j + COLOFF]
                                        - simplex[m + 1 + ROWOFF][j + COLOFF];
         if(max_Del < simplex[0][j + COLOFF] - simplex[m + 1 + ROWOFF][j + COLOFF]) {
             max_Del = simplex[0][j + COLOFF] - simplex[m + 1 + ROWOFF][j + COLOFF];
             max_Del_index = j;
         }
     }

     // Optimality reached, exit
     if(max_Del == 0 && max_Del_index == -1)
        return simplex;

    // Check for minimum ratio among computable ratios
    min_Ratio = 10000000.0f; min_Ratio_index = -1;
    for(i = 1; i <= m; i++) {
        simplex[i + ROWOFF][n + 1 + COLOFF] = simplex[i + ROWOFF][max_Del_index + COLOFF]
                / simplex[i + ROWOFF][n + 1 + COLOFF];
        if(simplex[i + ROWOFF][max_Del_index + COLOFF] == 0 ||
           simplex[i + ROWOFF][n + COLOFF] == 0)
           continue;
        else if(min_Ratio > simplex[i + ROWOFF][max_Del_index + COLOFF]
                / simplex[i + ROWOFF][n + 1 + COLOFF]) {
             min_Ratio = simplex[i + ROWOFF][max_Del_index + COLOFF]
                        / simplex[i + ROWOFF][n + 1 + COLOFF];
             min_Ratio_index = i;
        }
    }

    Print_Tableau(simplex, m, n);

    // Check if result unbounded, quit
    if(min_Ratio_index == -1) {
        simplex[0][0] = -1.0f;
        return simplex;
    }

    // Pivot element is found at indices obtained so far, now perform
    // Gauss elimination
    Gauss_Eliminate(simplex, m, n + 1, min_Ratio_index,
                    max_Del_index);

    // Exchange entering and leaving variables
    simplex[min_Ratio_index + ROWOFF][1] = max_Del_index;
    simplex[min_Ratio_index + ROWOFF][0] = simplex[0][max_Del_index + COLOFF];



}

float** Simplex_Big_M(float** simplex, int m, int n, int flag) {

}

float** Simplex_Two_Phase(float** simplex, int m, int n, int flag) {

}

float** Simplex_Dual(float** simplex, int m, int n, int flag) {

}

float** Prepare_simplex_table() {

}

void Gauss_Eliminate(float** matrix, int nrows, int ncols, int prow, int pcol) {
    int i, j;

    for(j = 1; j <= ncols; j++)
        matrix[prow + ROWOFF][j + COLOFF] /= matrix[prow + ROWOFF][pcol + COLOFF];

    for(i = 1; i <= nrows; i++) {
        if(i == prow)
            continue;

        for(j = 1; j <= ncols; j++) {
            matrix[i + ROWOFF][j + COLOFF] -= matrix[prow + ROWOFF][j + COLOFF]
                    * matrix[i + ROWOFF][pcol + COLOFF];
        }
    }
}

void Print_Tableau(float** simplex, int m, int n) {
    int i, j;
    printf("\n");
    for(i = 0; i <= 1 + m; i++) {
        for(j = 0; j <= 3 + n; j++) {
            printf(" %6.3f ", simplex[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
