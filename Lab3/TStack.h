#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
#include <string>

#define MAXS 1000 // Максимальный размер стека

// Структура для узла односвязного списка
template <class T>
struct Node {
    T data;      // Данные
    Node* next;  // Указатель на следующий элемент
};

// Шаблонный класс TStack (стек)
template <class T>
class TStack {
private:
    Node<T>* top;  // Указатель на верхний элемент стека
    size_t maxSize; // Максимальный размер стека
    size_t currentSize; // Текущий размер стека

public:
    TStack(size_t size = MAXS);          // Конструктор с параметром
    ~TStack();                           // Деструктор
    TStack(const TStack& s);             // Конструктор копирования
    TStack& operator=(const TStack<T>& s); // Оператор присваивания
    bool operator==(const TStack& s) const; // Сравнение на равенство
    bool operator!=(const TStack& s) const; // Сравнение на неравенство
    void Push(T val);                    // Добавить элемент в стек
    T Pop();                             // Извлечь элемент из стека
    bool Empty() const;                  // Проверка на пустоту
    bool Full() const;                   // Проверка на полноту стека
    T Top() const;                       // Посмотреть верхний элемент
    void Clear();                        // Очистить стек
    bool Check(const std::string& str);  // Проверка скобочной последовательности

    // Ввод элемента в стек
    friend std::istream& operator>>(std::istream& in, TStack& s) {
        T value;
        in >> value;
        s.Push(value);
        return in;
    }

    // Вывод элемента из стека
    friend std::ostream& operator<<(std::ostream& out, const TStack& s) {
        if (s.Empty())
            throw std::out_of_range("Stack is empty");
        out << s.top->data;
        return out;
    }
};

// Конструктор с параметром для стека
template <class T>
TStack<T>::TStack(size_t size) : maxSize(size), currentSize(0), top(nullptr) {
    if (size <= 0) {
        throw std::invalid_argument("Stack size must be greater than zero");
    }
    if (size > MAXS) {
        throw std::overflow_error("Stack size exceeds maximum allowed size");
    }
}

// Деструктор
template <class T>
TStack<T>::~TStack() {
    Clear();  // Освобождаем память, очищая стек
}

// Конструктор копирования
template <class T>
TStack<T>::TStack(const TStack<T>& s) : maxSize(s.maxSize), currentSize(s.currentSize), top(nullptr) {
    if (s.top == nullptr) {
        top = nullptr;
    }
    else {
        // Копируем элементы в новый стек
        Node<T>* current = s.top;
        Node<T>* last = nullptr;
        while (current != nullptr) {
            Node<T>* newNode = new Node<T>;
            newNode->data = current->data;
            newNode->next = nullptr;

            if (last == nullptr) {
                top = newNode;
            }
            else {
                last->next = newNode;
            }

            last = newNode;
            current = current->next;
        }
    }
}

// Оператор присваивания
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s) {
    if (this == &s)  // Проверка на самоприсваивание
        return *this;

    Clear();  // Очищаем текущий стек

    maxSize = s.maxSize;
    currentSize = s.currentSize;

    if (s.top == nullptr) {
        top = nullptr;
    }
    else {
        Node<T>* current = s.top;
        Node<T>* last = nullptr;
        while (current != nullptr) {
            Node<T>* newNode = new Node<T>;
            newNode->data = current->data;
            newNode->next = nullptr;

            if (last == nullptr) {
                top = newNode;
            }
            else {
                last->next = newNode;
            }

            last = newNode;
            current = current->next;
        }
    }

    return *this;
}

// Оператор сравнения на равенство
template <class T>
bool TStack<T>::operator==(const TStack<T>& s) const {
    // Сначала проверяем, что максимальные размеры стеков одинаковые
    if (maxSize != s.maxSize) {
        return false;  // Если максимальные размеры разные, стеки не равны
    }

    // Проверка размеров текущих стеков (например, они могут быть пустыми)
    if (currentSize != s.currentSize) {
        return false;  // Если текущие размеры разные, стеки не равны
    }

    // Теперь сравниваем элементы стеков
    Node<T>* current1 = top;
    Node<T>* current2 = s.top;
    while (current1 != nullptr) {
        if (current1->data != current2->data) {
            return false;  // Если элементы различаются, стеки не равны
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return true;  // Если все элементы совпали, стеки равны
}

// Оператор сравнения на неравенство
template <class T>
bool TStack<T>::operator!=(const TStack<T>& s) const {
    return !(*this == s);
}

// Добавление элемента на вершину стека
template <class T>
void TStack<T>::Push(T val) {
    if (Full()) {
        throw std::overflow_error("Stack is full");
    }
    Node<T>* newNode = new Node<T>;
    newNode->data = val;
    newNode->next = top;  // Новый элемент указывает на старую вершину
    top = newNode;        // Новый элемент становится верхним
    currentSize++;        // Увеличиваем текущий размер
}

// Удаление элемента с вершины стека
template <class T>
T TStack<T>::Pop() {
    if (Empty())
        throw std::out_of_range("Stack is empty");

    Node<T>* temp = top;
    T value = top->data;
    top = top->next;  // Перемещаем вершину на следующий элемент
    delete temp;      // Освобождаем память
    currentSize--;    // Уменьшаем текущий размер
    return value;
}

// Проверка на пустоту
template <class T>
bool TStack<T>::Empty() const {
    return top == nullptr;
}

// Проверка на полноту стека
template <class T>
bool TStack<T>::Full() const {
    return currentSize >= maxSize;
}

// Получение верхнего элемента
template <class T>
T TStack<T>::Top() const {
    if (Empty())
        throw std::out_of_range("Stack is empty");
    return top->data;
}

// Очистка стека
template <class T>
void TStack<T>::Clear() {
    while (!Empty()) {
        Pop();  // Удаляем элементы до тех пор, пока стек не станет пустым
    }
}

// Проверка скобочной последовательности
template <class T>
bool TStack<T>::Check(const std::string& str) {
    TStack<char> s;  // Вспомогательный стек для скобок
    for (char ch : str) {
        if (ch == '(') {  // Если открывающая скобка, добавляем в стек
            s.Push('(');
        }
        else if (ch == ')') {  // Если закрывающая скобка, проверяем стек
            if (s.Empty()) {
                return false;  // Если стек пуст, последовательность некорректна
            }
            s.Pop();  // Убираем последнюю открывающую скобку
        }
    }
    return s.Empty();  // Если стек пуст, последовательность корректна
}


// Класс TCalc для вычисления выражений
class TCalc {
    std::string infix;     // Инфиксное выражение
    std::string postfix;   // Постфиксное выражение
    TStack<double> StNum;  // Стек для чисел
    TStack<char> StChar;   // Стек для операций

public:
    TCalc();               // Конструктор
    void SetInfix(std::string _infix) { infix = _infix; }
    void SetPostfix(std::string _postfix) { postfix = _postfix; }
    std::string GetInfix() { return infix; }
    std::string GetPostfix() { return postfix; }
    void ToPostfix();         // Преобразование в постфикс
    double CalcPostfix();     // Вычисление постфиксного выражения
    double Calc();            // Вычисление инфиксного выражения
    int Prior(char op);       // Приоритет операции
};

// Реализация методов TCalc
TCalc::TCalc() : StNum(MAXS), StChar(MAXS) {}

int TCalc::Prior(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    return 0;
}

double TCalc::CalcPostfix() {
    StNum.Clear();
    std::string number = "";
    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9' || postfix[i] == '.' || postfix[i] == '_') {
            if (postfix[i] == '_') { // Обработка отрицательного числа
                number += '-';
            }
            else {
                number += postfix[i];
            }
        }
        else if (postfix[i] == ' ' && !number.empty()) {
            // Когда число завершено, преобразуем его в double
            StNum.Push(stod(number));
            number = "";
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
            double Num2 = StNum.Pop();
            double Num1 = StNum.Pop();
            if (postfix[i] == '+') {
                StNum.Push(Num1 + Num2);
            }
            else if (postfix[i] == '-') {
                StNum.Push(Num1 - Num2);
            }
            else if (postfix[i] == '*') {
                StNum.Push(Num1 * Num2);
            }
            else if (postfix[i] == '/') {
                if (Num2 == 0) throw - 1; // Деление на ноль
                StNum.Push(Num1 / Num2);
            }
            else if (postfix[i] == '^') {
                StNum.Push(pow(Num1, Num2));
            }
        }
    }
    if (!number.empty()) { // Если осталось число в конце
        StNum.Push(stod(number));
    }
    double a = StNum.Pop();
    if (!StNum.Empty()) {
        throw - 1; // Некорректное выражение
    }
    return a;
}


void TCalc::ToPostfix() {
	postfix = "";
	StChar.Clear();
	std::string s = "(" + infix + ")";
	if (!StChar.Check(infix)) {
		throw - 1;
	}

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			StChar.Push(s[i]);
		}
		else if (s[i - 1] == '(' && s[i] == '-') {
			postfix += "_"; // Отметить начало отрицательного числа
		}
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
			while (i < s.length() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
				postfix += s[i];
				i++;
			}
			i--; // Вернуть указатель назад
			postfix += ' '; // Разделяем числа пробелом
		}
		else if (s[i] == ')') {
			while (!StChar.Empty() && StChar.Top() != '(') {
				postfix += StChar.Pop();
				postfix += ' ';
			}
			if (!StChar.Empty()) {
				StChar.Pop(); // Убираем '('
			}
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
			while (!StChar.Empty() && Prior(StChar.Top()) >= Prior(s[i])) {
				postfix += StChar.Pop();
				postfix += ' ';
			}
			StChar.Push(s[i]);
		}
	}
	if (!StChar.Empty()) {
		throw - 1; // Если стек не пуст, выражение некорректно
	}
}

double TCalc::Calc() {
	std::string str = "(" + infix + ")";
	StNum.Clear();
	StChar.Clear();
	if (!StChar.Check(infix)) {
		throw - 1;
	}
	for (int i = 0; i < str.size(); i++)
	{
		char tmp = str[i];
		if (tmp == '(')
			StChar.Push(tmp);
		else if (str[i - 1] == '(' && tmp == '-')
			str[i] = '_';
		else if (i > 0 && tmp >= '0' && tmp <= '9' && str[i - 1] == '_')
		{
			size_t idx;
			double num = std::stod(&tmp, &idx);
			StNum.Push(num * (-1.0));
			i += idx - 1;
		}
		else if (tmp >= '0' && tmp <= '9' || tmp == '.') {
			size_t idx;
			double num = std::stod(&tmp, &idx);
			StNum.Push(num);
			i += idx - 1;
		}
		else if (tmp == ')')
		{
			char a = StChar.Pop();
			while (a != '(')
			{
				double Num2 = StNum.Pop();
				double Num1 = StNum.Pop();
				if (a == '+')
					StNum.Push(Num1 + Num2);
				if (a == '-')
					StNum.Push(Num1 - Num2);
				if (a == '*')
					StNum.Push(Num1 * Num2);
				if (a == '/')
				{
					if (Num2 == 0)
						throw - 1;
					StNum.Push(Num1 / Num2);
				}
				if (a == '^')
				{
					int p = pow(Num2, -1);
					if (p % 2 == 0 && Num1 < 0)
						throw - 1;
					StNum.Push(pow(Num1, Num2));
				}
				a = StChar.Pop();
			}
		}
		else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^')
		{
			while (Prior(StChar.Top()) >= Prior(tmp)) {
				double Num2 = StNum.Pop();
				double Num1 = StNum.Pop();
				char a = StChar.Pop();
				if (a == '+')
					StNum.Push(Num1 + Num2);
				if (a == '-')
					StNum.Push(Num1 - Num2);
				if (a == '*')
					StNum.Push(Num1 * Num2);
				if (a == '/')
				{
					if (Num2 == 0)
						throw - 1;
					StNum.Push(Num1 / Num2);
				}
				if (a == '^')
				{
					int p = pow(Num2, -1);
					if (p % 2 == 0 && Num1 < 0)
						throw - 1;
					StNum.Push(pow(Num1, Num2));
				}
			}
			StChar.Push(tmp);
		}
	}
	double a = StNum.Pop();
	if (StNum.Empty() == 0)
		throw - 1;
	return a;
}