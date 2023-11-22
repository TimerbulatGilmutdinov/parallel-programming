#include <stdio.h>
#include <mpi.h>
#include <cstdlib>

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
        int b[n][n];
        int c[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                a[i][j] = rand()%10;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                b[i][j] = rand()%10;
            }
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
            for (int j = 0; j < n; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
        printf("\n");


        int startIndex = 0;
        for (int i = 1; i < size; i++) {
            MPI_Send(&a[startIndex][0], sendSize * n, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&b[startIndex][0], sendSize * n, MPI_INT, i, 0, MPI_COMM_WORLD);
            startIndex += sendSize;
        }

        startIndex = 0;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&c[startIndex][0], sendSize * n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            startIndex += sendSize;
        }

        printf("C:\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    } else {
        int a[sendSize][n];
        int b[sendSize][n];
        int c[sendSize][n];

        MPI_Recv(&a[0][0], sendSize * n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&b[0][0], sendSize * n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < sendSize; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = a[i][j] * b[i][j];
            }
        }
        MPI_Send(&c[0][0], sendSize * n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
