#include "array.h"
using namespace std;

Array<char> initArray(const string& str) {
    Array<char> result{nullptr, 0, 0};
    if (str.empty()) return result;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\r') continue;
        push_backArray(result, str[i]);
    }
    return result;
}