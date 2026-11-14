#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "../structs/hash_table.h"

using namespace std;
using namespace std::chrono;

/* void runDemo() {
    cout << "Имперический анализ хэш-таблиц" << endl;

    ChainHashTable chainTable{};
    CuckooHashTable cuckooTable{};
    initChainTable(chainTable, 4);
    initCuckooTable(cuckooTable, 5);

    insertChain(chainTable, "apple", "100");
    insertChain(chainTable, "banana", "200");
    insertChain(chainTable, "orange", "300");
    insertChain(chainTable, "grape", "400");
    insertChain(chainTable, "melon", "500");
    insertChain(chainTable, "apple", "150");

    cout << "\nТаблица цепочек:" << endl;
    printChainTable(chainTable);
    cout << "Поиск 'apple': " << searchChain(chainTable, "apple") << endl;
    cout << "Удаление 'banana'" << endl;
    removeChain(chainTable, "banana");
    cout << "Поиск 'banana': "
         << (searchChain(chainTable, "banana").empty() ? "не найден" : "найден") << endl;


    cout << "\nХеширование кукушки:" << endl;
    insertCuckoo(cuckooTable, "apple", "100");
    insertCuckoo(cuckooTable, "banana", "200");
    insertCuckoo(cuckooTable, "orange", "300");
    insertCuckoo(cuckooTable, "apple", "150"); 

    printCuckooTable(cuckooTable);
    cout << "Поиск 'apple': " << searchCuckoo(cuckooTable, "apple") << endl;

    freeChainTable(chainTable);
    freeCuckooTable(cuckooTable);
} */

void runEmpiricalBenchmark(size_t count) {
    ChainHashTable chainTable{};
    CuckooHashTable cuckooTable{};
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

    size_t chainFound = 0;
    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        if (!searchChain(chainTable, keys[i]).empty()) {
            chainFound++;
        }
    }
    t2 = high_resolution_clock::now();
    auto chainSearchUs = duration_cast<microseconds>(t2 - t1).count();

    size_t maxChainLen = 0;
    for (size_t i = 0; i < chainTable.capacity; ++i) {
        size_t len = sizeOfSList(chainTable.buckets[i]);
        if (len > maxChainLen) {
            maxChainLen = len;
        }
    }

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

    size_t cuckooFound = 0;
    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        if (!searchCuckoo(cuckooTable, keys[i]).empty()) {
            cuckooFound++;
        }
    }
    t2 = high_resolution_clock::now();
    auto cuckooSearchUs = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        removeCuckoo(cuckooTable, keys[i]);
    }
    t2 = high_resolution_clock::now();
    auto cuckooRemoveUs = duration_cast<microseconds>(t2 - t1).count();

    cout << "\nЭмпирический анализ для N = " << count << " элементов" << endl;
    cout << "Метод цепочек:" << endl;
    cout << "  Вставка:  " << chainInsertUs << " мкс (Коллизий: " << chainTable.collisions
         << ", Макс. длина списка: " << maxChainLen << ")" << endl;
    cout << "  Поиск:    " << chainSearchUs << " мкс (Найдено: " << chainFound << "/" << count << ")" << endl;
    cout << "  Удаление: " << chainRemoveUs << " мкс" << endl;

    cout << "Хеширование кукушки:" << endl;
    cout << "  Вставка:  " << cuckooInsertUs << " мкс (Вытеснений: " << cuckooTable.displacements << ")" << endl;
    cout << "  Поиск:    " << cuckooSearchUs << " мкс (Найдено: " << cuckooFound << "/" << count << ")" << endl;
    cout << "  Удаление: " << cuckooRemoveUs << " мкс" << endl;

    delete[] keys;
    freeChainTable(chainTable);
    freeCuckooTable(cuckooTable);
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    /* runDemo(); */

    runEmpiricalBenchmark(1000);
    runEmpiricalBenchmark(10000);
    runEmpiricalBenchmark(50000);

    return 0;
}