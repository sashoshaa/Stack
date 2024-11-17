#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
#include <string>
using namespace std;

const int MAXS = 10000; // Максимальный размер стека.

template <class T>
class TStack
{
	T* pMem;          // Указатель на массив для хранения элементов стека.
	int MaxSize, Num; // MaxSize - максимальный размер стека, Num - текущий индекс вершины.
public:
	TStack(int _MaxSize = 10); // Конструктор инициализации.
	~TStack();                // Деструктор.
	TStack(const TStack& s);  // Конструктор копирования.
	int GetSize() { return MaxSize; } // Возвращает размер стека.
	int GetStartIndex() { return Num; } // Возвращает текущий индекс вершины.
	TStack& operator=(const TStack<T> s); // Оператор присваивания.
	bool operator==(const TStack& s) const; // Сравнение стеков (равенство).
	bool operator!=(const TStack& s) const; // Сравнение стеков (неравенство).
	T Pop();         // Удаление элемента из вершины стека.
	void Push(T val); // Добавление элемента в стек.
	bool Empty() const; // Проверка, пуст ли стек.
	bool Full() const;  // Проверка, полон ли стек.
	T Top() const;      // Возвращает элемент на вершине без удаления.
	void Clear();       // Очищает стек.
	bool Check(string str); // Проверяет правильность скобочной последовательности.

	// Перегрузка операторов ввода и вывода.
	friend istream& operator>>(istream& in, TStack& s)
	{
		if (s.Full()) // Проверка на полноту стека.
			throw - 1;
		Num++;
		in >> s.pMem[s.Num];
		return in;
	}

	friend ostream& operator<<(ostream& out, const TStack& s)
	{
		if (s.Empty()) // Проверка на пустоту стека.
			throw - 1;
		out << s.pMem[s.Num];
		return out;
	}
};

// Реализация конструктора стека.
template <class T>
TStack<T>::TStack(int _MaxSize)
{
	if (_MaxSize < 0 || _MaxSize > MAXS) // Проверка на корректный размер.
		throw - 1;
	MaxSize = _MaxSize;   // Установка максимального размера.
	Num = -1;             // Установка начального индекса (стек пустой).
	pMem = new T[MaxSize]; // Выделение памяти под элементы.
}

// Реализация конструктора копирования.
template <class T>
TStack<T>::TStack(const TStack<T>& s)
{
	if (s.MaxSize < 0 || s.MaxSize > MAXS || s.Num < -1 || s.Num >= s.MaxSize) // Проверка валидности.
		throw - 1;
	MaxSize = s.MaxSize;
	Num = s.Num;
	pMem = new T[MaxSize]; // Выделение памяти.
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i]; // Копирование элементов.
}

// Деструктор освобождает выделенную память.
template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}

// Реализация оператора присваивания.
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T> s)
{
	if (this == &s) // Проверка присваивания самому себе.
		return *this;
	if (MaxSize != s.MaxSize) // Если размеры стеков различны, перевыделяем память.
	{
		MaxSize = s.MaxSize;
		delete[] pMem;
		pMem = new T[MaxSize];
	}
	Num = s.Num;
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i]; // Копируем элементы.
	return *this;
}

// Реализация оператора сравнения (равно).
template <class T>
bool TStack<T>::operator==(const TStack& s) const
{
	if (this == &s) // Если сравниваем с самим собой, возвращаем true.
		return true;
	if (MaxSize != s.MaxSize || Num != s.Num) // Сравниваем размеры и количество элементов.
		return false;
	for (int i = 0; i <= Num; i++)
	{
		if (pMem[i] != s.pMem[i]) // Сравниваем элементы по индексам.
			return false;
	}
	return true;
}

// Реализация оператора сравнения (не равно).
template <class T>
bool TStack<T>::operator!=(const TStack& s) const
{
	return !(*this == s);
}

// Проверка на пустоту стека.
template <class T>
bool TStack<T>::Empty() const
{
	return Num == -1;
}

// Проверка на полноту стека.
template <class T>
bool TStack<T>::Full() const
{
	return Num == MaxSize - 1;
}

// Извлечение элемента из стека.
template <class T>
T TStack<T>::Pop()
{
	if (Empty()) // Если стек пуст, бросаем исключение.
		throw - 1;
	return pMem[Num--]; // Возвращаем элемент и уменьшаем индекс.
}

// Добавление элемента в стек.
template <class T>
void TStack<T>::Push(T val)
{
	if (Full()) // Если стек полон, бросаем исключение.
		throw - 1;
	pMem[++Num] = val; // Увеличиваем индекс и добавляем элемент.
}

// Просмотр элемента на вершине стека.
template <class T>
T TStack<T>::Top() const
{
	if (Empty()) // Если стек пуст, бросаем исключение.
		throw - 1;
	return pMem[Num];
}

// Очистка стека.
template <class T>
void TStack<T>::Clear()
{
	Num = -1; // Устанавливаем индекс в -1.
}

// Проверка правильности скобочной последовательности.
template <class T>
bool TStack<T>::Check(string str)
{
	TStack<char> s; // Временный стек для проверки.
	for (char ch : str)
	{
		if (ch == '(')
			s.Push('('); // Если открывающая скобка, добавляем в стек.
		else if (ch == ')')
		{
			if (s.Empty()) // Если стек пуст, последовательность некорректна.
				return false;
			s.Pop(); // Удаляем открывающую скобку.
		}
	}
	return s.Empty(); // Если стек пустой, последовательность корректна.
}

// Класс для работы с вычислениями в инфиксной и постфиксной нотации.
class TCalc
{
	string infix;       // Инфиксная запись выражения.
	string postfix;     // Постфиксная запись выражения.
	TStack<double> StNum; // Стек для чисел.
	TStack<char> StChar;  // Стек для операторов.
public:
	TCalc(); // Конструктор.
	void SetInfix(string _infix) { infix = _infix; }   // Установка инфиксной записи.
	void SetPostfix(string _postfix) { postfix = _postfix; } // Установка постфиксной записи.
	string GetInfix() { return infix; } // Получение инфиксной записи.
	string GetPostfix() { return postfix; } // Получение постфиксной записи.
	void ToPostfix(); // Преобразование в постфиксную нотацию.
	double CalcPostfix(); // Вычисление значения постфиксного выражения.
	double Calc();        // Вычисление значения инфиксного выражения.
	int Prior(char op);   // Приоритет операций.
};

// Реализация конструктора `TCalc`.
TCalc::TCalc()
{
	StNum = TStack<double>(MAXS);
	StChar = TStack<char>(MAXS);
}

// Реализация метода для приоритета операций.
int TCalc::Prior(char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else
		return 0;
}
double TCalc::CalcPostfix() {
	// Очистка стеков перед вычислением.
	StNum.Clear();  // Очистка стека чисел.
	StChar.Clear(); // Очистка стека операторов.

	// Проходим по всем символам постфиксной записи.
	for (int i = 0; i < postfix.length(); i++) {
		// Обработка отрицательных чисел (к примеру, "-3").
		if (i > 0 && postfix[i] >= '0' && postfix[i] <= '9' && postfix[i - 1] == '_') {
			// Если текущий символ является цифрой, а предыдущий символ является "_",
			// то это означает, что перед числом был знак минус.
			StNum.Push((postfix[i] - '0') * (-1)); // Помещаем отрицательное число в стек.
		}
		// Обработка обычных положительных чисел.
		else if (postfix[i] >= '0' && postfix[i] <= '9') {
			// Если символ является цифрой, добавляем его в стек.
			StNum.Push(postfix[i] - '0');
		}
		// Обработка операторов.
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
			// Когда встречается оператор, извлекаем два числа из стека для вычислений.
			double Num2 = StNum.Pop();  // Извлекаем второе число.
			double Num1 = StNum.Pop();  // Извлекаем первое число.

			// В зависимости от оператора выполняем нужную операцию.
			if (postfix[i] == '+') {
				StNum.Push(Num1 + Num2); // Сложение.
			}
			if (postfix[i] == '-') {
				StNum.Push(Num1 - Num2); // Вычитание.
			}
			if (postfix[i] == '*') {
				StNum.Push(Num1 * Num2); // Умножение.
			}
			if (postfix[i] == '/') {
				// Проверка на деление на 0.
				if (Num2 == 0) {
					throw - 1; // Исключение при делении на ноль.
				}
				StNum.Push(Num1 / Num2); // Деление.
			}
			if (postfix[i] == '^') {
				// Проверка на отрицательные степени для отрицательных чисел.
				int p = pow(Num2, -1);  // Вычисление обратной степени.
				if (p % 2 == 0 && Num1 < 0) {
					throw - 1; // Исключение, если пытаемся возвести отрицательное число в нецелую степень.
				}
				StNum.Push(pow(Num1, Num2)); // Возведение в степень.
			}
		}
	}

	// В конце должен остаться один элемент в стеке, это и будет результат.
	int a = StNum.Pop();  // Извлекаем результат из стека.

	// Если в стеке остались еще элементы, это означает ошибку.
	if (StNum.Empty() == 0) {
		throw - 1; // Исключение, если стек не пуст.
	}

	return a;  // Возвращаем результат.
}

void TCalc::ToPostfix() {
	postfix = ""; // Очистка строки
	StChar.Clear(); // Очистка стека операторов.
	string s = "(" + infix + ")"; // Окружение скобками для удобства 

	// Проверка корректности входного выражения infix 
	if (!StChar.Check(infix)) {
		throw - 1; // Исключение в случае ошибки 
	}

	
	for (int i = 0; i < s.length(); i++) {
		// Если символ — открывающая скобка, помещаем её в стек 
		if (s[i] == '(')
			StChar.Push(s[i]);
		// Если перед открывающей скобкой идет знак минус, это означает отрицательное число (унарныцй минус)
		else if (s[i - 1] == '(' && s[i] == '-')
			postfix += '_';  // Добавляем знак подчеркивания для представления отрицательного числа.
		// Если символ является цифрой или точкой (часть числа), добавляем его в постфиксную запись.
		else if (s[i] <= '9' && s[i] >= '0' || s[i] == '.') {
			postfix += s[i];
		}
		// Если символ ), то  начинаем извлечение операторов из стека до открывающей скобки
		else if (s[i] == ')') {
			char a = StChar.Pop(); // Извлекаем оператор 
			while (a != '(') { 
				postfix += a; // Добавляем оператор в постф
				a = StChar.Pop(); 
			}
		}
		
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
			
			// извлекаем операторы из стека и добавляем их в постфикс.
			while (Prior(StChar.Top()) >= Prior(s[i]))
				postfix += StChar.Pop();
			// Добавляем текущий оператор в стек.
			StChar.Push(s[i]);
		}
		else {
			throw - 1; // Исключение в случае некорректного символа
		}
	}

	// Если в стеке остались операторы, извлекаем их и добавляем в постф
	if (StChar.Empty() == 0)
		throw - 1; // Исключение в случае ошибки 
}

double TCalc::Calc() {
	string str = "(" + infix + ")";  // Добавляем скобки 
	StNum.Clear();  // Очищаем стек для чисел
	StChar.Clear();  // Очищаем стек для операторов

	// Проверяем корректность выражения с помощью метода Check.
	if (!StChar.Check(infix)) {
		throw - 1;  // выбрасываем исключение
	}

	
	for (int i = 0; i < str.size(); i++) {
		char tmp = str[i];  //текущий символ.

		// Если символ — открывающая скобка, помещаем её в стек 
		if (tmp == '(')
			StChar.Push(tmp);

		// унарность
		else if (str[i - 1] == '(' && tmp == '-')
			str[i] = '_';  

		// Если текущий символ — цифра, и перед ним идет символ _,
		// то извлекаем число, учитывая его знак.
		else if (i > 0 && tmp >= '0' && tmp <= '9' && str[i - 1] == '_') {
			size_t idx;
			double num = stod(&tmp, &idx);  // Преобразуем строку в число с плавающей точкой
			StNum.Push(num * (-1.0));  // Добавляем отриц число
			i += idx - 1;  // Пропускаем  обработанную часть 
		}

		// Если символ — это цифра или точка (часть числа), преобразуем его в число и добавляем в стек.
		else if (tmp >= '0' && tmp <= '9' || tmp == '.') {
			size_t idx;
			double num = stod(&tmp, &idx);  // Преобразуем строку в число.
			StNum.Push(num);  // Добавляем число в стек.
			i += idx - 1;  // Пропускаем уже обработанную часть строки.
		}

		// Если встречаем закрывающую скобку, извлекаем операторы и выполняем операции.
		else if (tmp == ')') {
			char a = StChar.Pop();  // Извлекаем оператор из стека.

			// Пока не встретим скобку
			while (a != '(') {
				double Num2 = StNum.Pop();  // Извлекаем два числа 
				double Num1 = StNum.Pop();

				
				if (a == '+')
					StNum.Push(Num1 + Num2);
				if (a == '-')
					StNum.Push(Num1 - Num2);
				if (a == '*')
					StNum.Push(Num1 * Num2);
				if (a == '/') {
					if (Num2 == 0)  // Проверка на деление на 0.
						throw - 1;
					StNum.Push(Num1 / Num2);
				}
				if (a == '^') {  // Возведение в степень.
					int p = pow(Num2, -1);
					if (p % 2 == 0 && Num1 < 0)  // Проверка на невозможность возведения отрицательного числа в дробную степень.
						throw - 1;
					StNum.Push(pow(Num1, Num2)); 
				}

				a = StChar.Pop();  
			}
		}

		
		else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^') {
		
			while (Prior(StChar.Top()) >= Prior(tmp)) {
				double Num2 = StNum.Pop();  // Извлекаем два числа из стека.
				double Num1 = StNum.Pop();
				char a = StChar.Pop();  // Извлекаем оператор из стека.

				
				if (a == '+')
					StNum.Push(Num1 + Num2);
				if (a == '-')
					StNum.Push(Num1 - Num2);
				if (a == '*')
					StNum.Push(Num1 * Num2);
				if (a == '/') {
					if (Num2 == 0)  // Проверка на деление на 0.
						throw - 1;
					StNum.Push(Num1 / Num2);
				}
				if (a == '^') {  // Возведение в степень.
					int p = pow(Num2, -1);
					if (p % 2 == 0 && Num1 < 0)  // Проверка на невозможность возведения отрицательного числа в дробную степень.
						throw - 1;
					StNum.Push(pow(Num1, Num2));  // Добавляем результат возведения в степень.
				}
			}

			// Добавляем текущий оператор в стек.
			StChar.Push(tmp);
		}
	}

	// Извлекаем результат из стека.
	double a = StNum.Pop();
	if (StNum.Empty() == 0)  // Если в стеке остались числа (ошибка в выражении).
		throw - 1;

	return a;  // Возвращаем результат вычислений.
}
