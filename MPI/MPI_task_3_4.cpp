#include <mpi.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv) {
    const int matrixSize = 100;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[matrixSize][matrixSize];

    if (rank == 0) {
        printf("Matrix:\n");
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                matrix[i][j] = i*2+j*3;
//                printf("%d ", matrix[i][j]);
            }
//            printf("\n");
        }
    }

    int local_rows = matrixSize / size;

    int local_matrix[local_rows][matrixSize];

    MPI_Scatter(matrix, local_rows * matrixSize, MPI_INT, local_matrix, local_rows * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);
    int local_max = 0;
    for (int i = 0; i < local_rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < matrixSize; j++) {
            row_sum += std::abs(local_matrix[i][j]);
        }
        if (row_sum > local_max) {
            local_max = row_sum;
        }
    }

    int global_max = 0;
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Matrix norm: %d\n", global_max);
    }

    MPI_Finalize();
    return 0;
}
