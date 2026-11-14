#include <iostream>
#include <string>
#include <stdexcept>
#include "logic.h"
using namespace std;

int main() {
    //system("chcp 65001 > nul");

    string expr;
    cout << "Введите логическое выражение: ";
    getline(cin, expr);

    try {
        string result = evaluateExpression(expr);
        cout << "Результат: " << result << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}