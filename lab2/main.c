#include "stdio.h"
#include "lpp.h"
#include "time.h"

int main() {
    srand(time(NULL));
    Matrix* a = allocate(3,3);
    int i, j;

    // UI for inputting equation matrices to solve / check for solutions

    for(i=0; i<a->nrows; i++)
        for(j=0; j<a->ncols; j++)
            a->mat[i][j] = (rand() % 1000)/10.0f;
    
    printf("\nMatrix A :\n");
    printm(a);

    Matrix* b = allocate(3, 1);
    for(i=0; i<b->nrows; i++)
        b->mat[i][0] = (rand() % 1000 / 10.0f);
    printf("Matrix b\n");
    printm(b);

    //Matrix* x = solve_gauss_elimination(a, b);
    Matrix* xx = solve_jacobi(a, b);

    //printf("Matrix x\n");
   // printm(x);
    printf("\n");
    printm(xx);

    free(b);
    free(a);
    return 0;
}
