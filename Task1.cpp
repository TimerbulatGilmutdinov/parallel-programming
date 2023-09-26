//#include <iostream>
//#include <omp.h>
//
//int main() {
//    const int numThreads = 8;
//
//#pragma omp parallel num_threads(numThreads) default(none)
//    {
//        int threadId = omp_get_thread_num();
//        int totalThreads = omp_get_num_threads();
//        printf("id=%d, total=%d, Hello world\n", threadId, totalThreads);
//    }
//
//    return 0;
//}