#ifndef TCALCULATOR_H
#define TCALCULATOR_H

#include <string>
#include "TStack.h"

class TCalculator {
private:
    std::string infixExpr;      // �������� ���������
    std::string postfixExpr;    // ��������� � ����������� ������
    TStack<char> stack;         // ���� ��� ��������

    int precedence(char op) const;
    bool isOperator(char c) const;
    void toPostfix();

public:
    TCalculator(const std::string& expr);
    double calculate();
};

#endif // TCALCULATOR_H
