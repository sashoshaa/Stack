
#include <iostream>
#include "TStack.h"
	using namespace std;
	int main()
	{
		TStack<int> s(10);
		s.Push(3);
		s.Push(4);
		s.Push(2);
		//cout << s.Pop() << endl;
		TCalc c;
		c.SetInfix("-3+4");
		c.ToPostfix() ;
		double a = c.CalcPostfix();
		cout << c.CalcPostfix() << endl;
	return 0;
}