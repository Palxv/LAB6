#include "sequence_utils.h"
#include <cmath>
#include <cstdlib>
// Функція для перевірки, чи є рядок числом
bool isNumber(const char* s) {
    if (s == nullptr || s[0] == '\0') return false;
    char* endptr;
    strtod(s, &endptr);
    return *endptr == '\0';
}
//сортування масиву. В початку всі нуль та від'ємні числа, потім всі додатні
void sortGoodBad(double* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] <= 0.0 && arr[j + 1] > 0.0) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// Функція для обчислення середнього арифметичного та гармонійного
void calculateMeans(double* arr, int size, double& outA, double& outH) {
    if (size <= 0) { outA = 0; outH = 0; return; }

    double sum = 0;
    double reciprocalSum = 0;
    bool hasZero = false;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (arr[i] == 0) hasZero = true;
        else reciprocalSum += 1.0 / arr[i];
    }

    outA = sum / size;
    if (hasZero || reciprocalSum == 0) outH = NAN;
    else outH = (double)size / reciprocalSum;
}