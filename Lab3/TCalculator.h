#ifndef TCALCULATOR_H
#define TCALCULATOR_H

#include <string>
#include "TStack.h"

class TCalculator {
private:
    std::string infixExpr;      // Исходное выражение
    std::string postfixExpr;    // Выражение в постфиксной записи
    TStack<char> stack;         // Стек для операций

    int precedence(char op) const;
    bool isOperator(char c) const;
    void toPostfix();

public:
    TCalculator(const std::string& expr);
    double calculate();
};

#endif // TCALCULATOR_H
