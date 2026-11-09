#pragma once
#include <string>
#include "set.h"

void printHelp();

extern const std::string FILE_NAME;

struct ArrOfSets { Set* ptr; std::string name; };

template <typename T>
struct Storage {
    T* items;
    size_t size;
    size_t capacity;
};

extern Storage<ArrOfSets> sets;

Set* fetchSet(const std::string& name);

void SaveAll();
void LoadAll();

void freeEverything();