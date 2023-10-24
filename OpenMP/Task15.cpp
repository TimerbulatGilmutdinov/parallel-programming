#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    int start, end;

    std::cout << "start number: ";
    std::cin >> start;

    std::cout << "enter finish number: ";
    std::cin >> end;

    int max_num = end;
    std::vector<bool> is_prime(max_num + 1, true);
    is_prime[0] = is_prime[1] = false;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int chunk_size = (max_num + 1) / num_threads;
        int start_idx = thread_id * chunk_size;
        int end_idx = (thread_id == num_threads - 1) ? max_num : start_idx + chunk_size - 1;

        for (int i = 2; i * i <= max_num; i++) {
            if (is_prime[i]) {
                for (int j = std::max(i * i, (start_idx + i - 1) / i * i); j <= end_idx; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    std::cout << "prime numbers in [" << start << ", " << end << "]:" << std::endl;
    for (int i = start; i <= end; i++) {
        if (is_prime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}