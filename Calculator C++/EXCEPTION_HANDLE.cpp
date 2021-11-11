#include "EXCEPTION_HANDLE.h"



EXCEPTION_HANDLE::EXCEPTION_HANDLE()
{

}



void EXCEPTION_HANDLE::integer(int& inputVariable)
{
	string test;

	while (1) {
		try {
			cin >> test;

			for (unsigned int nIndex = 0; nIndex < test.length(); nIndex++)
				if (!isdigit(test[nIndex]))
				{
					if (test[nIndex] == '-')
						throw InputFailureExcept("negatitve");
					else if (test[nIndex] == '.')
						throw InputFailureExcept("decimal");
					else
						throw InputFailureExcept("Not a digit");

				}
			stringstream strStream; //A stringstream associates a string object with a stream allowing you to read from the string as if it were a stream (like cin).
			strStream << test;
			strStream >> inputVariable;

			break;

		}
		catch (InputFailureExcept er)
		{
			cout << er.what() << endl;
			cout << "Try again " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}
	}
}


void EXCEPTION_HANDLE::character(char& inputVariable)
{


	while (1) {
		try {
			cin >> inputVariable;
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out any additional input from the stream
			if (cin.gcount() > 1) // if we cleared out more than one additional character
				throw InputFailureExcept(" More than one character detected ");
			else
			{
				inputVariable = toupper(inputVariable);
				if (inputVariable != 'P' && inputVariable != 'A')										//If the user enters a char other than P or A, throw exception
					throw InputFailureExcept("Input failure, Type in a char of P or A ");
			}


			break;

		}
		catch (InputFailureExcept er)
		{
			cout << er.what() << endl;
			cout << "Try again " << endl;

		}
	}

	//return inputVariable;

	//
}



void EXCEPTION_HANDLE::decimal(double& inputVariable) {

	string test;

	while (1) {
		try {
			cin >> test;

			for (unsigned int nIndex = 0; nIndex < test.length(); nIndex++)
			{

				if (test[nIndex] == '-')
					throw InputFailureExcept("negative");

				else if (!isdigit(test[nIndex])) {
					if (test[nIndex] == '.')
						continue;
					else
						throw InputFailureExcept("Not a digit");
				}



			}
		
			stringstream strStream;
			strStream << test;
			strStream >> inputVariable;
			

			break;

		}
		catch (InputFailureExcept er)
		{
			cout << er.what() << endl;
			cout << "Try again " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
}

