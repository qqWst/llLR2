#include <iostream>
#include <string>
#include "../structs/lfu.h"

using namespace std;

int readNextInt() {
    string token;
    while (cin >> token) {
        string clean = "";
        for (size_t i = 0; i < token.size(); ++i) {
            if ((token[i] >= '0' && token[i] <= '9') || token[i] == '-') {
                clean += token[i];
            }
        }
        if (!clean.empty() && clean != "-") {
            return stoi(clean);
        }
    }
    return -1;
}

int main() {
    system("chcp 65001 > nul");

    cout << "Ввод (cap и Q): ";
    int cap = readNextInt();
    int q = readNextInt();

    if (cap <= 0 || q <= 0) {
        cerr << "ОШИБКА: некорректные значения cap или Q!" << endl;
        return 1;
    }

    LFUCache cache(cap);
    string output = "";

    cout << "Введите запросы:" << endl;
    int processed = 0;
    while (processed < q) {
        string cmd;
        if (!(cin >> cmd)) break;

        if (cmd == "Queries" || cmd == "=") continue;

        if (cmd == "SET") {
            int x = readNextInt();
            int y = readNextInt();
            cache.set(x, y);
            processed++;
        } else if (cmd == "GET") {
            int x = readNextInt();
            int res = cache.get(x);
            if (!output.empty()) output += " ";
            output += to_string(res);
            processed++;
        } else {
            cerr << "ОШИБКА: неизвестная команда '" << cmd << "'" << endl;
            return 1;
        }
    }

    cout << "Вывод: " << output << endl;
    return 0;
}