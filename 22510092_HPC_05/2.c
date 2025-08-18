#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    static double A[N][N];
    double scalar = 5.0;
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = i + j;

    double start = omp_get_wtime();

    // Parallel matrix-scalar multiplication
    #pragma omp parallel for private(j) shared(A)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] *= scalar;
        }
    }

    double end = omp_get_wtime();
    printf("Matrix-Scalar Multiplication done in %f seconds\n", end - start);

    // small part of the result matrix
    printf("\nSample of Resulting Matrix (first 5x5 block):\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}
