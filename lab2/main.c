#include "stdio.h"
#include "lpp.h"
#include "time.h"

int main() {
    srand(time(NULL));
    Matrix* a = allocate(2,2);
    int i, j;

    // UI for inputting equation matrices to solve / check for solutions

    printf("\nMatrix A :\n");
    a->mat[0][0] = 2; a->mat[0][1] = 1;
    a->mat[1][0] = 1; a->mat[1][1] = 2;
    printm(a);

    Matrix* b = allocate(2, 1);
    b->mat[0][0] = 3;
    b->mat[1][0] = 1;
    printf("Matrix b\n");
    printm(b);

    //Matrix* x = solve_gauss_elimination(a, b);
    Matrix* xx = solve_jacobi(a, b);

    printf("Matrix solutions \n");
    printf("\n");
    printm(xx);

    free(b);
    free(a);
    return 0;
}
