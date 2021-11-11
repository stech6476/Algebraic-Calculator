#pragma once

#include <iostream>
#include <string>

using namespace std;

class InputFailureExcept      //This exception class gets a message from programmer to the what function//////
{
public:
	InputFailureExcept()
	{
		message = " ";
	}
	InputFailureExcept(string str)
	{
		message = str;
	}
	string what()
	{
		return message;
	}

private:
	string message;

};
