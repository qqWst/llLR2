#pragma once
#include <iostream>
#include "dlist.h"

class LFUCache {
private:
    int capacity;
    int size;
    DoubleList list; 

    void moveForward(DNode* node);
    void removeHead();

public:
    LFUCache(int cap);
    ~LFUCache();

    int get(int key);
    void set(int key, int value);
};