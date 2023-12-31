#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv) {
    const int vectorSize = 100;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int vector_1[vectorSize];
    int vector_2[vectorSize];

    if (rank == 0) {
        printf("Initial vector 1:\n");
        for (int i = 0; i < vectorSize; ++i) {
            vector_1[i] = i*10;
            printf("%d ", vector_1[i]);
        }

        printf("\nInitial vector 2:\n");
        for (int i = 0; i < vectorSize; ++i) {
            vector_2[i] = i*5;
            printf("%d ", vector_2[i]);
        }
        printf("\n");
    }

    int local_sum = 0;
    int local_product = 0;

    int single_process_vector_size = vectorSize / size;

    int local_vector_1_buf[single_process_vector_size];
    int local_vector_2_buf[single_process_vector_size];

    MPI_Scatter(vector_1, single_process_vector_size, MPI_INT, local_vector_1_buf, single_process_vector_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector_2, single_process_vector_size, MPI_INT, local_vector_2_buf, single_process_vector_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < single_process_vector_size; ++i) {
        local_product += local_vector_1_buf[i] * local_vector_2_buf[i];
    }

    MPI_Reduce(&local_product, &local_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result: %d\n", local_sum);
    }

    MPI_Finalize();
    return 0;
}
