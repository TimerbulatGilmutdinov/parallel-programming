#include <cstdio>

int main() {
    int a[10];
    int b[10];
    int sum_a = 0;
    int sum_b = 0;

    for (int i = 0; i < 10; i++) {
        a[i] = i * 3 + 1;
    }

    for (int i = 0; i < 10; i++) {
        b[i] = i * 5;
    }

#pragma omp parallel for reduction(+:sum_a, sum_b)
    for (int i = 0; i < 10; i++) {
        sum_a += a[i];
        sum_b += b[i];
    }

    double avg_a = (double) sum_a / 10.0;
    double avg_b = (double) sum_b / 10.0;

    printf("Average for a: %.2lf\n", avg_a);
    printf("Average for b: %.2lf\n", avg_b);

    return 0;
}