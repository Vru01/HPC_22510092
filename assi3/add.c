#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void initialize_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void matrix_addition_parallel(int **matrixA, int **matrixB, int **matrixC, int size, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000}; // Matrix sizes
    int num_threads_list[] = {1, 2, 4, 8}; 

    for (int s = 0; s < 5; s++) {
        int size = sizes[s];
        printf("\nMatrix size: %d x %d\n", size, size);

        int **matrixA = (int **)malloc(size * sizeof(int *));
        int **matrixB = (int **)malloc(size * sizeof(int *));
        int **matrixC = (int **)malloc(size * sizeof(int *));
        
        for (int i = 0; i < size; i++) {
            matrixA[i] = (int *)malloc(size * sizeof(int));
            matrixB[i] = (int *)malloc(size * sizeof(int));
            matrixC[i] = (int *)malloc(size * sizeof(int));
        }

        initialize_matrix(matrixA, size);
        initialize_matrix(matrixB, size);

        for (int t = 0; t < 4; t++) {
            int num_threads = num_threads_list[t];

            double start_time = omp_get_wtime();
            matrix_addition_parallel(matrixA, matrixB, matrixC, size, num_threads);
            double end_time = omp_get_wtime();

            printf("Threads: %d, Time: %.6f seconds\n", num_threads, end_time - start_time);
        }

        for (int i = 0; i < size; i++) {
            free(matrixA[i]);
            free(matrixB[i]);
            free(matrixC[i]);
        }
        free(matrixA);
        free(matrixB);
        free(matrixC);
    }

    return 0;
}