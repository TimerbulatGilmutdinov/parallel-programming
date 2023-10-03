#include <iostream>
#include <vector>
#include <omp.h>


std::vector<double> MatrixVectorMultiplySeq(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    std::vector<double> result(numRows, 0.0);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<double> MatrixVectorMultiplyParallel(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    std::vector<double> result(numRows, 0.0);

    omp_set_num_threads(16);

#pragma omp parallel for
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
#pragma omp atomic
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main() {
    int numRows = 1000;
    int numCols = 1000;
    std::vector<std::vector<double>> matrix(numRows, std::vector<double>(numCols, 1.0));
    std::vector<double> vector(numCols, 2.0);

    double startTimeSeq = omp_get_wtime();
    std::vector<double> resultSeq = MatrixVectorMultiplySeq(matrix, vector);
    double endTimeSeq = omp_get_wtime();

    double startTimeParallel = omp_get_wtime();
    std::vector<double> resultParallel = MatrixVectorMultiplyParallel(matrix, vector);
    double endTimeParallel = omp_get_wtime();

    printf("sequential time: %f sec\n", endTimeSeq-startTimeSeq);
    printf("parallel execution time: %f sec", endTimeParallel - startTimeParallel);

    return 0;
}