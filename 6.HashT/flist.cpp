#include "flist.h"
using namespace std;

void createSList(SingleList& SList) {
    SList.head = nullptr;
}

void killSList(SingleList& SList) {
    while (SList.head != nullptr) {
        pop_frontSList(SList);
    }
}

void push_frontSList(SingleList& SList, string key, string value) {
    SNode* newNode = new SNode{key, value, SList.head};
    SList.head = newNode;
}

void push_backSList(SingleList& SList, string key, string value) {
    if (SList.head == nullptr) {
        push_frontSList(SList, key, value);
        return;
    }
    SNode* current = SList.head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = new SNode{key, value, nullptr};
}

void push_afterSList(SingleList& SList, string key, string targetKey, string value) {
    SNode* current = SList.head;
    while (current != nullptr && current->key != targetKey) {
        current = current->next;
    }
    if (current != nullptr) {
        SNode* newNode = new SNode{key, value, current->next};
        current->next = newNode;
    } else {
        throw out_of_range("ОШИБКА: (push_afterSList) target вне списка!");
    }
}

void push_beforeSList(SingleList& SList, string key, string targetKey, string value) {
    if (SList.head == nullptr) return;
    if (SList.head->key == targetKey) {
        push_frontSList(SList, key, value);
        return;
    }
    SNode* current = SList.head;
    while (current->next != nullptr && current->next->key != targetKey) {
        current = current->next;
    }
    if (current->next != nullptr) {
        SNode* newNode = new SNode{key, value, current->next};
        current->next = newNode;
    }
}

void pop_frontSList(SingleList& SList) {
    if (SList.head == nullptr) return;
    SNode* temp = SList.head;
    SList.head = SList.head->next;
    delete temp;
}

void pop_backSList(SingleList& SList) {
    if (SList.head == nullptr) return;
    if (SList.head->next == nullptr) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

void pop_afterSList(SingleList& SList, string targetKey) {
    SNode* current = SList.head;
    while (current != nullptr && current->key != targetKey) {
        current = current->next;
    }
    if (current != nullptr && current->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return;
    }
    if (current != nullptr && current->next == nullptr) {
        return;
    }
    throw out_of_range("ОШИБКА: (pop_afterSList) target вне списка!");
}

void pop_beforeSList(SingleList& SList, string targetKey) {
    if (SList.head == nullptr || SList.head->next == nullptr || SList.head->key == targetKey) return;
    if (SList.head->next->key == targetKey) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    while (current->next->next != nullptr && current->next->next->key != targetKey) {
        current = current->next;
    }
    if (current->next->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

bool deleteByValueSList(SingleList& SList, string targetKey) {
    if (SList.head == nullptr) return false;
    if (SList.head->key == targetKey) {
        pop_frontSList(SList);
        return true;
    }
    SNode* current = SList.head;
    while (current->next != nullptr && current->next->key != targetKey) {
        current = current->next;
    }
    if (current->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }
    return false;
}

SNode* findSList(const SingleList& SList, string key) {
    SNode* current = SList.head;
    while (current != nullptr) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

bool getSList(const SingleList& SList, string key) {
    return findSList(SList, key) != nullptr;
}

void setSList(SingleList& SList, string newValue, string targetKey) {
    SNode* node = findSList(SList, targetKey);
    if (node != nullptr) {
        node->value = newValue;
    }
}

size_t sizeOfSList(const SingleList& SList) {
    size_t count = 0;
    SNode* current = SList.head;
    while (current != nullptr) {
        current = current->next;
        count++;
    }
    return count;
}

void printSList(const SingleList& SList) {
    if (SList.head == nullptr) {
        cout << "Односвязный список пуст." << endl;
        return;
    }
    SNode* current = SList.head;
    while (current != nullptr) {
        if (current->value.empty()) {
            cout << current->key << " ";
        } else {
            cout << "(" << current->key << " -> " << current->value << ") ";
        }
        current = current->next;
    }
    cout << endl;
}