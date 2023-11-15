#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    const int matrixSize = 100;
    const int vectorSize = 100;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[matrixSize][matrixSize];
    int vector[vectorSize];
    int local_result[matrixSize];

    if (rank == 0) {
//        printf("Matrix:\n");
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                matrix[i][j] = i*10+j*5;
//                printf("%.1f ", matrix[i][j]);
            }
//            printf("\n");
        }
        printf("Vector:\n");
        for (int i = 0; i < vectorSize; ++i) {
            vector[i] = i*5;
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    MPI_Bcast(vector, vectorSize, MPI_INT, 0, MPI_COMM_WORLD);

    int single_process_sub_matrix_size = matrixSize / size;

    int local_matrix_buf[single_process_sub_matrix_size][matrixSize];

    MPI_Scatter(matrix, single_process_sub_matrix_size * matrixSize, MPI_INT, local_matrix_buf, single_process_sub_matrix_size * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < single_process_sub_matrix_size; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            local_result[i] += local_matrix_buf[i][j] * vector[j];
        }
    }

    int global_result[matrixSize];
    MPI_Gather(local_result, single_process_sub_matrix_size, MPI_INT, global_result, single_process_sub_matrix_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resulting vector:\n");
        for (int i = 0; i < matrixSize; ++i) {
            printf("%d ", global_result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
