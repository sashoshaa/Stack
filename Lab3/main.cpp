
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
		c.SetInfix("(4-8+(9-6)^5+7/8+3*6)");
		c.ToPostfix();
		cout << c.CalcPostfix() << endl;
		c.SetInfix("4/8");
		c.ToPostfix();
		cout << c.CalcPostfix() << endl;
		c.SetInfix("-1/5");
		c.ToPostfix();
		cout << c.CalcPostfix() << endl;
		return 0;
}