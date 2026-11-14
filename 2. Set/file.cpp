#include "file.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

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
                for (SNode* n = s->buckets[j].head; n != nullptr; n = n->next) {
                    f << n->data << "\n";
                }
            }
        }
    }
}

void LoadAll() {
    ifstream f(FILE_NAME);
    if (!f) return;

    string tag;
    while (f >> tag) {
        if (tag != "SET") {
            // пропускаем неизвестную строку целиком
            string rest;
            getline(f, rest);
            continue;
        }

        string name;
        int count = 0;
        if (!(f >> name >> count)) break;

        // сброс до конца строки (учитывает \r\n)
        string dummy;
        getline(f, dummy);

        Set* set = fetchSet(name);
        for (int i = 0; i < count; ++i) {
            string value;
            if (!getline(f, value)) break;
            // удаляем возможный \r в конце (Windows)
            if (!value.empty() && value.back() == '\r')
                value.pop_back();
            if (!value.empty())
                setAdd(*set, value);
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