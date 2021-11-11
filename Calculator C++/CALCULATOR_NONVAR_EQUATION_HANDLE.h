#pragma once

#include "EXCEPTION_HANDLE.h"
#include <functional>
#include <iostream>
#include <algorithm>
using namespace std;

class CALCULATOR_NONVAR_EQUATION_HANDLE :           //The class that deals with non-algebraic mathematical expressions; almost the same as CALCULATOR_EQUATION_HANDLE class
	public EXCEPTION_HANDLE
{
public:

	bool getString(string& choic);                 //Will get user input with this function

	void fillcoeff(string& choi);                  //This function will parse the expression the right way calling all the below private functions

private:

	bool IsSpaceorTab(char c);                     //Checks if user inputted many tabs

	bool IsOperator(char c);                        //Checks if its operator +,-,*,/,(,)

	void parse(string& ch, bool& isValid);          //Parse checks for many error conditions

	void parseInternal(size_t& index, const string& ch, bool& isValid);    //Checks for error input of the form: ".1221.121"

	void single(string& choi, size_t& nIndex);         //A function that activates if user only inputted one number                

	void findRightBound(string& choi, size_t& nIndex);    //Helper function to find right bound index

	void findLeftBound(string& choi, size_t& nIndex);     //Helper function to find left bound index

	void appendSharp(string& choi, size_t& nIndex);   //Append # between each number(multi-number) for RPN evaluation

};

