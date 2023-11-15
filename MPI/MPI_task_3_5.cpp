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
        printf("Initial vector: ");
        for (int i = 0; i < vectorSize; ++i) {
            vector[i] = i * 10;
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    int single_process_vector_size = vectorSize / size;

    int local_process_vector_buf[single_process_vector_size];

    MPI_Scatter(vector, single_process_vector_size, MPI_INT, local_process_vector_buf, single_process_vector_size, MPI_INT,
                0, MPI_COMM_WORLD);

    int local_max = 0;
    int local_max_index = 0;

    for (int i = 0; i < single_process_vector_size; ++i) {
        if (local_process_vector_buf[i] > local_max) {
            local_max = local_process_vector_buf[i];
            local_max_index = i;
        }
    }
    printf("Local max for process %d = %d, index = %d\n", rank, local_max, local_max_index);

    int global_max_value;
    int global_max_index;

    MPI_Reduce(&local_max, &global_max_value, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_index, &global_max_index, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; ++i) {
            printf("Rank %d: Max value = %d, Index = %d\n", i, global_max_value,
                   (i * single_process_vector_size + global_max_index));
        }
    }

    MPI_Finalize();
    return 0;
}
