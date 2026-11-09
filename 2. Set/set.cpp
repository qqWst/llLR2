#include "set.h"
using namespace std;

void createSet(Set& set, size_t initialCapacity) {
    set.capacity = initialCapacity > 0 ? initialCapacity : 16;
    set.size = 0;
    set.buckets = new SetNode*[set.capacity];
    for (size_t i = 0; i < set.capacity; ++i) {
        set.buckets[i] = nullptr;
    }
}

size_t hashSet(const string& value, size_t capacity) {
    size_t hash = 5381;
    for (size_t i = 0; i < value.size(); ++i) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(value[i]);
    }
    return hash % capacity;
}

void rehashSet(Set& set, size_t newCapacity) {
    SetNode** newBuckets = new SetNode*[newCapacity];
    for (size_t i = 0; i < newCapacity; ++i) {
        newBuckets[i] = nullptr;
    }

    for (size_t i = 0; i < set.capacity; ++i) {
        SetNode* current = set.buckets[i];
        while (current != nullptr) {
            SetNode* nextNode = current->next;
            size_t newIndex = hashSet(current->value, newCapacity);
            current->next = newBuckets[newIndex];
            newBuckets[newIndex] = current;
            current = nextNode;
        }
    }

    delete[] set.buckets;
    set.buckets = newBuckets;
    set.capacity = newCapacity;
}

bool setAt(const Set& set, const string& value) {
    if (set.buckets == nullptr || set.capacity == 0) {
        return false;
    }
    size_t index = hashSet(value, set.capacity);
    SetNode* current = set.buckets[index];
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool setAdd(Set& set, const string& value) {
    if (set.buckets == nullptr || set.capacity == 0) {
        createSet(set, 16);
    }
    if (setAt(set, value)) {
        return false;
    }
    if (set.size >= set.capacity) {
        rehashSet(set, set.capacity * 2);
    }

    size_t index = hashSet(value, set.capacity);
    SetNode* newNode = new SetNode{value, set.buckets[index]};
    set.buckets[index] = newNode;
    ++set.size;
    return true;
}

bool setDel(Set& set, const string& value) {
    if (set.buckets == nullptr || set.capacity == 0) {
        return false;
    }
    size_t index = hashSet(value, set.capacity);
    SetNode* current = set.buckets[index];
    SetNode* prev = nullptr;

    while (current != nullptr) {
        if (current->value == value) {
            if (prev == nullptr) {
                set.buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            --set.size;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void printSet(const Set& set) {
    if (set.size == 0 || set.buckets == nullptr) {
        cout << "Множество пусто." << endl;
        return;
    }
    for (size_t i = 0; i < set.capacity; ++i) {
        SetNode* current = set.buckets[i];
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
    }
    cout << endl;
}

void deleteSet(Set& set) {
    if (set.buckets != nullptr) {
        for (size_t i = 0; i < set.capacity; ++i) {
            SetNode* current = set.buckets[i];
            while (current != nullptr) {
                SetNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] set.buckets;
    }
    set.buckets = nullptr;
    set.capacity = 0;
    set.size = 0;
}