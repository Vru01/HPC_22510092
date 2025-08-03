#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_POINTS 100000000

int main() {
    long long int num_points = NUM_POINTS;
    long long int points_in_circle = 0;
    double x, y;
    double pi;
    clock_t start, end;
    double sequential_time;

    // Initialize the random number generator
    srand(time(NULL));

    // Timing the sequential computation
    start = clock();

    for (long long int i = 0; i < num_points; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            points_in_circle++;
        }
    }

    end = clock();
    sequential_time = (double)(end - start) / CLOCKS_PER_SEC;

    pi = 4.0 * points_in_circle / num_points;

    printf("Sequential computation:\n");
    printf("Calculated value of pi: %f\n", pi);
    printf("Sequential execution time: %f seconds\n", sequential_time);

    return 0;
}
