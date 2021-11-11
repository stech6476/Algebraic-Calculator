#include <iostream>
#include <iomanip>
#include <string>

#include "RPN_for_Equation.h"
#include "CALCULATOR.h"
#include "CALCULATOR_EQUATION_HANDLE.h"
#include "CALCULATOR_NONVAR_EQUATION_HANDLE.h"
#include "RPN_for_NONVAR_EQUATION.h"

using namespace std;

void callCalc(CALCULATOR_EQUATION_HANDLE, CALCULATOR_NONVAR_EQUATION_HANDLE, int, string&); //A function that lets user decide to evaluate algebraic or non-algebraic expression

string prompt(CALCULATOR_EQUATION_HANDLE, CALCULATOR_NONVAR_EQUATION_HANDLE, int&, string); //Prompt user for infix expression

int main()								//A simple calcuator program that evaluates algebraic expressions in one variable, also finds its derivatives
{										//or evaluates a mathematical expression without variables

	string tar = " ";	
	int choice = 0; 
	CALCULATOR_EQUATION_HANDLE handle;                      //Algebraic Equation class

	CALCULATOR_NONVAR_EQUATION_HANDLE handlee;				//Non-variable Equation class

	cout << fixed << showpoint << setprecision(5);

	CALCULATOR one;                                   //Initialize calculator

	double x;

	cout << "Click 1 for Equation Calculator, 2 for Non-Equation Calculator: " << endl;


	while (choice != 9)
	{
		tar = prompt(handle, handlee, choice, tar);
		one.Input(tar, choice);                          

		if (choice == 1)                                  //Find derivative if algebraic 
		{
			int choice1;
			cout << "Click 1 for evaluation or 2 for derivative or 9 to exit." << endl;
			handle.integer(choice1);
			while (choice1 != 9)
			{

				if (choice1 == 1)
				{
					cout << "Where do you want to find the point of evaluation?" << endl;
					handle.decimal(x);
					one.findSolution(choice, x);
					one.printCalc();
				}
				else
				{
					cout << "Where do you want to find the derivative? " << endl;
					handle.decimal(x);
					one.derivative(x);
					one.printCalc();
				}
				cout << "Click 1 for evaluation or 2 for derivative or 9 to exit." << endl;
				handle.integer(choice1);
			}
		}
		else if(choice == 2)                                          //Else evaluate non-algebraic expression
		{
			one.findSolution(choice, 0);
			one.printCalc();
		}

		cout << "Click 1 for Equation Calculator, 2 for Non-Equation Calculator, or 9 to exit: " << endl;
		handle.integer(choice);
	}
	
	return 0;
}

string prompt(CALCULATOR_EQUATION_HANDLE handle, CALCULATOR_NONVAR_EQUATION_HANDLE handlee, int& choice, string tar) {

	while ((choice != 1) && (choice != 2)) {

		if ((choice != 1) && (choice != 2))
		{
			cout << "Choose 1 or 2." << endl;
		}

		handle.integer(choice);
	}

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	callCalc(handle, handlee, choice, tar);

	cout << "After parsing expression: " << tar << endl;

	return tar;
}

void callCalc(CALCULATOR_EQUATION_HANDLE handle, CALCULATOR_NONVAR_EQUATION_HANDLE handlee, int choice, string& tar)
{
	if (choice == 1)
	{
		while (1) {                                                
			try {
				                                          
				if (!handle.getString(tar))
				{
					throw("try again");
				}
				handle.fillcoeff(tar);
				break;

			}
			catch (const char* s)
			{
				cout << s << endl;

				cin.sync();
			}
		}

	}
	else
	{

		while (1) {
			try {

				if (!handlee.getString(tar))
				{
					throw("try again");
				}

				handlee.fillcoeff(tar);
				break;

			}
			catch (const char* s)
			{
				cout << s << endl;
				cin.sync();
			}
		}
	}
}