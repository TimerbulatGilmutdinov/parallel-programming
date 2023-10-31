#include <stdio.h>
#include <mpi.h>
#include <cstdlib>

int main(int argc, char **argv) {
    const int N = 10;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix1[N][N];
    int matrix2[N][N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix1[i][j] = i * (rand() % 7) + j * 2;
                matrix2[i][j] = j * (rand() % 5) + i * 3;
            }
        }
        printf("Matrix 1:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", matrix1[i][j]);
            }
            printf("\n");
        }

        printf("Matrix 2:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", matrix2[i][j]);
            }
            printf("\n");
        }

        for (int i = 1; i < size; ++i) {
            MPI_Send(&matrix1[0][0], N * N, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix2[0][0], N * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&matrix1[0][0], N * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&matrix2[0][0], N * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int buf[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            buf[i][j] = 0;
            for (int k = 0; k < N; k++) {
                buf[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    if (rank == 0) {
        int result[N][N];

        for (int i = 1; i < size; i++) {
            MPI_Recv(&result[0][0], N * N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (result[j][k] == 0) {
                        result[j][k] = buf[j][k];
                    }
                }
            }
        }

        printf("Resulting matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Send(&buf[0][0], N * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}