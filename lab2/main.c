#include "stdio.h"
#include "lpp.h"
#include "time.h"

int main() {
    srand(time(NULL));
    Matrix* a = allocate(5,3);
    int i, j;

    for(i=0; i<a->nrows-3; i++)
        for(j=0; j<a->ncols; j++)
            a->mat[i][j] = (rand() % 1000)/10.0f;

    printm(a);

    printf("\nRank of a = %d\n", get_rank(a));

    free(a);
    return 0;
}
