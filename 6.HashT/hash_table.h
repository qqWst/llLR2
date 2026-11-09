#pragma once
#include <iostream>
#include <string>

struct ChainNode {
    std::string key;
    std::string value;
    ChainNode* next;
};

struct ChainHashTable {
    ChainNode** buckets;
    size_t capacity;
    size_t size;
    size_t collisions;
};

void initChainTable(ChainHashTable& table, size_t capacity = 16);
void insertChain(ChainHashTable& table, const std::string& key, const std::string& value);
std::string searchChain(const ChainHashTable& table, const std::string& key);
bool removeChain(ChainHashTable& table, const std::string& key);
void printChainTable(const ChainHashTable& table);
void freeChainTable(ChainHashTable& table);

struct CuckooSlot {
    std::string key;
    std::string value;
    bool occupied;
};

struct CuckooHashTable {
    CuckooSlot* table1;
    CuckooSlot* table2;
    size_t capacity;
    size_t size;
    size_t displacements;
};

void initCuckooTable(CuckooHashTable& table, size_t capacity = 17);
void insertCuckoo(CuckooHashTable& table, const std::string& key, const std::string& value);
std::string searchCuckoo(const CuckooHashTable& table, const std::string& key);
bool removeCuckoo(CuckooHashTable& table, const std::string& key);
void printCuckooTable(const CuckooHashTable& table);
void freeCuckooTable(CuckooHashTable& table);