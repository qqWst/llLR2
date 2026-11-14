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

void push_frontSList(SingleList& SList, string value) {
    SNode* newNode = new SNode;
    newNode->data = value;
    newNode->next = SList.head;
    SList.head = newNode;
}

void push_backSList(SingleList& SList, string value) {
    if (SList.head == nullptr) {
        push_frontSList(SList, value);
        return;
    }
    SNode* current = SList.head;
    while (current->next != nullptr) {
        current = current->next;
    }

    SNode* newNode = new SNode;
    newNode->data = value;
    newNode->next = nullptr;
    current->next = newNode;
}

void push_afterSList(SingleList& SList, string value, string target) {
    SNode* current = SList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current != nullptr) {
        SNode* newNode = new SNode;
        newNode->data = value;
        newNode->next = current->next;
        current->next = newNode;
    }
    else {
        throw out_of_range("ОШИБКА: (push_afterSList) index вне списка!");
    }
}

void push_beforeSList(SingleList& SList, string value, string target) {
    if (SList.head == nullptr) return;
    if (SList.head->data == target) {
        push_frontSList(SList, value);
        return;
    }
    SNode* current = SList.head;
    while (current->next != nullptr && current->next->data != target) {
        current = current->next;
    }
    if (current->next != nullptr) {
        SNode* newNode = new SNode;
        newNode->data = value;
        newNode->next = current->next;
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

void pop_afterSList(SingleList& SList, string target) {
    SNode* current = SList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current != nullptr && current->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return;
    }
    if (current != nullptr && current->next == nullptr){
        return;
    }
    throw out_of_range("ОШИБКА: (popAfterSList) target вне списка!");
}

void pop_beforeSList(SingleList& SList, string target) {
    if (SList.head == nullptr || SList.head->next == nullptr || SList.head->data == target) return;
    if (SList.head->next->data == target) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    while (current->next->next != nullptr && current->next->next->data != target) {
        current = current->next;
    }
    if (current->next->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

void deleteByValueSList(SingleList& SList, string target) {
    if (SList.head == nullptr) return;
    if (SList.head->data == target) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    
    while (current->next != nullptr && current->next->data != target) {
        current = current->next;
    }
    
    if (current->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

bool getSList(const SingleList& SList, string value) {
    if (SList.head == nullptr) return false;
    SNode* current = SList.head;
    while (current != nullptr) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}

void setSList(SingleList& SList, string value, string target) {
    if (SList.head == nullptr) return;
    SNode* current = SList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current != nullptr) {
        current->data = value;
    }
}

size_t sizeOfSList(const SingleList& SList) {
    if (SList.head == nullptr) return 0;
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
    cout << "Односвязный список: " << endl;
    SNode* current = SList.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}