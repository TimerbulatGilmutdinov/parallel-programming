#include <iostream>
#include <cmath>

int main() {
    int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    int decimalNumber = 0;
    int length = sizeof(a) / sizeof(a[0]);

#pragma omp parallel for reduction(+:decimalNumber)
    for (int i = 0; i < length; i++) {
        int power = length - i - 1;
        int binaryDigit = a[i];
        int decimalDigit = binaryDigit * (int) (std::pow(2, power));
        decimalNumber += decimalDigit;
    }

    printf("number = %d", decimalNumber);

    return 0;
}