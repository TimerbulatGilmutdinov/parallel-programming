#include <stdio.h>
#include <mpi.h>
#include <cstdlib>

int main(int argc, char **argv) {
    const int N = 10;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[N][N];
    int transposedMatrix[N][N];

    if (rank == 0) {
        printf("Init matrix: \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i * (rand() % 5) + j * 2;
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        for (int i = 1; i < size; i++) {
            MPI_Send(matrix, N * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(matrix, N * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }

    if (rank == 0) {
        int result[N][N];

        for (int i = 1; i < size; i++) {
            MPI_Recv(&result[0][0], N * N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (result[j][k] == 0) {
                        result[j][k] = transposedMatrix[j][k];
                    }
                }
            }
        }
        printf("Transposed matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", transposedMatrix[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Send(&transposedMatrix[0][0], N * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}