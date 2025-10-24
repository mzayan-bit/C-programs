#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int *a, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = a[l + i];
    }
    for (int i = 0; i < n2; i++){
        R[i] = a[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergesort(int *a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    int n = 16, seg = 4, size = n / seg;
    int a[16];
    for (int i = 0; i < n; i++) a[i] = rand() % 100;

    double t1 = omp_get_wtime();

    // Sort segments in parallel
    #pragma omp parallel num_threads(seg)
    {
        int id = omp_get_thread_num();
        mergesort(a, id * size, (id + 1) * size - 1);
    }

    double t2 = omp_get_wtime();

    printf("Without ordered printing:\n");
    #pragma omp parallel num_threads(seg)
    {
        int id = omp_get_thread_num();
        printf("Segment %d: ", id + 1);
        for (int i = id * size; i < (id + 1) * size; i++) printf("%d ", a[i]);
        printf("\n");
    }

    printf("\nWith ordered printing:\n");
    #pragma omp parallel for ordered num_threads(seg)
    for (int id = 0; id < seg; id++) {
        #pragma omp ordered
        {
            printf("Segment %d: ", id + 1);
            for (int i = id * size; i < (id + 1) * size; i++) printf("%d ", a[i]);
            printf("\n");
        }
    }

    printf("\nTime: %f sec\n", t2 - t1);

    return 0;
}

