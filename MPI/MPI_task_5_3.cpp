#include <mpi.h>
#include <stdio.h>
#include <cstdlib>

const int rows = 8;
const int columns = 8;

struct MyStruct {
    int matrix_part[2][columns];
};

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        printf("Invalid processes count, should be 4");
        MPI_Finalize();
        exit(1);
    }

    MPI_Datatype new_type;

    MPI_Aint disp[2];
    int blocklengths[2];
    MPI_Datatype types[2];

    for (int i = 0; i < 2; ++i) {
        disp[i] = i * columns * 4; // int = 4 bytes
        blocklengths[i] = columns;
        types[i] = MPI_INT;
    }

    MPI_Type_create_struct(2, blocklengths, disp, types, &new_type);
    MPI_Type_commit(&new_type);

    MyStruct *temp = new MyStruct[size];

    if (rank == 0) {
        int matrix[rows][columns];
        printf("Initial array:\n");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = (i + j) % 10;
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        for (int n = 0, i = 0, k = 4; i < 4; i++, k++, n++) {
            for (int j = 0; j < columns; ++j) {
                temp[n].matrix_part[0][j] = matrix[i][j];
                temp[n].matrix_part[1][j] = matrix[k][j];
            }
        }
    }
    MyStruct process_part;

    MPI_Scatter(temp, 2 * columns, MPI_INT, &process_part, 2 * columns, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rows for process %d:\n", rank);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d ", process_part.matrix_part[i][j]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
