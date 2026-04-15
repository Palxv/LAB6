#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "sequence_utils.h"
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    string inFileName = "";
    string outFileName = "";
    double* numbers = nullptr;
    int count = 0;

    if (argc > 1) {
        if (isNumber(argv[1])) {
            cout << "Аргументи розпізнано як числа. Введіть назву файлу для результату: ";
            cin >> outFileName;
            count = argc - 1;
            numbers = new double[count];
            for (int i = 0; i < count; i++) {
                numbers[i] = atof(argv[i + 1]);
            }
        }
        else if (argc >= 3) {
            outFileName = argv[1];
            count = argc - 2;
            numbers = new double[count];
            for (int i = 0; i < count; i++) {
                numbers[i] = atof(argv[i + 2]);
            }
        }
        else if (argc == 2) {
            outFileName = argv[1];
            cout << "Вихідний файл: " << outFileName << ". Введіть ім'я вхідного файлу з даними: ";
            cin >> inFileName;
        }
    }
    else {
        cout << "Параметри відсутні.\n";
        cout << "Введіть ім'я вхідного файлу: "; cin >> inFileName;
        cout << "Введіть ім'я вихідного файлу: "; cin >> outFileName;
    }

    if (numbers == nullptr && inFileName != "") {
        ifstream inFile(inFileName);
        if (!inFile) {
            cerr << "Помилка: Не вдалося відкрити файл '" << inFileName << "'\n";
            return 1;
        }
        double temp;
        while (inFile >> temp) count++;
        if (count == 0) {
            cerr << "Помилка: Вхідний файл порожній.\n";
            return 1;
        }
        inFile.clear();
        inFile.seekg(0);
        numbers = new double[count];
        for (int i = 0; i < count; i++) inFile >> numbers[i];
        inFile.close();
    }

    if (numbers != nullptr && count > 0 && outFileName != "") {
        double arith = 0, harm = 0;
        sortGoodBad(numbers, count);
        calculateMeans(numbers, count, arith, harm);

        ofstream outFile(outFileName);
        if (outFile) {
            outFile << "Відсортовані числа: ";
            for (int i = 0; i < count; i++) outFile << numbers[i] << " ";
            outFile << "\n\nСереднє арифметичне: " << arith;
            outFile << "\nСереднє гармонічне: " << harm << endl;
            outFile.close();
            cout << "Готово! Результати в '" << outFileName << "'\n";
        }
        else {
            cerr << "Помилка створення файлу виводу.\n";
        }
        delete[] numbers;
    }

    return 0;
}