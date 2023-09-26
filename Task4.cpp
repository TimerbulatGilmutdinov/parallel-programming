//#include <iostream>
//#include <omp.h>
//
//int main() {
//    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    int b[10] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11};
//
//    int minA = a[0];
//    int maxB = b[0];
//
//    const int num_threads = 2;
//#pragma omp parallel num_threads(num_threads)
//    {
//        int threadId = omp_get_thread_num();
//
//        if (threadId == 0) {
//            for (int i = 1; i < 10; ++i) {
//                if (a[i] < minA) {
//#pragma omp critical
//                    {
//                        if (a[i] < minA) {
//                            minA = a[i];
//                        }
//                    }
//                }
//            }
//        }
//        if (threadId == 1) {
//            for (int i = 1; i < 10; ++i) {
//                if (b[i] > maxB) {
//#pragma omp critical
//                    {
//                        if (b[i] > maxB) {
//                            maxB = b[i];
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    printf("min from a: %d\n", minA);
//    printf("max from b: %d\n", maxB);
//
//    return 0;
//}