#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() 
{
    const int n = 100000; 
    float *vec = (float *)malloc(n * sizeof(float));
    float scalar = 5.0f;

    clock_t start, end;
    double cpu_time;

    start = clock();

    for (int i = 0; i < n; i++)
    {
        vec[i] = (float)i + 0.5f;
    }

    for (int i = 0; i < n; i++)
    {
        vec[i] += scalar;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%.2f\n", vec[i]);
    }

    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sequential Time required : %f seconds\n", cpu_time);

    free(vec);

    return 0;
}
