#pragma once
#pragma once
#include "REVERSEPOLISHNOTATION.h"
#include <string>
#include <iostream>
#include <stack>
#include <sstream>
using namespace std;


class RPN_for_Equation : public REVERSEPOLISHNOTATION             //A Reverse Polish Notation class that evaluates algebraic expressions
{
public:

	RPN_for_Equation();                                           //Default constructor

	RPN_for_Equation(string choic);                               //Parametrized constructor

	void setEquation(string choic);                               //Set function

	void InfixtoPostFix();                                        //Convert infix expression from user to postfix

	double postFixEvaluation(double x);                           //Evaluate the postfix expression with value double x

private:
	int operatorWeight(char ch) const;                            //Set operator weight

	int HasHigherPrecedence(char op1, char op2) const;            //Find which operator has higher weight
	 
	string postfix;                                               //A string that will concatenate operators first, then operands

	stack<char> sta;                                              //A stack used for InfixtoPostFix function

	stack<double> postcalculation;                                 //A stack used for postFixEvaluation function

	string choi;                                                   //User inputted infix string
};

