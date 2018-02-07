#include "stdio.h"
#include "lpp.h"
#include "time.h"

int main() {
    int nvars, neqs;
    printf("Enter nvars, neqs\n");
    scanf("%d %d", &nvars, &neqs);
    printf("No of vars = %d\nNo of eqs = %d\n", nvars, neqs);
    printf("Input matrix A :\n");
    int i,j;
    Matrix* A = allocate(neqs, nvars);
    Matrix* b = allocate(neqs, 1);
    Matrix* c = allocate(1, nvars);

    for(i=0; i<A->nrows; i++)
        for(j=0; j<A->ncols; j++)
            scanf("%f", &(A->mat[i][j]));
    
    printf("Input matrix b :\n");
    for(i=0; i<b->nrows; i++)
        scanf("%f", &(b->mat[i][0]));

    printf("Input matrix c :\n");
    for(i=0; i<c->ncols; i++)
        scanf("%f", &(c->mat[0][i]));

    // Output whatever user entered:
    printf("\n");
    printf("You entered : \n");
    printf("Matrix A = \n");
    printm(A);
    printf("Matrix b = \n");
    printm(b);
    printf("Matrix c = \n");
    printm(c);

    // Calling simplex method:
    Matrix* solution = solve_simplex(A, b, c);

    free(b);
    free(A);
    free(c);
    return 0;
}
