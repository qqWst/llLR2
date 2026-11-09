#include "logic.h"
#include <stdexcept>
using namespace std;

int getPriority(const string& op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|" || op == "^") return 1;
    return 0;
}

bool applyOp(Stack& values, const string& op) {
    if (op == "!") {
        if (isEmptyStack(values)) return false;
        string a = popStack(values);
        pushStack(values, (a == "0") ? "1" : "0");
    } else {
        if (isEmptyStack(values)) return false;
        string b = popStack(values);
        if (isEmptyStack(values)) return false;
        string a = popStack(values);

        int valA = (a == "1") ? 1 : 0;
        int valB = (b == "1") ? 1 : 0;
        int res = 0;

        if (op == "&") res = valA & valB;
        else if (op == "|") res = valA | valB;
        else if (op == "^") res = valA ^ valB;

        pushStack(values, res ? "1" : "0");
    }
    return true;
}

static void cleanupAndThrow(Stack& values, Stack& ops, const string& msg) {
    deleteStack(values);
    deleteStack(ops);
    throw invalid_argument(msg);
}

string evaluateExpression(const string& expr) {
    Stack values;
    Stack ops;
    createStack(values);
    createStack(ops);

    bool expectOperand = true;
    bool hasTokens = false;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (c == ' ' || c == '\t') continue;
        hasTokens = true;

        if (c == '0' || c == '1') {
            if (!expectOperand) {
                cleanupAndThrow(values, ops, "ОШИБКА: два операнда подряд, пропущен оператор (позиция " + to_string(i + 1) + ")");
            }
            pushStack(values, string(1, c));
            expectOperand = false;
        } 
        else if (c == '(') {
            if (!expectOperand) {
                cleanupAndThrow(values, ops, "ОШИБКА: пропущен оператор перед '(' (позиция " + to_string(i + 1) + ")");
            }
            pushStack(ops, "(");
            expectOperand = true;
        } 
        else if (c == ')') {
            if (expectOperand) {
                cleanupAndThrow(values, ops, "ОШИБКА: пустые скобки или пропущен операнд перед ')' (позиция " + to_string(i + 1) + ")");
            }
            while (!isEmptyStack(ops) && topStack(ops) != "(") {
                if (!applyOp(values, popStack(ops))) {
                    cleanupAndThrow(values, ops, "ОШИБКА: недостаточно операндов для операции");
                }
            }
            if (isEmptyStack(ops)) {
                cleanupAndThrow(values, ops, "ОШИБКА: лишняя закрывающая скобка ')' (позиция " + to_string(i + 1) + ")");
            }
            popStack(ops);
            expectOperand = false;
        } 
        else if (c == '!') {
            if (!expectOperand) {
                cleanupAndThrow(values, ops, "ОШИБКА: оператор '!' не может стоять после числа или ')' (позиция " + to_string(i + 1) + ")");
            }
            pushStack(ops, "!");
            expectOperand = true;
        } 
        else if (c == '&' || c == '|' || c == '^') {
            if (expectOperand) {
                cleanupAndThrow(values, ops, "ОШИБКА: пропущен операнд перед оператором '" + string(1, c) + "' (позиция " + to_string(i + 1) + ")");
            }
            string currentOp(1, c);
            while (!isEmptyStack(ops) && getPriority(topStack(ops)) >= getPriority(currentOp)) {
                if (!applyOp(values, popStack(ops))) {
                    cleanupAndThrow(values, ops, "ОШИБКА: недостаточно операндов для операции");
                }
            }
            pushStack(ops, currentOp);
            expectOperand = true;
        } 
        else {
            cleanupAndThrow(values, ops, "ОШИБКА: недопустимый символ '" + string(1, c) + "' (позиция " + to_string(i + 1) + ")");
        }
    }

    if (!hasTokens) {
        cleanupAndThrow(values, ops, "ОШИБКА: введено пустое выражение");
    }
    if (expectOperand) {
        cleanupAndThrow(values, ops, "ОШИБКА: незаконченное выражение (ожидался операнд в конце)");
    }

    while (!isEmptyStack(ops)) {
        string op = popStack(ops);
        if (op == "(") {
            cleanupAndThrow(values, ops, "ОШИБКА: не закрыта скобка '('");
        }
        if (!applyOp(values, op)) {
            cleanupAndThrow(values, ops, "ОШИБКА: недостаточно операндов для операции");
        }
    }

    string result = popStack(values);
    if (!isEmptyStack(values)) {
        cleanupAndThrow(values, ops, "ОШИБКА: некорректное выражение");
    }

    deleteStack(values);
    deleteStack(ops);
    return result;
}