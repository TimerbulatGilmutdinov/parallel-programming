#include <cstdio>
#include <omp.h>

int main() {
    int a[12];
    int b[12];
    int c[12];

    int num_threads_1 = 3;
    int num_threads_2 = 4;

#pragma omp parallel num_threads(num_threads_1)
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
#pragma omp critical
        {
            printf("parallel region 1: thread %d of %d\n", thread_num, total_threads);
        }

#pragma omp for schedule(static, 3)
        for (int i = 0; i < 12; i++) {
            a[i] = thread_num * 100 + i;
            b[i] = thread_num * 200 + i;
        }
#pragma omp critical
        {
            printf("initial array a:\n");
            for (int i = 0; i < 12; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");


            printf("initial array b:\n");
            for (int i = 0; i < 12; i++) {
                printf("%d ", b[i]);
            }
            printf("\n");
        }
    }

#pragma omp parallel num_threads(num_threads_2)
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
#pragma omp critical
        {
            printf("parallel region 2: thread %d of %d\n", thread_num, total_threads);
        }
#pragma omp for schedule(dynamic, 2)
        for (int i = 0; i < 12; i++) {
            c[i] = a[i] + b[i];
        }
#pragma omp critical
        {
            printf("array c:\n");
            for (int i = 0; i < 12; i++) {
                printf("%d ", c[i]);
            }
        }
    }

    return 0;
}