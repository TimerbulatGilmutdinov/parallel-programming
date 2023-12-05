#include <stdio.h>
#include <mpi.h>
#include <cstdlib>

const int max_n = 40000;

void bidirectional_ping_pong(int rank, int message_size) {

    int *mess = new int[message_size];

    for (int i = 0; i < message_size; ++i) {
        mess[i] = i + 1;
    }

    if (rank == 0) {
        double start = MPI_Wtime();

        MPI_Send(mess, message_size, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(mess, message_size, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double end = MPI_Wtime();

        double result = end - start;
        printf("Time took for bidirectional ping pong for size %d: %f seconds\n", message_size, result);
    } else {
        int *received = new int[message_size];

        MPI_Recv(received, message_size, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(received, message_size, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    delete[] mess;
}

void one_directional_ping_ping(int rank, int message_size) {
    int *mess = new int[message_size];

    for (int i = 0; i < message_size; ++i) {
        mess[i] = i + 1;
    }

    double start = MPI_Wtime();

    if (rank == 0) {
        MPI_Send(mess, message_size, MPI_INT, 1, 1, MPI_COMM_WORLD);
    } else {
        MPI_Send(mess, message_size, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        int *received = new int[message_size];

        MPI_Recv(received, message_size, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        int *mess2 = new int[message_size];

        MPI_Recv(mess2, message_size, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    double end = MPI_Wtime();

    double result = end - start;
    printf("Time took for one directional ping pong for size %d: %f seconds\n", message_size, result);

    delete[] mess;
}

int main(int argc, char **argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 2) {
        printf("Invalid size, should be 2!");
        MPI_Finalize();
        exit(1);
    }
    int message_size = 5000;

    for (int i = 0; i < 4; message_size += 5000, i++) {
        one_directional_ping_ping(rank, message_size);
    }
    message_size = 5000;
    for (int i = 0; i < 4; message_size += 5000, i++) {
        bidirectional_ping_pong(rank, message_size);
    }

    MPI_Finalize();
    return 0;
}
