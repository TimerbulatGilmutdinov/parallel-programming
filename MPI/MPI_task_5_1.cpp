#include <mpi.h>
#include <stdio.h>
#include <random>


int main(int argc, char** argv) {
    int* ranks = new int[]{8, 3, 9, 1, 6};

    const int group_size = 5;
    const int N = 10;

    int rank, size;
    int array[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 10) {
        printf("Invalid processes count, should be 10\n");
        MPI_Finalize();
        exit(1);
    }

    MPI_Group wgroup, group1, group2;
    MPI_Comm_group(MPI_COMM_WORLD, &wgroup);
    MPI_Group_incl(wgroup, group_size, ranks, &group1);
    MPI_Group_excl(wgroup, group_size, ranks, &group2);

    MPI_Comm comm1, comm2;
    MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
    MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);

    if (comm1 != MPI_COMM_NULL) {
        MPI_Comm_rank(comm1, &rank);
    }
    if (comm2 != MPI_COMM_NULL) {
        MPI_Comm_rank(comm2, &rank);
    }

    if (comm1 != MPI_COMM_NULL) {
        if (rank == 0) {
            for (int i = 0; i < N; i++) {
                array[i] = i;
            }
            printf("Initial array: \n");
            for (int i = 0; i < N; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
            printf("Process %d: \n", rank);
            for (int i = 0; i < N; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }

        MPI_Bcast(&array, N, MPI_FLOAT, 0, comm1);
        printf("Process %d: \n", rank);
        for (int i = 0; i < N; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    if (comm1 != MPI_COMM_NULL && rank == group_size - 1) {
        MPI_Send(&array, N, MPI_FLOAT, 0, 1, comm1);
    }

    if (comm1 != MPI_COMM_NULL && rank == 0) {
        int received[N];

        MPI_Recv(&received, N, MPI_FLOAT, group_size - 1, 1, comm1, MPI_STATUSES_IGNORE);
        printf("Result array for process %d: \n", rank);
        for (int i = 0; i < N; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    if (comm1 != MPI_COMM_NULL) {
        MPI_Comm_free(&comm1);
    }
    if (comm2 != MPI_COMM_NULL) {
        MPI_Comm_free(&comm2);
    }

    MPI_Group_free(&group1);
    MPI_Group_free(&group2);

    MPI_Finalize();
    return 0;
}
