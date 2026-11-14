#include "dlist.h"
#include <iostream>

using namespace std;

void createDList(DoubleList& DList) {
    DList.head = nullptr;
    DList.tail = nullptr;
}

void killDList(DoubleList& DList) {
    while (DList.head != nullptr) {
        pop_frontDList(DList);
    }
}

void push_frontDList(DoubleList& DList, int key, int value, int freq) {
    DNode* newNode = new DNode{ key, value, freq, DList.head, nullptr };

    if (DList.head != nullptr) {
        DList.head->prev = newNode;
    } else {
        DList.tail = newNode;
    }

    DList.head = newNode;
}

void push_backDList(DoubleList& DList, int key, int value, int freq) {
    DNode* newNode = new DNode{ key, value, freq, nullptr, DList.tail };

    if (DList.tail != nullptr) {
        DList.tail->next = newNode;
    } else {
        DList.head = newNode;
    }

    DList.tail = newNode;
}

void push_afterDList(DoubleList& DList, int key, int value, int targetKey, int freq) {
    DNode* current = findDList(DList, targetKey);
    if (current == nullptr) return;

    DNode* newNode = new DNode{ key, value, freq, current->next, current };

    if (current->next != nullptr) {
        current->next->prev = newNode;
    } else {
        DList.tail = newNode;
    }

    current->next = newNode;
}

void push_beforeDList(DoubleList& DList, int key, int value, int targetKey, int freq) {
    DNode* current = findDList(DList, targetKey);
    if (current == nullptr) return;

    DNode* newNode = new DNode{ key, value, freq, current, current->prev };

    if (current->prev != nullptr) {
        current->prev->next = newNode;
    } else {
        DList.head = newNode;
    }

    current->prev = newNode;
}

void pop_frontDList(DoubleList& DList) {
    if (DList.head == nullptr) return;

    DNode* temp = DList.head;
    DList.head = DList.head->next;

    if (DList.head != nullptr) {
        DList.head->prev = nullptr;
    } else {
        DList.tail = nullptr;
    }

    delete temp;
}

void pop_backDList(DoubleList& DList) {
    if (DList.tail == nullptr) return;

    DNode* temp = DList.tail;
    DList.tail = DList.tail->prev;

    if (DList.tail != nullptr) {
        DList.tail->next = nullptr;
    } else {
        DList.head = nullptr;
    }

    delete temp;
}

void pop_afterDList(DoubleList& DList, int targetKey) {
    DNode* current = findDList(DList, targetKey);
    if (current == nullptr || current->next == nullptr) return;

    DNode* temp = current->next;
    current->next = temp->next;

    if (temp->next != nullptr) {
        temp->next->prev = current;
    } else {
        DList.tail = current;
    }

    delete temp;
}

void pop_beforeDList(DoubleList& DList, int targetKey) {
    DNode* current = findDList(DList, targetKey);
    if (current == nullptr || current->prev == nullptr) return;

    DNode* temp = current->prev;
    current->prev = temp->prev;

    if (temp->prev != nullptr) {
        temp->prev->next = current;
    } else {
        DList.head = current;
    }

    delete temp;
}

void deleteByValueDList(DoubleList& DList, int targetKey) {
    DNode* current = findDList(DList, targetKey);
    if (current == nullptr) return;

    if (current == DList.head) {
        pop_frontDList(DList);
        return;
    }

    if (current == DList.tail) {
        pop_backDList(DList);
        return;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    delete current;
}

void setDList(DoubleList& DList, int newValue, int targetKey) {
    DNode* current = findDList(DList, targetKey);
    if (current != nullptr) {
        current->value = newValue;
    }
}

bool getDList(const DoubleList& DList, int key) {
    return findDList(DList, key) != nullptr;
}

DNode* findDList(const DoubleList& DList, int key) {
    DNode* current = DList.head;
    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

size_t sizeOfDList(const DoubleList& DList) {
    size_t count = 0;
    DNode* current = DList.head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void printDList(const DoubleList& DList) {
    if (DList.head == nullptr) {
        cout << "Двусвязный список пуст." << endl;
        return;
    }

    cout << "Двусвязный список:" << endl;
    DNode* current = DList.head;
    while (current != nullptr) {
        cout << "[" << current->key << ":" << current->value << "(f=" << current->freq << ")] ";
        current = current->next;
    }
    cout << endl;
}