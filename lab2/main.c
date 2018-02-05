#include "stdio.h"
#include "lpp.h"
#include "time.h"

int main() {
    srand(time(NULL));
    Matrix* a = allocate(3,3);
    int i, j;

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

    solve_gauss_elimination(a, b);

    free(b);
    free(a);
    return 0;
}
