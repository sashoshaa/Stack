#include <iostream>
#include "TStack.h"
using namespace std;
int main()
{
	TStack<int> s(10);
	s.Push(3);
	s.Push(4);
	s.Push(2);

	TCalc c;
	c.SetInfix("4.1+5");   // Устанавливаем инфиксное выражение
	c.ToPostfix();
	cout << c.CalcPostfix() << endl;
	return 0;
}