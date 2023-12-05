#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int rows = 8;
    const int columns = 8;
    const int odd_rows = rows / 2, even_rows = rows / 2;

    if (rank == 0) {
        int matrix_A[rows][columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j) {
                matrix_A[i][j] = (i + j) % 10;
            }
        printf("Initial matrix A:\n");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                printf("%d ", matrix_A[i][j]);
            }
            printf("\n");
        }

        MPI_Datatype odd;
        MPI_Datatype even;

        MPI_Type_vector(odd_rows, columns, columns * 2, MPI_INT, &odd);
        MPI_Type_commit(&odd);

        MPI_Type_vector(even_rows, columns, columns * 2, MPI_INT, &even);
        MPI_Type_commit(&even);

        MPI_Send(&matrix_A[1], 1, odd, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&matrix_A, 1, even, 1, 1, MPI_COMM_WORLD);

        MPI_Type_free(&odd);
        MPI_Type_free(&even);
    } else if (rank == 1) {
        int matrix_B[odd_rows][columns];
        MPI_Recv(&matrix_B, odd_rows * columns, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int matrix_C[even_rows][columns];
        MPI_Recv(&matrix_C, even_rows * columns, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (rank == 1) {
            printf("Odd rows:\n");
            for (int i = 0; i < odd_rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    printf("%d ", matrix_B[i][j]);
                }
                printf("\n");
            }

            printf("Even rows:\n");
            for (int i = 0; i < even_rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    printf("%d ", matrix_C[i][j]);
                }
                printf("\n");
            }
        }
    }

    MPI_Finalize();
    return 0;
}
