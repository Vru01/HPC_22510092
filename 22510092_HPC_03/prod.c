#include <stdio.h>
#include <omp.h>

#define N 100

int main() {
    int i, min_product;
    int vector1[N], vector2[N];
    
    for (i = 0; i < N; i++) {
        vector1[i] = i + 1;
        vector2[i] = N - i;
    }
    
    min_product = vector1[0] * vector2[0];
    
    #pragma omp parallel for reduction(min: min_product)
    for (i = 1; i < N; i++) {
        int product = vector1[i] * vector2[i];
        if (product < min_product) {
            min_product = product;
        }
    }
    
    printf("Minimum scalar product: %d\n", min_product);
    
    return 0;
}