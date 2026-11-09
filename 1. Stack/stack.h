#pragma once
#include <iostream>
#include <string>

struct StackNode {
    std::string value;
    StackNode* next;
};

struct Stack {
    StackNode* head;
};

void createStack(Stack& stack);
bool isEmptyStack(const Stack& stack);
void pushStack(Stack& stack, const std::string& value);
std::string popStack(Stack& stack);
std::string topStack(const Stack& stack);
void printStack(const Stack& stack);
void deleteStack(Stack& stack);