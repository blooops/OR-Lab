#ifndef LLP_H
#define LLP_H

#include "util.h"

// Reduce the given matrix to row echelon form
void row_echelon_form(Matrix* m) {

    int i,j;

    i = j = 0;

    // Loop till either last row or last column is reach
    while( i!=m->nrows && j!=m->ncols ) { 

        // ensure pivot element is non zero
        if(m->mat[i][j] == 0.0f) {

            int exchange_i = i+1;
            int found_alternate = 0;

            while(exchange_i < m->nrows) {

                if(m->mat[exchange_i][j] != 0.0f) {
                    row_exchange(m, i, exchange_i);
                    found_alternate = 1;
                }
                exchange_i++;
            }

            if(found_alternate == 0) {
                return;
            }
        }

        // Make pivot element 1.0f
        row_scaling(m, i, (float) (1 / m->mat[i][j]));

        // Reduce other values in column of the pivot element
        int k;
        for(k=0; k<m->nrows; k++) {
            if(k == i)
                continue;
            row_combine(m, k, i, -1.0f * m->mat[k][j]);
        }

        // increment i and j to next possible pivot
        i++;
        j++;
    }
}

// Return the rank of the given matrix
int get_rank(Matrix* m) {

    Matrix* m_copy = copy_matrix(m);
    row_echelon_form(m_copy);
 
    int rank = 0;
    int i,j;
    for(i=0; i<m->nrows; i++) {
        int not_zero_flag = 0;
        for(j=0; j<m->ncols; j++) {
            if(m_copy->mat[i][j] - 0.0f > 0.001f) {
                not_zero_flag = 1;
            }


        }

        if(not_zero_flag == 1)
            rank++;
    }

    free(m_copy);
    return rank;
}

// Solve a set of linear equations of form Ax = b using Gauss Elimination method.
// Assumptions: A = m*n mattrix, b = m*1 vector
// (Assumes that the set of equations is solvable using this method)
// (Returns NULL if any error occurs while solving)
Matrix* solve_gauss_elimination(Matrix* A, Matrix* b) {

    // Allocate memory for solution matrix
    Matrix* x = allocate(1, A->ncols);

    // Allocate memory and assign values to combined equation matrix [A | b]
    Matrix* comb = allocate(A->nrows, A->ncols + 1);
    int i,j;
    for(i=0; i<A->nrows; i++) {
        for(j=0; j<A->ncols; j++) {
            comb->mat[i][j] = A->mat[i][j];
        }
    }
    for(i=0; i<A->nrows; i++) {
        comb->mat[i][A->ncols] = b->mat[i][0];
    }


    // Reduce combined matrix to row-echelon form
    row_echelon_form(comb);

    for(i=0; i<x->ncols; i++) {
        x->mat[0][i] = comb->mat[i][comb->ncols-1];
    }


    free(comb);
    return x;
    
}

// Solve set of linear equations of form Ax = b using Jacobi iteration
// (Assumes that the set of equations is solvable using this method)
Matrix* solve_jacobi_iteration(Matrix* A, Matrix* b) {

}

#endif
