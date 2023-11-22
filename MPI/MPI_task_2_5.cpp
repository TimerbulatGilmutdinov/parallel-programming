#include <stdio.h>
#include <mpi.h>
#include <cstdlib>

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int rows_count = 10;
    const int columns_count = 10;

    if (rank == 0) {
        int initial_matrix[rows_count][columns_count];
        int transposed_matrix[columns_count][rows_count];

        for (int i = 0; i < rows_count; ++i) {
            for (int j = 0; j < columns_count; j++) {
                initial_matrix[i][j] = rand() % 10;
            }
        }

        printf("initial matrix:\n");
        for (int i = 0; i < rows_count; ++i) {
            for (int j = 0; j < columns_count; j++) {
                printf("%d ", initial_matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        for (int sending_row_index = 0; sending_row_index < rows_count; sending_row_index++) {
            MPI_Send(&initial_matrix[sending_row_index][0], columns_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }

        for (int receiving_row_index = 0; receiving_row_index < columns_count; receiving_row_index++) {
            MPI_Recv(&transposed_matrix[receiving_row_index][0], rows_count, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("transposed matrix:\n");
        for (int i = 0; i < columns_count; ++i) {
            for (int j = 0; j < rows_count; j++) {
                printf("%d ", transposed_matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    } else if (rank == 1) {
        int matrix[rows_count][columns_count];

        for (int received = 0; received < rows_count; received++) {
            MPI_Recv(&matrix[received][0], columns_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        int transposed_matrix[rows_count][columns_count];
        for (int i = 0; i < rows_count; ++i) {
            for (int j = 0; j < columns_count; j++) {
                transposed_matrix[j][i] = matrix[i][j];
            }
        }

        for (int sent = 0; sent < columns_count; sent++) {
            MPI_Send(&transposed_matrix[sent][0], rows_count, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
