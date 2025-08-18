#include <stdio.h>
#include <omp.h>

int fib(int n) {
    if (n < 2) return n;
    int x, y;
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait   // wait for both tasks to finish
    return x + y;
}

int main() {
    int n = 10, result;
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single   // only one thread starts fib()
        result = fib(n);
    }

    double end = omp_get_wtime();
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Time = %f seconds\n", end - start);
    return 0;
}
