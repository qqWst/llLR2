#pragma once
#include <iostream>

struct LFUNode {
    int key;
    int value;
    int freq;
    LFUNode* prev;
    LFUNode* next;
};

class LFUCache {
private:
    int capacity;
    int size;
    LFUNode* head;
    LFUNode* tail;

    LFUNode* findNode(int key);
    void moveForward(LFUNode* node);
    void removeHead();

public:
    LFUCache(int cap);
    ~LFUCache();

    int get(int key);
    void set(int key, int value);
};