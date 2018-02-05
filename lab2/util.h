#ifndef UTIL_H
#define UTIL_H

#include "stdlib.h"

// Matrix Structure Definitions:

typedef struct Matrix {
    float** mat;
    int nrows, ncols;
} Matrix;

// Matrix specific function definitions

// Pretty print a matrix to console
void printm(Matrix* m) {
    int i, j;
    for(i=0; i<m->nrows; i++) {
        for(j=0; j<m->ncols; j++) {
            printf("%8.3f ", m->mat[i][j]);
        }
        printf("\n");
    }

}

// definition of free for Matrix* object. Use freem instead of free for Matrix* objects
void freem(Matrix* m) {
    if(m != NULL) {
        if(m->mat != NULL) {
            free(m->mat);
        }
        free(m);
    }
}

// Allocate memory for a matrix, initialize it with 0.0f and return pointer to it (NULL
// in case of allocation error)
Matrix* allocate(int nr, int nc) {

   Matrix* m = (Matrix*) malloc(sizeof(Matrix));
   if(m == NULL)
       return NULL;

   m->nrows = nr; m->ncols = nc;

   m->mat = (float**) malloc(sizeof(float*) * nr);
   if(m->mat == NULL) {
       free(m);
       return NULL;
   }

   int i;
   for(i=0; i<nr; i++) {
       m->mat[i] = (float*) malloc(sizeof(float) * nc);
   }

   if(m->mat == NULL) {
       free(m);
       return NULL;
   } 
   
   int j;
   for(i=0; i<m->nrows; i++) {
       for(j=0; j<m->ncols; j++) {
           m->mat[i][j] = 0.0f;
       }
   }
   return m;
}

// Make a copy of the given matrix
Matrix* copy_matrix(Matrix* m) {

    Matrix* n = allocate(m->nrows, m->ncols);
    if(n==NULL)
        return NULL;

    int i,j;
    for(i=0; i<n->nrows; i++) {
        for(j=0; j<n->ncols; j++) {
            n->mat[i][j] = m->mat[i][j];
        }
    }

    return n;
}

// Matrix addition (return NULL if error occurs or conditions aren't met)
Matrix* add(Matrix* a, Matrix* b) {

    if(a->nrows != b->nrows || a->ncols != b->ncols) 
        return NULL;
    
    Matrix* c = allocate(a->nrows, a->ncols);
    if(c == NULL)
        return NULL;

    int i, j;
    for(i=0; i<a->nrows; i++) {
        for(j=0; j<a->ncols; j++) {
            c->mat[i][j] = a->mat[i][j] + b->mat[i][j];
        }
    }

    return c;
}

// Matrix multiplication (return NULL if error occurs or conditions aren't met)
Matrix* mult(Matrix* a, Matrix* b) {

    if(a->ncols != b->nrows ) 
        return NULL;
    
    Matrix* c = allocate(a->nrows, b->ncols);
    if(c == NULL)
        return NULL;

    int i, j;
    for(i=0; i<a->nrows; i++) {
        for(j=0; j<b->ncols; j++) {
            int k;
            for(int k=0; k<a->ncols; k++) {
                c->mat[i][j] += a->mat[i][k] * b->mat[k][j];
            }
        }
    }

    return c;
}


// Matrix subtraction (as above)
Matrix* sub(Matrix* a, Matrix* b) {
    if(a->nrows != b->nrows || a->ncols != b->ncols) 
        return NULL;
    
    Matrix* c = allocate(a->nrows, a->ncols);
    if(c == NULL)
        return NULL;

    int i, j;
    for(i=0; i<a->nrows; i++) {
        for(j=0; j<a->ncols; j++) {
            c->mat[i][j] = a->mat[i][j] - b->mat[i][j];
        }
    }

    return c;

}

// Matrix scaling (as above)
Matrix* scale(Matrix* m, float factor) {

    Matrix* m_new = allocate(m->nrows, m->ncols);
    if(m_new == NULL)
        return NULL;

    int i, j;
    for(i=0; i<m->nrows; i++) {
        for(j=0; j<m->ncols; j++) {
            m_new->mat[i][j] = m->mat[i][j] * factor;
        }
    }

    return m_new;
}

// Matrix scaling in place (as above)
void scale_in_place(Matrix* m, float factor) {

    int i, j;
    for(i=0; i<m->nrows; i++) {
        for(j=0; j<m->ncols; j++) {
            m->mat[i][j] *= factor;
        }
    }
}

// Row operation exchange
void row_exchange(Matrix* m, int row1, int row2) {

    int i;
    for(i=0; i<m->ncols; i++) {
        float tmp = m->mat[row1][i];
        m->mat[row1][i] = m->mat[row2][i];
        m->mat[row2][i] = tmp;
    }
}

// Row operation scaling
void row_scaling(Matrix* m, int row, float factor) {
    
    int i;
    for(i=0; i<m->ncols; i++)
        m->mat[row][i] *= factor;
}

// Row operation combine
void row_combine(Matrix* m, int row_to, int row_from, float factor) {

    int i;
    for(i=0; i<m->ncols; i++) 
        m->mat[row_to][i] += factor * m->mat[row_from][i];
}

#endif
