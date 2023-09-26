#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() {
    const int rows = 6;
    const int cols = 8;
    int d[rows][cols];

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            d[i][j] = std::rand() % 100;
        }
    }

    double avg = 0;
    int minArr = d[0][0];
    int maxArr = d[0][0];
    int countBy3 = 0;

#pragma omp parallel sections num_threads(3)
    {
#pragma omp section
        {
            int threadId = omp_get_thread_num();
            int localSum = 0;

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    localSum += d[i][j];
                }
            }

#pragma omp critical
            {
                avg = static_cast<double>(localSum) / (rows * cols);
                std::cout << "Section 1, thread id: " << threadId << ": average = " << avg << std::endl;
            }
        }

#pragma omp section
        {
            int threadId = omp_get_thread_num();

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (d[i][j] < minArr) {
                        minArr = d[i][j];
                    }
                    if (d[i][j] > maxArr) {
                        maxArr = d[i][j];
                    }
                }
            }
#pragma omp critical

            printf("Section 2, thread id: %d, min=%d, max=%d\n", threadId, minArr, maxArr);
        }

#pragma omp section
        {
            int threadId = omp_get_thread_num();

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (d[i][j] % 3 == 0) {
#pragma omp atomic
                        countBy3++;
                    }
                }
            }
#pragma omp critical

            printf("Section 3, thread id: %d, count=%d\n", threadId, countBy3);
        }
    }

    return 0;
}


