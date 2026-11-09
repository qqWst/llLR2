#ifndef FLIST_H
#define FLIST_H
#include <iostream>

struct SNode {
    std::string data;
    SNode* next;
};

struct SingleList {
    SNode* head;
};

void createSList(SingleList& SList);
void killSList(SingleList& SList);
void push_frontSList(SingleList& SList, std::string value);
void push_backSList(SingleList& SList, std::string value);
void push_afterSList(SingleList& SList, std::string value, std::string target);
void push_beforeSList(SingleList& SList, std::string value, std::string target);
void pop_frontSList(SingleList& SList);
void pop_backSList(SingleList& SList);
void pop_afterSList(SingleList& SList, std::string target);
void pop_beforeSList(SingleList& SList, std::string target);
void deleteByValueSList(SingleList& SList, std::string target);
bool getSList(const SingleList& SList, std::string value);
void setSList(SingleList& SList, std::string value, std::string target);
size_t sizeOfSList(const SingleList& SList);
void printSList(const SingleList& SList);


#endif