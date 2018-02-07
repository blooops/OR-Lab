#ifndef LLP_H
#define LLP_H

#include "util.h"
#include <math.h>
#define MAX_NO_STEPS 1000

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
    if(m_copy == NULL || m_copy->mat == NULL) {
        freem(m_copy);
        return -1;
    }
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

    freem(m_copy);
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

    if(x == NULL || x->mat==NULL || comb == NULL || comb->mat == NULL) {
        freem(x);
        freem(comb);
        return NULL;
    }
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


    freem(comb);
    return x;
    
}

// Return the MSDiff between two vectors
float SQR_DIFF(Matrix* x1, Matrix* x2) {

    int i;
    float value;
    for(i=0; i<x1->ncols; i++) {
        value += (x1->mat[0][i] - x2->mat[0][i]) * (x1->mat[0][i] - x2->mat[0][i]);
    }
    value = sqrt(value);
    return value;
}

// Solve set of linear equations of form Ax = b using Jacobi iteration
// (Assumes that the set of equations is solvable using this method)
Matrix* solve_jacobi(Matrix* originalA, Matrix* originalb) {

    Matrix* A = copy_matrix(originalA);
    Matrix* b = copy_matrix(originalb);
    Matrix* xi = allocate(1, A->ncols);
    Matrix* xf = allocate(1, A->ncols);

    if(A == NULL || b == NULL || xi == NULL || xf == NULL) {
        freem(A);
        freem(b);
        freem(xi);
        freem(xf);
        return NULL;
    }
    int no_steps = 0; // DEBUG

    while(no_steps <= MAX_NO_STEPS) {
        int i,j;
        
        for(i=0; i<A->ncols; i++) {
            float sigma = 0.0f;
            for(j=0; j<A->nrows; j++) {
                if(i!=j)
                    sigma += A->mat[i][j] * xi->mat[0][j];
            }

            xf->mat[0][i] = (b->mat[i][0] - sigma) / A->mat[i][i];

        }

        no_steps++;

        //printf("Iteration #%d\n", no_steps);
        //printm(xf);

        if(SQR_DIFF(xf, xi) < 0.001f) 
            break;

        else {
            for(i=0; i<A->ncols; i++) 
                xi->mat[0][i] = xf->mat[0][i];
        }

    }

    freem(A);
    freem(b);
    freem(xi);
    return xf;
}

// Defining structures for simplex method:
typedef struct simplex {
    Matrix* Cj;
    int* BV;
    Matrix* CBi;
    Matrix* coeff;
    Matrix* solutions;
    Matrix* ratios;
    Matrix* Zj;
    Matrix* Delj;
    int key_row;
    int key_col;
    float key_elem;
} Simplex;

// Function to allocate s Simplex* instance
// Return NULL in case of errors
Simplex* allocate_simplex(int nvars, int neqs ) {

    Simplex* sim;
    sim = (Simplex*) malloc(sizeof(Simplex));

    if(sim == NULL)
        return NULL;

    sim->Cj = allocate(1, nvars);
    sim->BV = (int*) malloc(neqs * sizeof(int));
    sim->CBi = allocate(neqs, 1);
    sim->coeff = allocate(neqs, nvars);
    sim->solutions = allocate(neqs, 1);
    sim->ratios = allocate(neqs, 1);
    sim->Zj = allocate(1, nvars);
    sim->Delj = allocate(1, nvars);
    sim->key_row = -1;
    sim->key_col = -1;
    sim->key_elem = 0.0f;

    if(sim->Cj == NULL || sim->BV == NULL || sim->CBi == NULL || 
            sim->coeff == NULL || sim->solutions == NULL || sim->ratios == NULL || 
            sim->Zj == NULL || sim->Delj == NULL) {
        freem(sim->Cj); 
        free(sim->BV);
        freem(sim->CBi);
        freem(sim->coeff);
        freem(sim->solutions);
        freem(sim->ratios);
        freem(sim->Zj);
        freem(sim->Delj);
        free(sim);
        return NULL;
    }

    return sim;

}

// Solve the optimization problem : maximize (cT * x) wrt constraint A * x = b
// Assumes slack variables have been added and everything is in standard form
// Returns NULL in case of any error
Matrix* solve_simplex(Matrix* A, Matrix* b, Matrix* c) {

    Simplex* sim = allocate_simplex(A->ncols, A->nrows);
    if(sim == NULL)
        return NULL;

    // sim created, now initialize the simplex structure
    int i,j;

    printf("First Iteration Details:\n");
    // Setting up Cjs

    printf("sim->Cj\n");
    for(i=0; i<sim->Cj->ncols; i++) {
        sim->Cj->mat[0][i] = c->mat[0][i];
    }
    printm(sim->Cj);

    // Setting up coeff
    printf("sim->coeff\n");
    for(i=0; i<sim->coeff->nrows; i++) {
        for(j=0; j<sim->coeff->ncols; j++) {
            sim->coeff->mat[i][j] = A->mat[i][j];
        }
    }
    printm(sim->coeff);

    // Setting up solutions
    printf("sim->solutions\n");
    for(i=0; i<sim->solutions->nrows;i++) {
        sim->solutions->mat[i][0] = b->mat[i][0];
    }
    printm(sim->solutions);

    // Setting up BV:
    int nvars = A->ncols;
    int neqs = A->nrows;
    int offset=0;
    printf("sim->BV\n");
    for(i=nvars-neqs; i<nvars; i++) {
        sim->BV[offset] = i;
        offset++;
    }
    for(i=0; i<neqs; i++)
        printf("%d\n ", sim->BV[i]);
    printf("\n");

    int nsteps = 0;

    while(nsteps <=10) {

        // Calculating CBi's based on the set BV
        for(i=0; i<sim->CBi->nrows; i++) {
            sim->CBi->mat[i][0] = sim->Cj->mat[0][sim->BV[i]] ;
        }

        // Calculating Zj's
        for(i=0; i<sim->Zj->ncols; i++) {
            for(j=0; j<sim->coeff->nrows; j++) {
                sim->Zj->mat[0][i] += sim->coeff->mat[j][i] * 
                sim->CBi->mat[j][0];
            }
        }

        // Calculating Delj's
        for(i=0; i<sim->Delj->ncols; i++) {
            sim->Delj->mat[0][i] = sim->Cj->mat[0][i] -
            sim->Zj->mat[0][i];
            sim->Delj->mat[0][i] *= -1;
        }


        // Finding key column ( Maximum value of Delj)
        float val = sim->Delj->mat[0][0];
        sim->key_col = 0;
        for(i=1; i<sim->Delj->ncols; i++) {
            if(val < sim->Delj->mat[0][i]) {
                sim->key_col = i;
                val = sim->Delj->mat[0][i];
            }
        }
        if(val > 0.0f)
            break;

        // Calculating sim->ratios:
        for(i=0; i<sim->ratios->nrows; i++) {
            if(sim->coeff->mat[i][sim->key_col] != 0.0f)
            sim->ratios->mat[i][0] = sim->solutions->mat[i][0] / 
            sim->coeff->mat[i][sim->key_col];

            else 
                sim->ratios->mat[i][0] = 100000000000000;
        }

        // Finding key_row (Minimize)
        val = sim->ratios->mat[0][0];
        sim->key_row = 0;
        for(i=1; i<sim->ratios->nrows; i++) {
            if(val > sim->ratios->mat[i][0]) {
                sim->key_row = i;
                val = sim->ratios->mat[i][0];
            }
        }


        // Caching value of key element
        sim->key_elem = sim->coeff->mat[sim->key_row][sim->key_col];

        // Exchanging the new basic variable for the exiting one
        sim->BV[sim->key_row] = sim->key_col;
        
        // Evaluating the new sim->coeff matrix and sim->solutions
        for(i=0; i<sim->coeff->ncols; i++) {
            sim->coeff->mat[sim->key_row][i] /= sim->key_elem;
        }
        sim->solutions->mat[sim->key_row][0] /= sim->key_elem;

        for(i=0; i<sim->coeff->nrows; i++) {
            if(i == sim->key_row)
                continue;
            sim->solutions->mat[i][0] -=
            sim->solutions->mat[sim->key_row][0] *
            sim->coeff->mat[i][sim->key_col];

            for(j=0; j<sim->coeff->ncols; j++) {
                sim->coeff->mat[i][j]  = sim->coeff->mat[i][j]
                - ( sim->coeff->mat[sim->key_row][j] 
                * sim->coeff->mat[i][sim->key_col]);
            }

        }

        nsteps++;


        printf("Calculated CBi = \n");
        printm(sim->CBi);
        printf("Calculated Zj = \n");
        printm(sim->Zj);
        printf("Calculated Delj = \n");
        printm(sim->Delj);
        printf("Found key column = %d\n", sim->key_col);
        printf("Calculated sim->ratios =\n");
        printm(sim->ratios);
        printf("Found key row = %d\n", sim->key_row);
        printf("Found key element's value = %8.3f\n", sim->key_elem);
        printf("Next Iteration #%d\n", nsteps);
        printf("Evaluated sim->coeff = \n");
        printm(sim->coeff);
        printf("Current sim->BV = \n");
        for(i=0; i<neqs; i++)
            printf("%d\n", sim->BV[i]);

    }
    return NULL;
}

#endif
















