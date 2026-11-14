#include "hash_table.h"
using namespace std;

static size_t hashFunc1(const string& key, size_t capacity) {
    size_t hash = 5381;
    for (size_t i = 0; i < key.size(); ++i) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(key[i]);
    }
    return hash % capacity;
}

static size_t hashFunc2(const string& key, size_t capacity) {
    size_t hash = 2166136261u;
    for (size_t i = 0; i < key.size(); ++i) {
        hash ^= static_cast<unsigned char>(key[i]);
        hash *= 16777619u;
    }
    return hash % capacity;
}


void initChainTable(ChainHashTable& table, size_t capacity) {
    table.capacity = capacity > 0 ? capacity : 16;
    table.size = 0;
    table.collisions = 0;
    table.buckets = new SingleList[table.capacity];
    for (size_t i = 0; i < table.capacity; ++i) {
        createSList(table.buckets[i]);
    }
}

static void rehashChain(ChainHashTable& table, size_t newCapacity) {
    SingleList* newBuckets = new SingleList[newCapacity];
    for (size_t i = 0; i < newCapacity; ++i) {
        createSList(newBuckets[i]);
    }

    for (size_t i = 0; i < table.capacity; ++i) {
        SNode* curr = table.buckets[i].head;
        while (curr != nullptr) {
            size_t idx = hashFunc1(curr->key, newCapacity);
            push_frontSList(newBuckets[idx], curr->key, curr->value);
            curr = curr->next;
        }
        killSList(table.buckets[i]);
    }

    delete[] table.buckets;
    table.buckets = newBuckets;
    table.capacity = newCapacity;
}

void insertChain(ChainHashTable& table, const string& key, const string& value) {
    if (table.buckets == nullptr) {
        initChainTable(table, 16);
    }

    size_t idx = hashFunc1(key, table.capacity);
    SNode* existing = findSList(table.buckets[idx], key);
    if (existing != nullptr) {
        existing->value = value;
        return;
    }

    if (table.size >= table.capacity) {
        rehashChain(table, table.capacity * 2);
        idx = hashFunc1(key, table.capacity);
    }

    if (table.buckets[idx].head != nullptr) {
        table.collisions++;
    }

    push_frontSList(table.buckets[idx], key, value);
    table.size++;
}

string searchChain(const ChainHashTable& table, const string& key) {
    if (table.buckets == nullptr || table.capacity == 0) return "";
    size_t idx = hashFunc1(key, table.capacity);
    SNode* found = findSList(table.buckets[idx], key);
    return found != nullptr ? found->value : "";
}

bool removeChain(ChainHashTable& table, const string& key) {
    if (table.buckets == nullptr || table.capacity == 0) return false;
    size_t idx = hashFunc1(key, table.capacity);
    if (deleteByValueSList(table.buckets[idx], key)) {
        table.size--;
        return true;
    }
    return false;
}

void printChainTable(const ChainHashTable& table) {
    if (table.buckets == nullptr) return;
    for (size_t i = 0; i < table.capacity; ++i) {
        if (table.buckets[i].head != nullptr) {
            cout << "[" << i << "]: ";
            printSList(table.buckets[i]);
        }
    }
}

void freeChainTable(ChainHashTable& table) {
    if (table.buckets != nullptr) {
        for (size_t i = 0; i < table.capacity; ++i) {
            killSList(table.buckets[i]);
        }
        delete[] table.buckets;
    }
    table.buckets = nullptr;
    table.capacity = 0;
    table.size = 0;
    table.collisions = 0;
}


void initCuckooTable(CuckooHashTable& table, size_t capacity) {
    table.capacity = capacity > 0 ? capacity : 17;
    table.size = 0;
    table.displacements = 0;
    table.table1 = new CuckooSlot[table.capacity];
    table.table2 = new CuckooSlot[table.capacity];
    for (size_t i = 0; i < table.capacity; ++i) {
        table.table1[i].occupied = false;
        table.table2[i].occupied = false;
    }
}

static void rehashCuckoo(CuckooHashTable& table, size_t newCapacity) {
    CuckooSlot* oldTable1 = table.table1;
    CuckooSlot* oldTable2 = table.table2;
    size_t oldCapacity = table.capacity;
    size_t oldDisplacements = table.displacements;

    initCuckooTable(table, newCapacity);
    table.displacements = oldDisplacements;

    for (size_t i = 0; i < oldCapacity; ++i) {
        if (oldTable1[i].occupied) {
            insertCuckoo(table, oldTable1[i].key, oldTable1[i].value);
        }
        if (oldTable2[i].occupied) {
            insertCuckoo(table, oldTable2[i].key, oldTable2[i].value);
        }
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

void insertCuckoo(CuckooHashTable& table, const string& key, const string& value) {
    if (table.table1 == nullptr) {
        initCuckooTable(table, 17);
    }

    size_t h1 = hashFunc1(key, table.capacity);
    if (table.table1[h1].occupied && table.table1[h1].key == key) {
        table.table1[h1].value = value;
        return;
    }

    size_t h2 = hashFunc2(key, table.capacity);
    if (table.table2[h2].occupied && table.table2[h2].key == key) {
        table.table2[h2].value = value;
        return;
    }

    if (table.size >= table.capacity) {
        rehashCuckoo(table, table.capacity * 2 + 1);
    }

    string curKey = key;
    string curVal = value;
    const size_t MAX_LOOP = 64;

    for (size_t step = 0; step < MAX_LOOP; ++step) {
        size_t pos1 = hashFunc1(curKey, table.capacity);
        if (!table.table1[pos1].occupied) {
            table.table1[pos1] = {curKey, curVal, true};
            table.size++;
            return;
        }

        swap(curKey, table.table1[pos1].key);
        swap(curVal, table.table1[pos1].value);
        table.displacements++;

        size_t pos2 = hashFunc2(curKey, table.capacity);
        if (!table.table2[pos2].occupied) {
            table.table2[pos2] = {curKey, curVal, true};
            table.size++;
            return;
        }

        swap(curKey, table.table2[pos2].key);
        swap(curVal, table.table2[pos2].value);
        table.displacements++;
    }

    rehashCuckoo(table, table.capacity * 2 + 1);
    insertCuckoo(table, curKey, curVal);
}

string searchCuckoo(const CuckooHashTable& table, const string& key) {
    if (table.table1 == nullptr || table.capacity == 0) return "";

    size_t h1 = hashFunc1(key, table.capacity);
    if (table.table1[h1].occupied && table.table1[h1].key == key) {
        return table.table1[h1].value;
    }

    size_t h2 = hashFunc2(key, table.capacity);
    if (table.table2[h2].occupied && table.table2[h2].key == key) {
        return table.table2[h2].value;
    }

    return "";
}

bool removeCuckoo(CuckooHashTable& table, const string& key) {
    if (table.table1 == nullptr || table.capacity == 0) return false;

    size_t h1 = hashFunc1(key, table.capacity);
    if (table.table1[h1].occupied && table.table1[h1].key == key) {
        table.table1[h1].occupied = false;
        table.size--;
        return true;
    }

    size_t h2 = hashFunc2(key, table.capacity);
    if (table.table2[h2].occupied && table.table2[h2].key == key) {
        table.table2[h2].occupied = false;
        table.size--;
        return true;
    }

    return false;
}

void printCuckooTable(const CuckooHashTable& table) {
    if (table.table1 == nullptr || table.table2 == nullptr) return;
    cout << "Таблица 1" << endl;
    for (size_t i = 0; i < table.capacity; ++i) {
        if (table.table1[i].occupied) {
            cout << "[" << i << "]: (" << table.table1[i].key << " -> " << table.table1[i].value << ")" << endl;
        }
    }
    cout << "Таблица 2" << endl;
    for (size_t i = 0; i < table.capacity; ++i) {
        if (table.table2[i].occupied) {
            cout << "[" << i << "]: (" << table.table2[i].key << " -> " << table.table2[i].value << ")" << endl;
        }
    }
}

void freeCuckooTable(CuckooHashTable& table) {
    delete[] table.table1;
    delete[] table.table2;
    table.table1 = nullptr;
    table.table2 = nullptr;
    table.capacity = 0;
    table.size = 0;
}