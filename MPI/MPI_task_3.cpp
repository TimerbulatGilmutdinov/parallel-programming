//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <mpi.h>

//int main(int argc, char** argv) {
//    int rank, size;
//    int a[10];
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);

//    if (rank == 0) {
//        srand(time(NULL));
//        for (int i = 0; i < 10; i++) {
//            a[i] = rand() % 100;
//        }
//        MPI_Send(a, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
//    } else if (rank == 1) {
//        MPI_Recv(a, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

//        printf("Accepted array on process 1:\n");
//        for (int i = 0; i < 10; i++) {
//            printf("%d ", a[i]);
//        }
//        printf("\n");
//    }
//    MPI_Finalize();

//    return 0;
//}