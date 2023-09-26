//#include <iostream>
//#include <omp.h>
//
//int main() {
//    int a = 5;
//    int b = 15;
//
//    printf("Before parallel block 1, a=%d, b=%d\n",a,b);
//
//#pragma omp parallel num_threads(2) private(a) firstprivate(b)
//    {
//        int threadId = omp_get_thread_num();
//        a += threadId;
//        b += threadId;
//        printf("Inside parallel block 1, thread id: %d, a=%d, b=%d\n", threadId,a,b);
//    }
//    printf("After parallel block 1, a=%d, b=%d\n", a,b);
//    printf("Before parallel block 2, a=%d, b=%d\n", a,b);
//
//#pragma omp parallel num_threads(4) shared(a) private(b)
//    {
//        int threadId = omp_get_thread_num();
//        a -= threadId;
//        b -= threadId;
//        printf("Inside parallel block 2, thread id: %d, a=%d, b=%d\n", threadId,a,b);
//    }
//
//    printf("After parallel block 2, a=%d, b=%d\n", a,b);
//
//    return 0;
//}