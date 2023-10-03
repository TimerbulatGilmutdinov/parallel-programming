#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

int main() {
    const int arraySize = 100;
    const int numThreads = 4;

    omp_set_num_threads(numThreads);

    srand(time(nullptr));
    int array[arraySize];
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand();
    }

    int maxValue = -INT_MAX;

#pragma omp parallel for
    for (int i = 0; i < arraySize; i++) {
        if (array[i] % 7 == 0) {
#pragma omp critical
            {
                if (array[i] > maxValue) {
                    maxValue = array[i];
                }
            }
        }
    }

    if (maxValue != -INT_MAX) {
        printf("max value dividable by 7: %d", maxValue);
    } else {
        printf("no numbers dividable by 7");
    }

    return 0;
}