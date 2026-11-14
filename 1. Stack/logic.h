#pragma once
#include <string>
#include "../structs/stack.h"

int getPriority(const std::string& op);
bool applyOp(Stack& values, const std::string& op);
std::string evaluateExpression(const std::string& expr);