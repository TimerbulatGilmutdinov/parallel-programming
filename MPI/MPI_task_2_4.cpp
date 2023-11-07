#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int matrixSize = 10;
    const int rowsPerProcess = matrixSize / size;
    const int elementsPerProcess = rowsPerProcess * matrixSize;

    int matrixA[matrixSize][matrixSize];
    int matrixB[matrixSize][matrixSize];
    int localMatrixA[rowsPerProcess][matrixSize];
    int localMatrixB[matrixSize][matrixSize];
    int localMatrixC[rowsPerProcess][matrixSize];

    if (rank == 0) {
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                matrixA[i][j] = i * matrixSize + j;
                matrixB[i][j] = j * matrixSize + i;
            }
        }

        printf("Matrix A:\n");
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                printf("%d ", matrixA[i][j]);
            }
            printf("\n");
        }

        printf("Matrix B:\n");
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                printf("%d ", matrixB[i][j]);
            }
            printf("\n");
        }

        for (int i = 1; i < size; ++i) {
            int startRow = i * rowsPerProcess;
            MPI_Send(&matrixA[startRow][0], elementsPerProcess, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrixB[0][0], matrixSize * matrixSize, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (int i = 0; i < rowsPerProcess; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                localMatrixA[i][j] = matrixA[i][j];
            }
        }
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                localMatrixB[i][j] = matrixB[i][j];
            }
        }
    } else {
        MPI_Recv(&localMatrixA[0][0], elementsPerProcess, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&localMatrixB[0][0], matrixSize * matrixSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < rowsPerProcess; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            localMatrixC[i][j] = 0;
            for (int k = 0; k < matrixSize; ++k) {
                localMatrixC[i][j] += localMatrixA[i][k] * localMatrixB[k][j];
            }
        }
    }

    if (rank == 0) {
        int resultMatrix[matrixSize][matrixSize];

        for (int i = 1; i < size; ++i) {
            int startRow = i * rowsPerProcess;
            MPI_Recv(&resultMatrix[startRow][0], elementsPerProcess, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (int i = 0; i < rowsPerProcess; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                resultMatrix[i][j] = localMatrixC[i][j];
            }
        }

        printf("Result Matrix C:\n");
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                printf("%d ", resultMatrix[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Send(&localMatrixC[0][0], elementsPerProcess, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
