#pragma once
#include <string>
class REVERSEPOLISHNOTATION                                       //REVERSEPOLISHNOATION ADT 
{
public:
	virtual int operatorWeight(char ch) const = 0;

	virtual int HasHigherPrecedence(char op1, char op2) const = 0;

	virtual	void InfixtoPostFix() = 0;

	virtual double postFixEvaluation(double x) = 0;

};

