#pragma once

class EXCEPTION_HANDLING_INTERFACE                       //This is ADT of Exception Handling class
{
public:

	virtual void integer(int& target) = 0;

	virtual void character(char& inputVariable) = 0;

	virtual void decimal(double& inputVariable) = 0;

};

