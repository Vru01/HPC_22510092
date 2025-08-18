#include <stdio.h>
#include <omp.h>

#define SIZE 5
int buffer[SIZE], count = 0;
omp_lock_t lock;

void producer(int id) {
    for (int i = 0; i < 5; i++) {
        omp_set_lock(&lock);
        if (count < SIZE) {
            buffer[count++] = i;
            printf("Producer %d produced %d\n", id, i);
        }
        omp_unset_lock(&lock);
    }
}

void consumer(int id) {
    for (int i = 0; i < 5; i++) {
        omp_set_lock(&lock);
        if (count > 0) {
            int item = buffer[--count];
            printf("Consumer %d consumed %d\n", id, item);
        }
        omp_unset_lock(&lock);
    }
}

int main() {
    omp_init_lock(&lock);

    #pragma omp parallel sections
    {
        #pragma omp section
        producer(1);
        #pragma omp section
        consumer(1);
    }

    omp_destroy_lock(&lock);
    return 0;
}
