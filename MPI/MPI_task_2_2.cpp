#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int n = 10;
    const int sendSize = n / (size - 1);

    if (n % (size - 1) != 0) {
        MPI_Finalize();
        printf("invalid process count");
        exit(1);
    }

    if (rank == 0) {

        int a[n][n];
        int b[n];
        int c[n];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                a[i][j] = rand() % 10;
            }
        }
        for (int i = 0; i < n; ++i) {
            b[i] = rand() % 10;
        }

        printf("A:\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("B:\n");
        for (int i = 0; i < n; ++i) {
            printf("%d ", b[i]);
        }
        printf("\n");


        int startIndex = 0;
        for (int i = 1; i < size; i++) {
            MPI_Send(&a[startIndex][0], sendSize * n, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&b[0], n, MPI_INT, i, 0, MPI_COMM_WORLD);
            startIndex += sendSize;
        }

        startIndex = 0;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&c[startIndex], sendSize, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            startIndex += sendSize;
        }

        printf("C:\n");
        for (int i = 0; i < n; ++i) {
            printf("%d ", c[i]);
        }
    } else {
        int a[sendSize][n];
        int b[n];
        int c[sendSize];

        MPI_Recv(&a[0][0], sendSize * n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&b[0], n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < sendSize; i++) {
            c[i] = 0;
            for (int j = 0; j < n; j++) {
                c[i] += a[i][j] * b[j];
            }
        }
        MPI_Send(&c[0], sendSize, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }

    MPI_Finalize();
    return 0;
}