#include <iostream>
#include <cstdlib>
#include <omp.h>

int main() {
    const int arraySize = 30;
    int a[arraySize];

    omp_set_num_threads(4);
    srand(time(nullptr));
    for (int i = 0; i < arraySize; i++) {
        a[i] = rand();
    }

    int count = 0;

#pragma omp parallel for
    for (int i = 0; i < arraySize; i++) {
        if (a[i] % 9 == 0) {
#pragma omp atomic
            count++;
        }
    }

    printf("count dividable by 9: %d", count);

    return 0;
}