#include <stdio.h>
#include <omp.h>

#define N 10   // keep small for demonstration

int main() {
    static int arr[N], prefix[N];
    int i;

    // Initialize array with 1,2,3,4,5,...
    for (i = 0; i < N; i++)
        arr[i] = i + 1;  

    double start = omp_get_wtime();

    prefix[0] = arr[0];
    #pragma omp parallel
    {
        #pragma omp for
        for (i = 1; i < N; i++) {
            //  This has a dependency so OpenMP parallelization here may cause race conditions.
            prefix[i] = prefix[i - 1] + arr[i]; 
        }
    }

    double end = omp_get_wtime();

    printf("Prefix sum result:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\n");

    printf("Prefix sum done in %f seconds\n", end - start);
    return 0;
}
