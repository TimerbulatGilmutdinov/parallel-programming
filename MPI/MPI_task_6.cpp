#include <mpi.h>
#include <random>

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int vectorSize = 100;
    constexpr int a = 5;
    constexpr int b = 7;

    int vector_x[vectorSize];
    int vector_y[vectorSize];
    int vector_z[vectorSize];

    if (rank == 0) {
        for (int i = 0; i < vectorSize; i++) {
            vector_x[i] = rand() % 13;
            vector_y[i] = rand() % 17;
        }

        for (int i = 1; i < size; i++) {
            MPI_Send(vector_x, vectorSize, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(vector_y, vectorSize, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(vector_x, vectorSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector_y, vectorSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < vectorSize; i++) {
        vector_z[i] = a * vector_x[i] + b * vector_y[i];
//        printf("z[%d] = %d*%d + %d*%d = %d\n", i,a,vector_x[i],b,vector_y[i],vector_z[i]);
    }

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&vector_z[i * vectorSize / size], vectorSize / size, MPI_INT, i, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        }

        printf("Result vector z: \n");
        for (int i: vector_z) {
            printf("%d ", i);
        }
        printf("\n");
    } else {
        MPI_Send(vector_z, vectorSize / size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}