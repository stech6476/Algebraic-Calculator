#pragma once

#include "CALCULATOR_INTERFACE.h"
#include "RPN_for_Equation.h"
#include "RPN_for_NONVAR_EQUATION.h"

#include <iostream>

using namespace std;


class CALCULATOR :
	public CALCULATOR_INTERFACE
{
public:
	CALCULATOR();                           //Implement ATD with a class using "has-a" relationship/aggregation of Reverse Polish Notation
											//Objects as private members 
	void derivative(double x);
	void printCalc() const;
	void Input(string choic, int inp);
	void findSolution(int inp, double eval);

private:
	double result;
	RPN_for_Equation equation;
	RPN_for_NONVAR_EQUATION equ;
};

