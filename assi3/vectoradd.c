#include <stdio.h>
#include <omp.h>

#define SIZE 200

int main() {
    int i;
    int vectorA[SIZE], vectorB[SIZE], vectorC[SIZE];

    for (i = 0; i < SIZE; i++) {
        vectorA[i] = i;
        vectorB[i] = i;
    }

    printf("Static scheduling:\n");
    for (int chunk = 1; chunk <= 10; chunk++) {
        double start_time = omp_get_wtime();

        #pragma omp parallel for schedule(static, chunk) num_threads(4)
        for (i = 0; i < SIZE; i++) {
            vectorC[i] = vectorA[i] + vectorB[i];
        }

        double end_time = omp_get_wtime();
        printf("Chunk size: %d, Time: %f seconds\n", chunk, end_time - start_time);
    }

    printf("\nDynamic scheduling:\n");
    for (int chunk = 1; chunk <= 10; chunk++) {
        double start_time = omp_get_wtime();

        #pragma omp parallel for schedule(dynamic, chunk) num_threads(4)
        for (i = 0; i < SIZE; i++) {
            vectorC[i] = vectorA[i] + vectorB[i];
        }

        double end_time = omp_get_wtime();
        printf("Chunk size: %d, Time: %f seconds\n", chunk, end_time - start_time);
    }

    // Demonstrate the use of nowait clause
    printf("\nDemonstrating nowait clause:\n");
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for nowait
        for (i = 0; i < SIZE; i++) {
            vectorC[i] = vectorA[i] + vectorB[i];
        }

        printf("Thread %d finished its work\n", omp_get_thread_num());
    }

    return 0;
}