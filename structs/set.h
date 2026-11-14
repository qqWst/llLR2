#pragma once
#include <iostream>
#include <string>
#include "flist.h" 

struct Set {
    SingleList* buckets; 
    size_t capacity;     
    size_t size;  
};       

void createSet(Set& set, size_t initialCapacity = 16);
size_t hashSet(const std::string& value, size_t capacity);
void rehashSet(Set& set, size_t newCapacity);

bool setAt(const Set& set, const std::string& value);
bool setAdd(Set& set, const std::string& value);
bool setDel(Set& set, const std::string& value);

void printSet(const Set& set);
void deleteSet(Set& set);