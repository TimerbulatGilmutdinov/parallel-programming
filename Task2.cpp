//#include <iostream>
//#include <omp.h>
//
//int main() {
//#pragma omp parallel num_threads(3) if(omp_get_num_threads() > 1) default(none)
//    {
//        int numThreads = omp_get_num_threads();
//        int threadId = omp_get_thread_num();
//
//        printf("Region 1 id=%d, total=%d\n", threadId, numThreads);
//    }
//
//#pragma omp parallel num_threads(1) if(omp_get_num_threads() > 1) default(none)
//    {
//        int numThreads = omp_get_num_threads();
//        int threadId = omp_get_thread_num();
//
//        printf("Region 1 id=%d, total=%d\n", threadId, numThreads);
//    }
//
//    return 0;
//}