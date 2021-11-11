#include "CALCULATOR_NONVAR_EQUATION_HANDLE.h"


bool CALCULATOR_NONVAR_EQUATION_HANDLE::IsSpaceorTab(char c)					//Functions are like the functions in CALCULATOR_EQUATION_HANDLE, but more simpler
{																				//Less checking because there is no variable
	switch (c)
	{
	case '\t':
	case ' ':
		return true;
	default:
		return false;
	}
}

bool CALCULATOR_NONVAR_EQUATION_HANDLE::IsOperator(char c)
{
	switch (c)
	{
	case '*':
	case '-':
	case '+':
	case '^':
	case '/':
		return true;
	default:
		return false;
	}
}

bool CALCULATOR_NONVAR_EQUATION_HANDLE::getString(string& choic)
{

	bool isValid = true;
	cout << "Fill the coefficients starting with the highest order " << endl;


	getline(cin, choic);													   //This is where the user input the infix expression
	 
	choic.erase(remove_if(choic.begin(), choic.end(), bind1st(mem_fun(&CALCULATOR_NONVAR_EQUATION_HANDLE::IsSpaceorTab), this)), choic.end());    //remove all extraneous tabs, spaces
	 
	std::transform(choic.begin(), choic.end(), choic.begin(), ::tolower);                            //transform all variables to lower case

	//cout << "choic is " << choic << endl;

	string letters = "1234567890.*-+/^()";                                                               //Only numbers and operators allowed
	size_t indx = choic.find_first_not_of(letters);

	if (indx != std::string::npos)																	 //If invalid expression throw error
	{
		cout << "error at indx " << indx << " == '" << choic[indx] << "'\n" << std::endl;
		isValid = false;

		cout << "Isvalid is false\n";
	}



	if (isValid == true) {																		 //If adjacent operators found throw error, will abort expressions like 33+44
		string::iterator it;

		it = adjacent_find(choic.begin(), choic.end());


		if (it != choic.end())
		{
			cout << "Adjacent operators found\n";
			isValid = false;
		}
	}

	if ((ispunct(choic[0]) && choic[0] != '.'))													 //Can't start with operator
	{

		if (ispunct(choic[0] != ')'))
		{
			cout << "Can't start with a operator " << endl;
			isValid = false;
		}

	}

	if (isValid == true) {																		 //Can't end with operator
		if (ispunct(choic[choic.length() - 1]))
		{
			if (choic[choic.length() - 1] != ')')
			{
				cout << "Can't end with a operator " << endl;
				isValid = false;

			}


		}
	}

	parse(choic, isValid);

	return isValid;

}

void CALCULATOR_NONVAR_EQUATION_HANDLE::parseInternal(size_t& index, const string& ch, bool& isValid)				//Checks for invalid case .1232.1233
{
	do
	{
		index++;


		if (ch[index] == '.')
		{
			cout << "not valid format .1221.121 found at index " << index << endl;
			isValid = false;
			break;
		}


	} while (!(IsOperator(ch[index])) && (index < ch.length()) && isValid);

}



void CALCULATOR_NONVAR_EQUATION_HANDLE::parse(string& ch, bool& isValid)											 //Checks for many invalid cases 
{
	size_t index = 0;

	if (ch[0] == '.')
	{

		if ((!isdigit(ch[1])))
		{
			cout << "format .x found " << endl;
			isValid = false;
		}
		else
		{

			parseInternal(index, ch, isValid);
		}
	}

	if (ch[0] != '.')
		index = 1;

	for (index; index < ch.length() && isValid; index++)
	{

		if (ch[index] == '.')
		{

			if (ch[index - 1] == 'x' || (!isdigit(ch[index + 1]) && isValid))
			{
				cout << "format .x or x. found " << endl;
				isValid = false;
			}
			else
			{

				parseInternal(index, ch, isValid);

			}
		}

		if (ch[index] == '^')
		{
			bool foundParen = false;
			do
			{
				index++;
				if (ch[index] == '(')
				{
					foundParen = true;
				}

				if (ch[index] == 'x')
				{

					if (foundParen == false)
					{
						cout << "You are inputting exponential variables, please input parenthesis for precedence. " << endl;
						isValid = false;
						break;
					}

				}


			} while (index < ch.length() && isValid);
		}

	}

}


void CALCULATOR_NONVAR_EQUATION_HANDLE::fillcoeff(string& choi)
{
	//	cout << "calling fill " << endl;


	size_t nIndex = 0;

	bool isChanged = false;

	/*	if (isdigit(choi[0]))
		{

		nIndex = nIndex + 1;
		appendSharp(choi, nIndex);
		isChanged = true;

		}*/

	if (choi[0] == '(')
	{
		nIndex = nIndex + 1;
		appendSharp(choi, nIndex);
		isChanged = true;

	}

	if (isChanged == false)
	{
		nIndex = 1;
	}

	for (nIndex; nIndex <= choi.length(); nIndex++)
	{
		//cout << "Inside for loop " << endl;
		///	cout << "nindex is " << nIndex << endl;

		if (isdigit(choi[nIndex]) && (isdigit(choi[nIndex - 1])) || (choi[nIndex - 1] == '.'))
		{
			//	cout << "calling sharp " << endl;
			appendSharp(choi, nIndex);
			//	cout << "Final sharp choi is " << choi << endl;
		}

	}

	//cout << "Paren choic" << choi << endl;


}


void CALCULATOR_NONVAR_EQUATION_HANDLE::single(string& choi, size_t& nIndex)
{
	choi.insert(nIndex, 1, '(');
	nIndex++;
	choi.insert(nIndex + 1, 1, ')');
	nIndex++;

}

void CALCULATOR_NONVAR_EQUATION_HANDLE::findRightBound(string& choi, size_t& nIndex)
{

	do
	{
	//	cout << "Right before do is " << nIndex << endl;
		nIndex++;
	//	cout << "right after do is " << nIndex << endl;

	} while (!(IsOperator(choi[nIndex])) && choi[nIndex] != '\0' && choi[nIndex] != ')');



}

void CALCULATOR_NONVAR_EQUATION_HANDLE::findLeftBound(string& choi, size_t& nIndex)
{

	do {
		nIndex--;
		if (nIndex == 0)
			break;



	} while ((nIndex >= 1) && isdigit(choi[nIndex - 1]) || choi[nIndex - 1] == '.');

}





void CALCULATOR_NONVAR_EQUATION_HANDLE::appendSharp(string& choi, size_t& nIndex)
{
	//cout << "INside sharp " << endl;
	size_t left = nIndex;
	size_t right = nIndex;

	while (!(IsOperator(choi[left - 1])) && (left >= 0) && isdigit(choi[left - 1]) || choi[left - 1] == '.')
	{
		left = left - 1;

		if (left == 0)
			break;
	}

	choi.insert(left, 1, '#');
	nIndex = nIndex + 1;
	//cout << "LeftBoundIndex is: " << nIndex << endl;
	//cout << "choi after left is " << choi << endl;
	/*findLeftBound(choi, nIndex);
	cout << "LeftBoundIndex is: " << nIndex << endl;

	choi.insert(nIndex, 1, '#');

	nIndex++;*/

	//cout << "RIghtINdex before calling is " << right << endl;

	findRightBound(choi, right);
	//cout << "RIght for # is " << right << endl;
	choi.insert(right, 1, '#');
	//cout << "Right choi is " << choi << endl;


	nIndex = right;

	//cout << "Nindex after leaving sharp is " << nIndex << endl;

}