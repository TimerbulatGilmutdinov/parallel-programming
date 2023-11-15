#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 10;
    const int elements_for_process_count = (N * N) / size;

    int matrixA[N][N];
    int matrixB[N][N];
    int localMatrixA[N][N];
    int localMatrixB[N][N];
    int localMatrixC[N][N];

    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                matrixA[i][j] = i * 2 + j;
                matrixB[i][j] = j * 2 + i;
            }
        }

        printf("Matrix A:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d ", matrixA[i][j]);
            }
            printf("\n");
        }

        printf("Matrix B:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d ", matrixB[i][j]);
            }
            printf("\n");
        }

        for (int i = 1; i < size; ++i) {
            int start = i * elements_for_process_count;
            int end = (i + 1) * elements_for_process_count;
            MPI_Send(&matrixA[0][0] + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrixB[0][0] + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                localMatrixA[i][j] = matrixA[i][j];
                localMatrixB[i][j] = matrixB[i][j];
            }
        }
    } else {
        MPI_Recv(&localMatrixA, elements_for_process_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&localMatrixB, elements_for_process_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            localMatrixC[i][j] = localMatrixA[i][j] * localMatrixB[i][j];
        }
    }

    if (rank == 0) {
        int resultMatrix[N][N];

        for (int i = 1; i < size; ++i) {
            int start = i * elements_for_process_count;
            int end = (i == size - 1) ? (N * N) : ((i + 1) * elements_for_process_count);
            MPI_Recv(&resultMatrix[0][0] + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                resultMatrix[i][j] = localMatrixC[i][j];
            }
        }

        printf("Matrix C:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d ", resultMatrix[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Send(&localMatrixC[0][0], elements_for_process_count, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
