#include <mpi.h>
#include <iostream>


int main(int argc, char** argv)
{
    int rank, size;
    int* received_numbers;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0) {
        received_numbers = new int[size - 1];
        for (int sender_rank = 1; sender_rank < size; sender_rank++) {
            MPI_Recv(&received_numbers[sender_rank - 1], 1, MPI_INT, sender_rank, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        std::cout << "Received nums:" << std::endl;
        for (int sender_rank = 1; sender_rank < size; sender_rank++) {
            std::cout << received_numbers[sender_rank - 1] << " ";
        }
        std::cout << std::endl;
    } else {
        int result = rank*10;
        MPI_Send(&result, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}