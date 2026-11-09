#include "lfu.h"

LFUCache::LFUCache(int cap) {
    capacity = cap > 0 ? cap : 0;
    size = 0;
    head = nullptr;
    tail = nullptr;
}

LFUCache::~LFUCache() {
    LFUNode* current = head;
    while (current != nullptr) {
        LFUNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

LFUNode* LFUCache::findNode(int key) {
    LFUNode* current = head;
    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LFUCache::moveForward(LFUNode* node) {
    while (node->next != nullptr && node->next->freq <= node->freq) {
        LFUNode* prevNode = node->prev;
        LFUNode* nextNode = node->next;
        LFUNode* afterNext = nextNode->next;

        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        } else {
            head = nextNode;
        }
        nextNode->prev = prevNode;

        nextNode->next = node;
        node->prev = nextNode;

        node->next = afterNext;
        if (afterNext != nullptr) {
            afterNext->prev = node;
        } else {
            tail = node;
        }
    }
}

void LFUCache::removeHead() {
    if (head == nullptr) return;

    LFUNode* oldHead = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete oldHead;
    --size;
}

int LFUCache::get(int key) {
    if (capacity == 0) return -1;

    LFUNode* node = findNode(key);
    if (node == nullptr) {
        return -1;
    }

    node->freq++;
    moveForward(node);
    return node->value;
}

void LFUCache::set(int key, int value) {
    if (capacity == 0) return;

    LFUNode* node = findNode(key);
    if (node != nullptr) {
        node->value = value;
        node->freq++;
        moveForward(node);
        return;
    }

    if (size >= capacity) {
        removeHead();
    }

    LFUNode* newNode = new LFUNode{key, value, 1, nullptr, head};
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
    ++size;

    moveForward(newNode);
}