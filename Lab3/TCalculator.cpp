#include "TCalculator.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

TCalculator::TCalculator(const std::string& expr) : infixExpr(expr), stack(100) {
    toPostfix();
}

int TCalculator::precedence(char op) const {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool TCalculator::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void TCalculator::toPostfix() {
    postfixExpr = "";
    for (char c : infixExpr) {
        if (isdigit(c)) {
            postfixExpr += c;
        }
        else if (isOperator(c)) {
            while (!stack.isEmpty() && precedence(stack.Top()) >= precedence(c)) {
                postfixExpr += stack.Pop();
            }
            stack.Push(c);
        }
    }
    while (!stack.isEmpty()) {
        postfixExpr += stack.Pop();
    }
}

double TCalculator::calculate() {
    TStack<double> evalStack(100);
    for (char c : postfixExpr) {
        if (isdigit(c)) {
            evalStack.Push(c - '0'); // Преобразование символа в число
        }
        else if (isOperator(c)) {
            double b = evalStack.Pop();
            double a = evalStack.Pop();
            switch (c) {
            case '+': evalStack.Push(a + b); break;
            case '-': evalStack.Push(a - b); break;
            case '*': evalStack.Push(a * b); break;
            case '/':
                if (b == 0) throw std::runtime_error("Ошибка: деление на ноль.");
                evalStack.Push(a / b);
                break;
            }
        }
    }
    return evalStack.Pop();
}
