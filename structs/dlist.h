#ifndef DLIST_H
#define DLIST_H
#include <iostream>

struct DNode {
    int key;
    int value;
    int freq;
    DNode* next;
    DNode* prev;
};

struct DoubleList {
    DNode* head;
    DNode* tail;
};

void createDList(DoubleList& DList);
void killDList(DoubleList& DList);
void push_frontDList(DoubleList& DList, int key, int value, int freq = 1);
void push_backDList(DoubleList& DList, int key, int value, int freq = 1);
void push_afterDList(DoubleList& DList, int key, int value, int targetKey, int freq = 1);
void push_beforeDList(DoubleList& DList, int key, int value, int targetKey, int freq = 1);
void pop_frontDList(DoubleList& DList);
void pop_backDList(DoubleList& DList);
void pop_afterDList(DoubleList& DList, int targetKey);
void pop_beforeDList(DoubleList& DList, int targetKey);
void deleteByValueDList(DoubleList& DList, int targetKey);
void setDList(DoubleList& DList, int newValue, int targetKey);
bool getDList(const DoubleList& DList, int key);
DNode* findDList(const DoubleList& DList, int key);
size_t sizeOfDList(const DoubleList& DList);
void printDList(const DoubleList& DList);

#endif