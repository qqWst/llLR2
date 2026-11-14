#include "lfu.h"

LFUCache::LFUCache(int cap) {
    capacity = cap > 0 ? cap : 0;
    size = 0;
    createDList(list);
}

LFUCache::~LFUCache() {
    killDList(list);
    size = 0;
}

void LFUCache::moveForward(DNode* node) {
    while (node->next != nullptr && node->next->freq <= node->freq) {
        DNode* prevNode = node->prev;
        DNode* nextNode = node->next;
        DNode* afterNext = nextNode->next;

        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        } else {
            list.head = nextNode;
        }
        nextNode->prev = prevNode;

        nextNode->next = node;
        node->prev = nextNode;

        node->next = afterNext;
        if (afterNext != nullptr) {
            afterNext->prev = node;
        } else {
            list.tail = node;
        }
    }
}

void LFUCache::removeHead() {
    if (list.head == nullptr) return;
    pop_frontDList(list);
    --size;
}

int LFUCache::get(int key) {
    if (capacity == 0) return -1;

    DNode* node = findDList(list, key);
    if (node == nullptr) {
        return -1;
    }

    node->freq++;
    moveForward(node);
    return node->value;
}

void LFUCache::set(int key, int value) {
    if (capacity == 0) return;

    DNode* node = findDList(list, key);
    if (node != nullptr) {
        node->value = value;
        node->freq++;
        moveForward(node);
        return;
    }

    if (size >= capacity) {
        removeHead();
    }

    push_frontDList(list, key, value, 1);
    ++size;

    moveForward(list.head);
}