#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() 
{
    const int n = 100;
    float *vec = (float *)malloc(n * sizeof(float));
    float scalar = 5.0f ;

    for(int i=0;i<n;i++)
    {
        vec[i] = (float)i + 0.5f;
    }

    for(int i=0;i<n;i++)
    {
        vec[i] += scalar;
    }

    for(int i=0;i<10;i++)
    {
        printf("%.2f",vec[i]);
    }

    printf("\n");

    free(vec);

    return 0;
}