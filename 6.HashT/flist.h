#ifndef FLIST_H
#define FLIST_H
#include <iostream>
#include <string>
#include <stdexcept>

struct SNode {
    std::string key;
    std::string value;
    SNode* next;
};

struct SingleList {
    SNode* head;
};

void createSList(SingleList& SList);
void killSList(SingleList& SList);

void push_frontSList(SingleList& SList, std::string key, std::string value = "");
void push_backSList(SingleList& SList, std::string key, std::string value = "");
void push_afterSList(SingleList& SList, std::string key, std::string targetKey, std::string value = "");
void push_beforeSList(SingleList& SList, std::string key, std::string targetKey, std::string value = "");

void pop_frontSList(SingleList& SList);
void pop_backSList(SingleList& SList);
void pop_afterSList(SingleList& SList, std::string targetKey);
void pop_beforeSList(SingleList& SList, std::string targetKey);
bool deleteByValueSList(SingleList& SList, std::string targetKey);

bool getSList(const SingleList& SList, std::string key);
SNode* findSList(const SingleList& SList, std::string key);
void setSList(SingleList& SList, std::string newValue, std::string targetKey);

size_t sizeOfSList(const SingleList& SList);
void printSList(const SingleList& SList);

#endif