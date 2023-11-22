#include <iostream>
#include <string>
#include "mpi.h"
#include <algorithm>


int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int a = 2;
    const int b = 3;
    const int n = 10;
    const int sendSize = n / (size - 1);

    if (n % (size - 1) != 0) {
        MPI_Finalize();
        printf("invalid process count");
        exit(1);
    }

    if (rank == 0) {
        int x[n];
        int y[n];
        int z[n];

        for (int i = 0; i < n; ++i) {
            x[i] = rand() % 10;
        }

        for (int i = 0; i < n; ++i) {
            y[i] = rand() % 10;
        }

        printf("x: ");
        for (int i = 0; i < n; ++i) {
            printf("%d ", x[i]);
        }
        printf("\n");
        printf("y: ");
        for (int i = 0; i < n; ++i) {
            printf("%d ", y[i]);
        }
        printf("\n");

        int startIndex = 0;
        for (int i = 1; i < size; i++) {
            MPI_Send(&x[startIndex], sendSize, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&y[startIndex], sendSize, MPI_INT, i, 0, MPI_COMM_WORLD);
            startIndex += sendSize;
        }

        startIndex = 0;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&z[startIndex], sendSize, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            startIndex += sendSize;
        }

        printf("z: ");
        for (int i = 0; i < n; ++i) {
            printf("%d ", z[i]);
        }
        printf("\n");
    } else {
        int count;
        MPI_Status status;

        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);

        int x[count];
        int y[count];
        int z[count];

        MPI_Recv(&x[0], count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&y[0], count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < count; i++) {
            z[i] = a * x[i] + b * y[i];
        }

        MPI_Send(&z[0], count, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
