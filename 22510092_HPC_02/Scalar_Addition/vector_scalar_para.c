#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() 
{
    const int n = 1000000; 
    float *vec = (float *)malloc(n * sizeof(float));
    float scalar = 5.0f;
    int num_thread_inputs;

    // Get the number of different thread configurations
    printf("Enter the number of different thread configurations: ");
    scanf("%d", &num_thread_inputs);

    int *num_threads = (int *)malloc(num_thread_inputs * sizeof(int));

    // Get the thread counts from the user
    for (int i = 0; i < num_thread_inputs; i++) {
        printf("Enter the number of threads for configuration %d: ", i + 1);
        scanf("%d", &num_threads[i]);
    }

    for (int t = 0; t < num_thread_inputs; t++) 
    {
        // Initialize the vector
        #pragma omp parallel for num_threads(num_threads[t])
        for (int i = 0; i < n; i++)
        {
            vec[i] = (float)i + 0.5f;
        }

        clock_t start, end;
        double cpu_time;

        start = clock();

        // Perform the vector addition
        #pragma omp parallel for num_threads(num_threads[t])
        for (int i = 0; i < n; i++)
        {
            vec[i] += scalar;
        }

        end = clock();
        cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Threads: %d, Time required : %f seconds\n", num_threads[t], cpu_time);

    }

    free(num_threads);
    free(vec);
    return 0;
}
