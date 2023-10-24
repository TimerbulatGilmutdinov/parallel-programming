#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    const int ROWS = 6;
    const int COLS = 8;
    int d[ROWS][COLS];
    int min_value = INT_MAX;
    int max_value = INT_MIN;

    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            d[i][j] = rand();
        }
    }

    omp_set_num_threads(4);

#pragma omp parallel for
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
#pragma omp critical
            {
                if (d[i][j] < min_value) {
                    min_value = d[i][j];
                }
                if (d[i][j] > max_value) {
                    max_value = d[i][j];
                }
            }
        }
    }

    printf("min value: %d\n", min_value);
    printf("max value: %d\n", max_value);

    return 0;
}