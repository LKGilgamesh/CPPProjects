//============================================================================
// Name        : Calculations.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
//#include "Main.cpp"

char Op;
double a;
double b;

int calculate(char Op, double a, double b)
{
	if(Op == '+')
	{
		cout << a+b << endl;
	}
	else if(Op == '-')
	{
		cout << a-b << endl;
	}
	else if(Op == '*')
	{
		cout << a*b << endl;
	}
	else if(Op == '/')
	{
		cout << a/b << endl;
	}
	else
	{
		cout << "Something went wrong in calculate" << endl;
	}
	return 0;
}
int exceptions(double a)
{
	bool stillWrong = true;
	while(stillWrong == true){
		if(a == 1)
		{
			cout << "Invalid Operator, please try again" << endl;
			cin >> Op;

		}
		else if(a == 2)
		{
			cout << "Divide by Zero error, please reenter the Operator" << endl;
			cin >> Op;
		}
		else{
			cout << "Something went wrong in exceptions" << endl;
		}
		if(Op == '+' || Op == '-' || Op == '*'|| Op == '/')
		{

			stillWrong = false;
			return Op;
		}
		else
		{
			cout << "It's still wrong" << endl;
		}
	}
	return 0;
}
