#include <iostream>
#include <string>
#include "../structs/set.h"

using namespace std;

int solveTurtles(int n) {
    Set truthfulTurtles{nullptr, 0, 0};
    createSet(truthfulTurtles, 16);

    for (int i = 0; i < n; ++i) {
        int a, b;
        if (!(cin >> a >> b)) {
            deleteSet(truthfulTurtles);
            throw runtime_error("ОШИБКА: некорректный ввод координат черепахи!");
        }

        string statement = to_string(a) + " " + to_string(b);

        if (!setAt(truthfulTurtles, statement)
           && !(a < 0 || b < 0 || a + b + 1 != n)) {
            setAdd(truthfulTurtles, statement);
        }
    }

    int answer = static_cast<int>(truthfulTurtles.size);
    deleteSet(truthfulTurtles);
    return answer;
}

int main() {
    system("chcp 65001 > nul");

    int n;
    cout << "Ввод: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "ОШИБКА: количество черепах должно быть положительным числом!" << endl;
        return 1;
    }

    try {
        int maxTruthful = solveTurtles(n);
        cout << "Вывод: " << maxTruthful << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}