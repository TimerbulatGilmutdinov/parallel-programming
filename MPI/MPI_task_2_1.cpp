#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int vectorSize = 10;
    const int length = vectorSize / size;
    const int a = 5;
    const int b = 7;

    int vector_x[vectorSize];
    int vector_y[vectorSize];
    int vector_z[vectorSize];

    int temp_x[length];
    int temp_y[length];

    if (rank == 0) {
        for (int i = 0; i < vectorSize; i++) {
            vector_x[i] = i*2+1;
            vector_y[i] = i*3+1;
        }

        for (int i = 1; i < size; i++) {
            MPI_Send(vector_x + i * length, length, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(vector_y + i * length, length, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (int i = 0; i < length; i++) {
            temp_x[i] = vector_x[i];
            temp_y[i] = vector_y[i];
        }
    }
    else {
        MPI_Recv(temp_x, length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(temp_y, length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    int temp_z[length];
    for (int i = 0; i < length; i++) {
        temp_z[i] = a * temp_x[i] + b * temp_y[i];
    }

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(vector_z + i * length, length, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (int i = 0; i < length; i++) {
            vector_z[i] = a * temp_x[i] + b * temp_y[i];
        }

        printf("Result on process 0:\n");
        for (int i = 0; i < vectorSize; i++) {
            printf("%d = %d*%d+%d*%d\n", vector_z[i],a,vector_x[i],b,vector_y[i]);
        }
        printf("\n");
    }
    else {
        MPI_Send(temp_z, length, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
