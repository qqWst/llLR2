#include "file.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void printHelp() {
    cout << "Формат: КОМАНДА <имя_структуры> [аргументы]" << endl;
    cout << "SET: SETADD <name> <value> | SETDEL <name> <value> | SET_AT <name> <value>" << endl;
    cout << "ELSE: PRINT set <name> | HELP | EXIT" << endl;
}

const string FILE_NAME = "data.txt";

Storage<ArrOfSets> sets = {nullptr, 0, 0};

template <typename T>
static void regGrow(Storage<T>& r) {
    size_t newCap = r.capacity == 0 ? 4 : r.capacity * 2;
    T* n = new T[newCap];
    for (size_t i = 0; i < r.size; ++i) n[i] = r.items[i];
    delete[] r.items;
    r.items = n;
    r.capacity = newCap;
}

Set* fetchSet(const string& name) {
    for (size_t i = 0; i < sets.size; ++i)
        if (sets.items[i].name == name) return sets.items[i].ptr;

    if (sets.size == sets.capacity) regGrow(sets);

    Set* s = new Set;
    createSet(*s);

    sets.items[sets.size++] = {s, name};
    return s;
}

void SaveAll() {
    ofstream f(FILE_NAME);
    if (!f) return;

    for (size_t i = 0; i < sets.size; ++i) {
        Set* s = sets.items[i].ptr;
        f << "SET " << sets.items[i].name << " " << s->size << "\n";
        if (s->buckets != nullptr) {
            for (size_t j = 0; j < s->capacity; ++j) {
                for (SetNode* n = s->buckets[j]; n != nullptr; n = n->next) {
                    f << n->value << "\n";
                }
            }
        }
    }
}

void LoadAll() {
    ifstream f(FILE_NAME);
    if (!f) return;
    string tag, name;
    int count;

    while (f >> tag >> name) {
        if (f >> count) {
            f.ignore();
            if (tag == "SET") {
                Set* set = fetchSet(name);
                for (int i = 0; i < count; ++i) {
                    string s; getline(f, s);
                    setAdd(*set, s);
                }
            }
        }
    }
}

void freeEverything() {
    for (size_t i = 0; i < sets.size; ++i) {
        deleteSet(*sets.items[i].ptr);
        delete sets.items[i].ptr;
    }
    delete[] sets.items;
    sets.items = nullptr;
    sets.size = 0;
    sets.capacity = 0;
}