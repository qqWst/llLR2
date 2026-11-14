#include "histogram.h"
using namespace std;

void sortInsert(Array<char>& arr) {
    for (size_t i = 1; i < arr.size; ++i) {
        char key = arr.data[i];
        int j = (int)i - 1;

        while (j >= 0 && arr.data[j] > key) {
            arr.data[j + 1] = arr.data[j];
            j--;
        }
        arr.data[j + 1] = key;
    }
}

void countAndDeleteRepeats(Array<char>& arr, Array<int>& counts) {
    if (arr.size == 0) return;

    size_t i = 0;
    while (i < arr.size) {
        int count = 1;
        while (i + 1 < arr.size && arr.data[i + 1] == arr.data[i]) {
            count++;
            removeArray(arr, i + 1);
        }
        push_backArray(counts, count);
        i++;
    }
}

void printHistogram(const Array<char>& chars, const Array<int>& counts) {
    if (chars.size == 0) return;

    int maxHeight = 0;
    for (size_t i = 0; i < counts.size; ++i) {
        if (counts.data[i] > maxHeight) {
            maxHeight = counts.data[i];
        }
    }

    for (int level = maxHeight; level >= 1; --level) {
        for (size_t i = 0; i < counts.size; ++i) {
            if (counts.data[i] >= level) {
                cout << '#';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }

    for (size_t i = 0; i < chars.size; ++i) {
        cout << chars.data[i];
    }
    cout << endl;
}
