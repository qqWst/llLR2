#include "stack.h"
using namespace std;

void createStack(Stack& stack) {
    stack.head = nullptr;
}

bool isEmptyStack(const Stack& stack) {
    return stack.head == nullptr;
}

void pushStack(Stack& stack, const string& value) {
    StackNode* newNode = new StackNode{value, stack.head};
    stack.head = newNode;
}

string popStack(Stack& stack) {
    if (isEmptyStack(stack)) {
        return "";
    }
    StackNode* newHead = stack.head->next;
    string result = stack.head->value;
    delete stack.head;
    stack.head = newHead;
    return result;
}

string topStack(const Stack& stack) {
    if (isEmptyStack(stack)) {
        return "";
    }
    return stack.head->value;
}

void printStack(const Stack& stack) {
    if (stack.head == nullptr) {
        cout << "Стэк пуст." << endl;
        return;
    }
    for (const StackNode* currentNode = stack.head; currentNode != nullptr; currentNode = currentNode->next) {
        cout << currentNode->value << " ";
    }
    cout << endl;
}

void deleteStack(Stack& stack) {
    while (stack.head != nullptr) {
        StackNode* temp = stack.head;
        stack.head = temp->next;
        delete temp;
    }
}