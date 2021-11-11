#pragma once

#include <string>
#include <iostream>

using namespace std;

class CALCULATOR_INTERFACE
{
public:

	virtual void derivative(double) = 0;     //Basic functions of a calculator: derivative, findsolution, print, and Input, this is ADT

	virtual void printCalc() const = 0;

	virtual void findSolution(int, double) = 0;

	virtual void Input(string, int) = 0;

};

