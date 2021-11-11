#pragma once

#include "EXCEPTION_HANDLING_INTERFACE.h"

#include "InputFailureExcept.h"

#include <sstream>
#include <iostream>

using namespace std;

class EXCEPTION_HANDLE :  public EXCEPTION_HANDLING_INTERFACE      //Basic exception handling class to handle format error/recorrect fail state;												
{																    //Will use user-defined class "InputFailureExcept.h"
public:
	EXCEPTION_HANDLE();


	void integer(int& inputVariable);                        //Exception handling for integer inputs


	void character(char& inputVariable);                    //Exception handling for character inputs


	void decimal(double& inputVariable);                    //Exception handling for decimal inputs

};

