#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 12;
    int arr[n];
    const int block_size = n / size + 1;

    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            arr[i] = i + 1;
        }

        for (int i = 1; i < size; ++i) {
            int send_count;
            if (i < n % size) {
                send_count = block_size;
            } else {
                send_count = block_size - 1;
            }
            MPI_Send(arr + i * (block_size - 1), send_count, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        int receive_count;
        if (rank < n % size) {
            receive_count = block_size;
        } else {
            receive_count = block_size - 1;
        }
        MPI_Recv(arr, receive_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Process %d: ", rank);
    int count;
    if (rank < n % size) {
        count = block_size;
    } else {
        count = block_size - 1;
    }
    for (int i = 0; i < count; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
