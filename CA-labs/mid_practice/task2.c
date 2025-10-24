#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main()
{
    int a[6][6], b[6][6], c[6][6] = {0}, d[6][6] = {0};

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            a[i][j] = rand() % 36;
            b[i][j] = rand() % 36;
        }
    int i,j;
    #pragma omp parallel for private(i, j) shared(a, b, c)
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    int l,m;
    #pragma omp parallel for private(l, m) shared(a, b, d)
    for (l = 0; l < 6; l++) {
        for (m = 0; m < 6; m++) {
            d[l][m] = a[l][m] * b[l][m];
        }
    }

    printf("Unordered output:\n");
    #pragma omp parallel for shared(d)
    for (int y = 0; y < 6; y++) {
        for (int z = 0; z < 6; z++) {
            printf("d[%d][%d] = %d\n", y, z, d[y][z]);
        }
    }

    printf("\nOrdered output:\n");
    #pragma omp parallel for ordered shared(d)
    for (int y = 0; y < 6; y++) {
        for (int z = 0; z < 6; z++) {
            #pragma omp ordered
            printf("d[%d][%d] = %d\n", y, z, d[y][z]);
        }
    }
    return 0;
}
