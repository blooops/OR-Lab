#include "Utils.h"

float** Simplex_Standard(float** simplex, int m, int n, int flag) {
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

float** Prepare_Simplex_Table() {

    /*
     * Assumes the following:
     *      All variables are non negative (negative variables are to be
     *      tackled by user at input)
     *      number of variables does not account for slack variables
     */

    int i, j;
    int m, n;
    int type; int method;
    printf("Enter type of problem (1 - MAXIZATION / 2 - MINIMIZATION): \n");
    scanf("%d", &type);
    printf("Enter the number of variables : \n");
    scanf("%d", &n);
    printf("Enter the number of constraints : \n");
    scanf("%d", &m);

    float** simplex = (float**) malloc((m + 2) * sizeof(float*));
    for(i = 0; i <= m + 1; i++)
        simplex[i] = (float*) malloc((n + m + 4) * sizeof(float));

    // Inputting Objective Function details
    printf("Enter the details of Objective Function now:\n");
    printf("Enter the number of variables in OF :\n");
    int t_a; scanf("%d", &t_a);
    while(t_a--) {
        printf("Enter a variable number of OF :\n");
        int t_index; scanf("%d", &t_index);
        printf("Enter the coefficient of above mentioned variable :\n");
        scanf("%f", &simplex[0][t_index + COLOFF]);
    }

    // Inputting Constraints
    printf("Now Enter the details about the constraints :\n");
    t_a = 1;
    while(t_a <= m) {
        printf("Enter type of constraint (1 - > | 2 - <) :\n");
        int t_type; scanf("%d", &t_type);
        int t_i;
        for(t_i = 1; t_i  <= n; t_i++) {
            printf("Enter coefficient of variable %d :\n", t_i);
            scanf("%f", &simplex[t_a + ROWOFF][t_i + COLOFF]);
        }
        printf("Enter RHS of this inequality :\n");
        scanf("%f", &simplex[t_a + ROWOFF][t_i + COLOFF]);
        t_a++;
    }

    // User Inputs done, now verify solvability: TODO

}

void Gauss_Eliminate(float** matrix, int nrows, int ncols, int prow, int pcol) {
    // Function to perform Gauss Reduction (Row wise) to Simplex Tableau

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
    // Function to print the Simplex Tableau passed
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

int Validate_Algorithm(float** simplex, int m, int n, int algorithm) {

}
