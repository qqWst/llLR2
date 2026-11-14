#include "set.h"
using namespace std;

void createSet(Set& set, size_t initialCapacity) {
    set.capacity = initialCapacity > 0 ? initialCapacity : 16;
    set.size = 0;
    set.buckets = new SingleList[set.capacity];
    for (size_t i = 0; i < set.capacity; ++i) {
        createSList(set.buckets[i]); 
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
    SingleList* newBuckets = new SingleList[newCapacity];
    for (size_t i = 0; i < newCapacity; ++i) {
        createSList(newBuckets[i]);
    }

    for (size_t i = 0; i < set.capacity; ++i) {
        SNode* current = set.buckets[i].head;
        while (current != nullptr) {
            size_t newIndex = hashSet(current->data, newCapacity);
            push_frontSList(newBuckets[newIndex], current->data);
            current = current->next;
        }
        killSList(set.buckets[i]);
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
    return getSList(set.buckets[index], value);
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
    push_frontSList(set.buckets[index], value);
    ++set.size;
    return true;
}

bool setDel(Set& set, const string& value) {
    if (!setAt(set, value)) {
        return false;
    }
    
    size_t index = hashSet(value, set.capacity);
    deleteByValueSList(set.buckets[index], value);
    --set.size;
    return true;
}

void printSet(const Set& set) {
    if (set.size == 0 || set.buckets == nullptr) {
        cout << "Множество пусто." << endl;
        return;
    }
    for (size_t i = 0; i < set.capacity; ++i) {
        SNode* current = set.buckets[i].head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << endl;
}

void deleteSet(Set& set) {
    if (set.buckets != nullptr) {
        for (size_t i = 0; i < set.capacity; ++i) {
            killSList(set.buckets[i]); 
        }
        delete[] set.buckets; 
    }
    set.buckets = nullptr;
    set.capacity = 0;
    set.size = 0;
}