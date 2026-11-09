#include <iostream>
#include <string>
#include <chrono>
#include "hash_table.h"

using namespace std;
using namespace std::chrono;

void runEmpiricalBenchmark(size_t count) {
    ChainHashTable chainTable;
    CuckooHashTable cuckooTable;
    initChainTable(chainTable, 16);
    initCuckooTable(cuckooTable, 17);

    string* keys = new string[count];
    for (size_t i = 0; i < count; ++i) {
        keys[i] = "key_" + to_string(i * 37 + 13);
    }

    auto t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        insertChain(chainTable, keys[i], to_string(i));
    }
    auto t2 = high_resolution_clock::now();
    auto chainInsertUs = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        searchChain(chainTable, keys[i]);
    }
    t2 = high_resolution_clock::now();
    auto chainSearchUs = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        removeChain(chainTable, keys[i]);
    }
    t2 = high_resolution_clock::now();
    auto chainRemoveUs = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        insertCuckoo(cuckooTable, keys[i], to_string(i));
    }
    t2 = high_resolution_clock::now();
    auto cuckooInsertUs = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        searchCuckoo(cuckooTable, keys[i]);
    }
    t2 = high_resolution_clock::now();
    auto cuckooSearchUs = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        removeCuckoo(cuckooTable, keys[i]);
    }
    t2 = high_resolution_clock::now();
    auto cuckooRemoveUs = duration_cast<microseconds>(t2 - t1).count();

    cout << "\n=== Эмпирический анализ для N = " << count << " элементов ===" << endl;
    cout << "Метод цепочек:" << endl;
    cout << "  Вставка:  " << chainInsertUs << " мкс (Коллизий: " << chainTable.collisions << ")" << endl;
    cout << "  Поиск:    " << chainSearchUs << " мкс" << endl;
    cout << "  Удаление: " << chainRemoveUs << " мкс" << endl;

    cout << "Хеширование кукушки:" << endl;
    cout << "  Вставка:  " << cuckooInsertUs << " мкс (Вытеснений: " << cuckooTable.displacements << ")" << endl;
    cout << "  Поиск:    " << cuckooSearchUs << " мкс" << endl;
    cout << "  Удаление: " << cuckooRemoveUs << " мкс" << endl;

    delete[] keys;
    freeChainTable(chainTable);
    freeCuckooTable(cuckooTable);
}

int main() {
    system("chcp 65001 > nul");

    runEmpiricalBenchmark(1000);
    runEmpiricalBenchmark(10000);
    runEmpiricalBenchmark(50000);

    return 0;
}