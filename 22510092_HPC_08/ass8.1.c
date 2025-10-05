#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 8   // Image size (NxN)
#define K 3   // Kernel size (KxK)

int main(int argc, char* argv[]) {
    int rank, size;
    int i, j, m, n;

    double image[N][N], kernel[K][K], result[N][N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = N / size;

    // Master initializes image and kernel
    if (rank == 0) {
        printf("Original Image:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                image[i][j] = i + j;
                printf("%4.1f ", image[i][j]);
            }
            printf("\n");
        }

        printf("Kernel:\n");
        double tempK[K][K] = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
        };
        for (i = 0; i < K; i++) {
            for (j = 0; j < K; j++) {
                kernel[i][j] = tempK[i][j];
                printf("%4.1f ", kernel[i][j]);
            }
            printf("\n");
        }
    }

    // Broadcast kernel to all processes
    MPI_Bcast(kernel, K*K, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter image rows
    double subImage[rows_per_process][N];
    MPI_Scatter(image, rows_per_process*N, MPI_DOUBLE,
                subImage, rows_per_process*N, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    // Each process computes convolution on its rows
    double subResult[rows_per_process][N];
    int pad = K/2;

    for (i = 0; i < rows_per_process; i++) {
        for (j = 0; j < N; j++) {
            double sum = 0.0;
            for (m = 0; m < K; m++) {
                for (n = 0; n < K; n++) {
                    int x = i + rank*rows_per_process + m - pad;
                    int y = j + n - pad;
                    if (x >= 0 && x < N && y >= 0 && y < N) {
                        sum += subImage[i + m - pad][j + n - pad] * kernel[m][n];
                    }
                }
            }
            subResult[i][j] = sum;
        }
    }

    // Gather results back to master
    MPI_Gather(subResult, rows_per_process*N, MPI_DOUBLE,
               result, rows_per_process*N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    // Master prints final result
    if (rank == 0) {
        printf("Convolved Image:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%6.1f ", result[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
