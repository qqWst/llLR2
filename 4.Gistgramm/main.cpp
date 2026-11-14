#include <iostream>
#include <string>
#include "../structs/array.h"
#include "histogram.h"
using namespace std;

int main() {
    system("chcp 65001 > nul");

    string input;
    cout << "Ввод: ";
    getline(cin, input);

    Array<char> chars = initArray(input);
    sortInsert(chars);

    Array<int> counts{nullptr, 0, 0};
    countAndDeleteRepeats(chars, counts);

    cout << "Вывод:" << endl;
    printHistogram(chars, counts);

    killArray(chars);
    killArray(counts);

    return 0;
}