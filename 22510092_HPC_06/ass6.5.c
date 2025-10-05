#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size, n = 8;
    int A[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // Example array
    int local_sum = 0, total_sum = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) printf("Run with 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    int start = rank * (n / 2);
    int end = start + (n / 2);

    for (int i = start; i < end; i++) {
        local_sum += A[i];
    }

    if (rank == 0) {
        int other_sum;
        MPI_Recv(&other_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum = local_sum + other_sum;
        printf("Total sum of array = %d\n", total_sum);
    } else if (rank == 1) {
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}