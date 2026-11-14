#include <iostream>
#include <string>
#include "../structs/hash_table.h"

using namespace std;

int main() {
    system("chcp 65001 > nul");

    int num;
    cout << "Ввод: ";
    if (!(cin >> num) || num < 1 || num > 3999) {
        cerr << "ОШИБКА: введите целое число от 1 до 3999!" << endl;
        return 1;
    }

    ChainHashTable romanMap;
    initChainTable(romanMap, 32);

    insertChain(romanMap, "1000", "M");
    insertChain(romanMap, "900",  "CM");
    insertChain(romanMap, "500",  "D");
    insertChain(romanMap, "400",  "CD");
    insertChain(romanMap, "100",  "C");
    insertChain(romanMap, "90",   "XC");
    insertChain(romanMap, "50",   "L");
    insertChain(romanMap, "40",   "XL");
    insertChain(romanMap, "10",   "X");
    insertChain(romanMap, "9",    "IX");
    insertChain(romanMap, "5",    "V");
    insertChain(romanMap, "4",    "IV");
    insertChain(romanMap, "1",    "I");

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const size_t count = sizeof(values) / sizeof(values[0]);

    string result = "";

    for (size_t i = 0; i < count; ++i) {
        while (num >= values[i]) {
            result += searchChain(romanMap, to_string(values[i]));
            num -= values[i];
        }
    }

    cout << "Вывод: \"" << result << "\"" << endl;

    freeChainTable(romanMap);
    return 0;
}