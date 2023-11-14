#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    const int vectorSize = 100;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int vector[vectorSize];

    if (rank == 0) {
        printf("Initial vector:\n");
        for (int i = 0; i < vectorSize; ++i) {
            vector[i] = i * 10;
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    int local_sum = 0;
    int local_norm = 0;

    int single_process_vector_size = vectorSize / size;

    int local_vector[single_process_vector_size];

    MPI_Scatter(vector, single_process_vector_size, MPI_INT, local_vector, single_process_vector_size, MPI_INT, 0,
                MPI_COMM_WORLD);

    for (int i = 0; i < single_process_vector_size; ++i) {
        local_sum += local_vector[i];
    }

    MPI_Reduce(&local_sum, &local_norm, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result: %d", local_norm);
    }

    MPI_Finalize();
    return 0;
}
