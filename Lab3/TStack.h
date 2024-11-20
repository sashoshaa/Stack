#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
#include <string>

using namespace std;

const int MAXS = 10000; // Максимальный размер стека

// Шаблонный класс TStack (стек)
template <class T>
class TStack {
	T* pMem;            // Массив для хранения элементов стека
	int MaxSize, Num;   // Максимальный размер стека и текущий индекс

public:
	TStack(int _MaxSize = 10);       // Конструктор
	~TStack();                       // Деструктор
	TStack(const TStack& s);         // Конструктор копирования
	int GetSize() { return MaxSize; } // Получить размер стека
	int GetStartIndex() { return Num; } // Получить текущий индекс
	TStack& operator=(const TStack<T> s); // Оператор присваивания
	bool operator==(const TStack& s) const; // Сравнение на равенство
	bool operator!=(const TStack& s) const; // Сравнение на неравенство
	T Pop();         // Извлечь элемент из стека
	void Push(T val); // Добавить элемент в стек
	bool Empty() const; // Проверка на пустоту
	bool Full() const;  // Проверка на полноту
	T Top() const;      // Посмотреть верхний элемент
	void Clear();       // Очистить стек
	bool Check(string str); // Проверка скобочной последовательности

	// Ввод элемента в стек
	friend istream& operator>>(istream& in, TStack& s) {
		if (s.Full())
			throw - 1;
		Num++;
		in >> s.pMem[s.Num];
		return in;
	}

	// Вывод элемента из стека
	friend ostream& operator<<(ostream& out, const TStack& s) {
		if (s.Empty())
			throw - 1;
		out << s.pMem[s.Num];
		return out;
	}
};


// Конструктор с заданием максимального размера стека
template <class T>
TStack<T>::TStack(int _MaxSize) {
	if (_MaxSize < 0 || _MaxSize > MAXS) // Проверка на корректный размер
		throw - 1;
	MaxSize = _MaxSize; // Устанавливаем максимальный размер
	Num = -1;           // Инициализируем стек как пустой
	pMem = new T[MaxSize]; // Выделяем память под массив
}

// Конструктор копирования
template <class T>
TStack<T>::TStack(const TStack<T>& s) {
	if (s.MaxSize < 0 || s.MaxSize > MAXS || s.Num < -1 || s.Num >= s.MaxSize)
		throw - 1;
	MaxSize = s.MaxSize; // Копируем размер
	Num = s.Num;         // Копируем индекс верхнего элемента
	pMem = new T[MaxSize]; // Выделяем память
	for (int i = 0; i <= Num; i++) // Копируем элементы
		pMem[i] = s.pMem[i];
}

// Деструктор: освобождаем память
template <class T>
TStack<T>::~TStack() {
	delete[] pMem; // Удаляем массив
}

// Оператор присваивания
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T> s) {
	if (this == &s) // Проверка на самоприсваивание
		return *this;
	if (MaxSize != s.MaxSize) { // Если размеры разные, перевыделяем память
		MaxSize = s.MaxSize;
		delete[] pMem;
		pMem = new T[MaxSize];
	}
	Num = s.Num; // Копируем индекс
	for (int i = 0; i <= Num; i++) // Копируем элементы
		pMem[i] = s.pMem[i];
	return *this;
}

// Оператор сравнения на равенство
template <class T>
bool TStack<T>::operator==(const TStack& s) const {
	if (this == &s) // Если сравниваем с самим собой
		return true;
	if (MaxSize != s.MaxSize || Num != s.Num) // Сравниваем размеры и индексы
		return false;
	for (int i = 0; i <= Num; i++) { // Сравниваем элементы
		if (pMem[i] != s.pMem[i])
			return false;
	}
	return true;
}

// Оператор сравнения на неравенство
template <class T>
bool TStack<T>::operator!=(const TStack& s) const {
	return !(*this == s); // Используем оператор равенства
}

// Проверка: пуст ли стек
template <class T>
bool TStack<T>::Empty() const {
	return Num == -1; // Если индекс -1, стек пуст
}

// Проверка: полон ли стек
template <class T>
bool TStack<T>::Full() const {
	return Num == MaxSize - 1; // Если индекс равен размеру - 1, стек полон
}

// Удаление элемента с вершины стека
template <class T>
T TStack<T>::Pop() {
	if (Empty()) // Если стек пуст, ошибка
		throw - 1;
	return pMem[Num--]; // Возвращаем элемент и уменьшаем индекс
}

// Добавление элемента на вершину стека
template <class T>
void TStack<T>::Push(T val) {
	if (Full()) // Если стек полон, ошибка
		throw - 1;
	pMem[++Num] = val; // Увеличиваем индекс и добавляем элемент
}

// Получение верхнего элемента без удаления
template <class T>
T TStack<T>::Top() const {
	if (Empty()) // Если стек пуст, ошибка
		throw - 1;
	return pMem[Num]; // Возвращаем верхний элемент
}

// Очистка стека
template <class T>
void TStack<T>::Clear() {
	Num = -1; // Устанавливаем индекс в -1, делая стек пустым
}

// Проверка правильности скобочной последовательности
template <class T>
bool TStack<T>::Check(string str) {
	TStack<char> s; // Вспомогательный стек
	for (char ch : str) {
		if (ch == '(') // Если открывающая скобка, добавляем в стек
			s.Push('(');
		else if (ch == ')') { // Если закрывающая, проверяем стек
			if (s.Empty())
				return false; // Если стек пуст, последовательность некорректна
			s.Pop(); // Убираем последнюю открывающую скобку
		}
	}
	return s.Empty(); // Если стек пуст, последовательность корректна
}


// Класс TCalc для вычисления выражений
class TCalc {
	string infix;     // Инфиксное выражение
	string postfix;   // Постфиксное выражение
	TStack<double> StNum; // Стек для чисел
	TStack<char> StChar;  // Стек для операций

public:
	TCalc();
	void SetInfix(string _infix) { infix = _infix; }
	void SetPostfix(string _postfix) { postfix = _postfix; }
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
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
	string number = "";
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
	string s = "(" + infix + ")";
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
	string str = "(" + infix + ")";
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
			double num = stod(&tmp, &idx);
			StNum.Push(num * (-1.0));
			i += idx - 1;
		}
		else if (tmp >= '0' && tmp <= '9' || tmp == '.') {
			size_t idx;
			double num = stod(&tmp, &idx);
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