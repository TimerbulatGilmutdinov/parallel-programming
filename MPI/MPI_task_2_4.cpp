#include <iostream>
#include <string>
#include <mpi.h>
#include <algorithm>

int** get_transposed_matrix(int **input_arr, int rows_count, int columns_count) {
    int *arr = new int[rows_count * columns_count];
    int **arrT = new int *[columns_count];
    for (int i = 0; i < columns_count; i++) {
        arrT[i] = &arr[i * rows_count];
    }
    for (int i = 0; i < rows_count; ++i) {
        for (int j = 0; j < columns_count; j++) {
            arrT[j][i] = input_arr[i][j];
        }
    }
    return arrT;
}

int** get_filled_matrix(int rows_count, int columns_count) {
    int *arr = new int[rows_count * columns_count];
    int **arr2 = new int *[rows_count];
    for (int i = 0; i < rows_count; i++) {
        arr2[i] = &arr[i * columns_count];
    }
    for (int i = 0; i < rows_count; ++i) {
        for (int j = 0; j < columns_count; j++) {
            arr2[i][j] = rand() % 10;
        }
    }
    return arr2;
}

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int rows_count_A = 10;
    const int columns_count_A = 12;

    const int rows_count_B = 12;
    const int columns_count_B = 10;

    const int result_matrix_rows_count = rows_count_A;
    const int result_matrix_columns_count = columns_count_B;

    const int sendSize = result_matrix_rows_count / (size - 1);

    if (result_matrix_rows_count % (size - 1) != 0) {
        MPI_Finalize();
        printf("invalid process count");
        exit(1);
    }

    if (rank == 0) {
        int **matrix_A = get_filled_matrix(rows_count_A, columns_count_A);
        int **matrix_B = get_filled_matrix(rows_count_B, columns_count_B);
        int result_matrix[result_matrix_rows_count][result_matrix_columns_count];

        printf("A:\n");
        for (int i = 0; i < rows_count_A; ++i) {
            for (int j = 0; j < columns_count_A; j++) {
                printf("%d ", matrix_A[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("B:\n");
        for (int i = 0; i < rows_count_B; ++i) {
            for (int j = 0; j < columns_count_B; j++) {
                printf("%d ", matrix_B[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int **transposed_matrix_B = get_transposed_matrix(matrix_B, rows_count_B, columns_count_B);

        for (int i = 1, startIndex = 0; i < size; i++,startIndex+=sendSize) {
            MPI_Send(&matrix_A[startIndex][0], sendSize * columns_count_A, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&transposed_matrix_B[0][0], rows_count_B * columns_count_B, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (int i = 1, startIndex = 0; i < size; i++, startIndex+=sendSize) {
            MPI_Recv(&result_matrix[startIndex][0], sendSize * result_matrix_columns_count, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("C:\n");
        for (int i = 0; i < result_matrix_rows_count; ++i) {
            for (int j = 0; j < result_matrix_columns_count; j++) {
                printf("%d ", result_matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    } else {
        int matrix_A[sendSize][columns_count_A];
        int transposed_matrix_B[columns_count_B][rows_count_B];
        int result_matrix_buf[sendSize][columns_count_B];

        MPI_Recv(&matrix_A[0][0], sendSize * columns_count_A, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&transposed_matrix_B[0][0], rows_count_B * columns_count_B, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < sendSize; i++) {
            for (int j = 0; j < columns_count_B; j++) {
                result_matrix_buf[i][j] = 0;
                for (int k = 0; k < columns_count_A; k++) {
                    result_matrix_buf[i][j] += matrix_A[i][k] * transposed_matrix_B[j][k];
                }
            }
        }
        MPI_Send(&result_matrix_buf[0][0], sendSize * columns_count_B, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}