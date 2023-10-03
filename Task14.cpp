#include <iostream>

int main() {
    int number = 210;
    long result = 0;

#pragma omp parallel for reduction(+:result)
    for (int i = 1; i <= number*2; i += 2) {
        result += i;
    }

    printf("result = %lld", result);

    return 0;
}
