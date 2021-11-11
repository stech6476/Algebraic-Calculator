#include "CALCULATOR_EQUATION_HANDLE.h"


bool CALCULATOR_EQUATION_HANDLE::IsSpaceorTab(char c)
{
	switch (c)
	{
	case '\t':
	case ' ':
		return true;
	default:
		return false;
	}
}

bool  CALCULATOR_EQUATION_HANDLE::IsOperator(char c)
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

bool  CALCULATOR_EQUATION_HANDLE::IsOperatorWithoutMult(char c)          //Switch statment without multiplication operator
{
	switch (c)
	{
	case '-':
	case '+':
	case '^':
	case '/':
	case ')':
	case '(':
		return true;
	default:
		return false;
	}
}

bool CALCULATOR_EQUATION_HANDLE::getString(string& choic)
{
	bool isValid = true;
	cout << "Fill the coefficients starting with the highest order " << endl;


	getline(cin, choic);                                                                //This is where the user input the infix expression

	choic.erase(remove_if(choic.begin(), choic.end(), bind1st(mem_fun(&CALCULATOR_EQUATION_HANDLE::IsSpaceorTab), this)), choic.end());     //remove all extraneous tabs, spaces

	std::transform(choic.begin(), choic.end(), choic.begin(), ::tolower);                  //transform all variables to lower case

	//cout << "choic is " << choic << endl;

	string letters = "1234567890.x*-+/^()";                                                  //The only varible allowed is x and numbers and operators
	size_t indx = choic.find_first_not_of(letters);

	/*string string1 = "*x";                                                                 //Can let user avoid typing 23*x expressions however, won't be valid because expressions like 23x*23x exist and vital in mathematics
	string string2 = "x*";

	if ((choic.find(string1) != string::npos) || (choic.find(string2) != string::npos))
	{
		cout << "can't append multiplication sign before or after variable " << endl;
		isValid = false;

		cout << "Isvalid is false\n";
	}*/

	if (indx != std::string::npos)                                                              //If invalid expression throw error
	{
		cout << "error at indx " << indx << " == '" << choic[indx] << "'\n" << std::endl;
		isValid = false;

		cout << "Isvalid is false\n";
	}

	if (isValid == true) {                                                   //If adjacent operators found throw error, will abort expressions like 33+44
		string::iterator it;

		it = adjacent_find(choic.begin(), choic.end());


		if (it != choic.end())
		{
			cout << "Adjacent operators found\n";
			isValid = false;
		}


	}

	if (isValid == true) {                                                          //Can't start with operator
		if (ispunct(choic[0]) && choic[0] != '.')
		{
			if (ispunct(choic[0] != ')'))
			{
				cout << "Can't start with a operator " << endl;
				isValid = false;
			}

		}


	}

	if (isValid == true) {															 //Can't end with operator
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


void CALCULATOR_EQUATION_HANDLE::parseInternal(size_t& index, const string& ch, bool& isValid)           //Checks for invalid case .1232.1233
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

void  CALCULATOR_EQUATION_HANDLE::parse(string& ch, bool& isValid)            //Checks for many invalid cases 
{
	size_t index = 0; 
	if (ch[0] == '.')                                                      //First case
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
		
			if (ch[index - 1] == 'x' || (!isdigit(ch[index + 1]) && isValid))                   //Second case 
			{
				cout << "format .x or x. found " << endl;
				isValid = false;
			}
			else
			{

				parseInternal(index, ch, isValid);

			}
		}

		if (ch[index] == '^')                             //Third case for expressions 1^x+23, should be 1^(x+23) 
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



void  CALCULATOR_EQUATION_HANDLE::single(string& choi, size_t& nIndex)
{
	size_t iterator = nIndex;
	bool finish = false;

	if (choi.length() == 1)                               //If only 1 number completely abort
	{
		finish = true;
	}
	else
	{
		choi.insert(iterator, 1, '(');                     //Else put a left parenthesis
	}

	if (finish == false)                        //This if is for expressions x*3, still unfinished
	{


		if (choi[nIndex + 2] == '*')
		{
			iterator = nIndex + 2;
			nIndex = iterator;
			//	cout << "inside asterisk iterator is: " << iterator << endl;
			do
			{
		//		cout << "Right before do is " << nIndex << endl;
				iterator = iterator + 1;
			//	cout << "right after do is " << iterator << endl;

			} while (!(IsOperatorWithoutMult(choi[iterator])) && isdigit(choi[iterator]) || choi[iterator] == 'x' && choi[iterator] != '\0');
			//findRightBound(choi, iterator);

			choi.insert(iterator, 1, ')');

			//cout << "choi in single: " << choi << endl;
			//cout << "new nIndex: " << nIndex << endl;

		}
		else                                              //Main part of function, triggered when a variable is found like 3x; will turn into (3*x)
		{
			iterator = iterator + 2;

			nIndex = iterator;

			choi.insert(iterator, 1, '*');

			findRightBound(choi, iterator);

			choi.insert(iterator, 1, ')');

			//cout << "choi in single: " << choi << endl;
			//cout << "new nIndex: " << nIndex << endl;
		}

	}


}


void CALCULATOR_EQUATION_HANDLE::fillcoeff(string& choi)               //Main function that calls all other functions
{
	//	cout << "calling fill " << endl;

	size_t nIndex = 0;
	bool isChanged = false;


	if (choi[0] == 'x')                                 //If the expressions starts with x 
	{
		single(choi, nIndex);
		isChanged = true;

	}
	else if (isdigit(choi[0]))                         //If the expression starts with a number
	{

		nIndex = nIndex + 1;
		appendSharp(choi, nIndex);
		isChanged = true;

	}
	else if (choi[0] == '(')                         //If the expression starts with left parenthesis
	{
		nIndex = nIndex + 1;
		appendSharp(choi, nIndex);
		isChanged = true;

	}

	if (isChanged == false)
	{
		nIndex = 1;
	}

	for (nIndex; nIndex <= choi.length(); nIndex++)            //Main loop that iterates through each number putting a #sharp sign between numbers, 
	{														   //and parenthesis around variables 
	//	cout << "Inside for loop " << endl;
	//	cout << "nindex is " << nIndex << endl;

		if (choi.length() > 1)
		{


			if ((choi[nIndex] == 'x') && (!isdigit(choi[nIndex - 1])) && choi[nIndex - 1] != '#')
			{

				if (choi[nIndex - 1] == '*')
				{
					//				cout << "calling paren inside asterisk " << endl;

					appendParen(choi, nIndex);

					//				cout << "Final paren choi is " << choi << endl;
				}
				/*	else if (choi[nIndex + 1] == '*')
					{
						cout << "calling paren inside asterisk " << endl;
						appendParen(choi, nIndex);

						cout << "Final paren choi is " << choi << endl;
					}
					else
					{
						single(choi, nIndex);
					}*/

			}
			else if ((choi[nIndex] == 'x'))														//If variable is detected, first input a multiplication sign after it and enclose parenthesis
			{
				/*if (choi[nIndex - 1] == '*')
				{
					cout << "calling paren inside singular asterisk " << endl;

					appendParen(choi, nIndex);

					cout << "Final paren choi is " << choi << endl;
				}
				else if (choi[nIndex + 1] == '*')
				{
					cout << "calling paren inside singular asterisk " << endl;
					appendParen(choi, nIndex);

					cout << "Final paren choi is " << choi << endl;
				}
				else
				{*/
				//			cout << "calling paren inside singular asterisk" << endl;
				choi.insert(nIndex, 1, '*');
				nIndex = nIndex + 1;
				//			cout << "After * is " << choi << endl;
				appendParen(choi, nIndex);
				//			cout << "Final paren choi is " << choi << endl;
					//	}

			}
			else if (isdigit(choi[nIndex]) || (choi[nIndex - 1] == '.'))
			{
				//		cout << "calling sharp at nIndex: " << nIndex << endl;
				appendSharp(choi, nIndex);
				//		cout << "Final sharp choi is " << choi << endl;
			}

		}

	}

	//cout << "Final choic" << choi << endl;


}


void  CALCULATOR_EQUATION_HANDLE::findRightBound(string& choi, size_t& nIndex)                      //Find the right bound index until conditions are met
{
	do
	{
	//	cout << "Right before do is " << nIndex << endl;
		nIndex = nIndex + 1;
	//	cout << "right after do is " << nIndex << endl;

	} while (!(IsOperator(choi[nIndex])) && choi[nIndex] != 'x' && choi[nIndex] != '\0');


}

void  CALCULATOR_EQUATION_HANDLE::findLeftBound(string& choi, size_t& nIndex)      //Find the left bound index until conditions are met
{

	/*do {
		nIndex--;
		if (nIndex == 0)
			break;

	} while ((nIndex >= 1) && isdigit(choi[nIndex - 1]) || choi[nIndex - 1] == '.' || choi[nIndex - 1] == '#');*/

	while (!(IsOperator(choi[nIndex])) && choi[nIndex] == '*' && (nIndex >= 0) && isdigit(choi[nIndex]) && choi[nIndex] == '.' && choi[nIndex] == '#')
	{
		nIndex = nIndex - 1;

		if (nIndex == 0)
			break;
	}


}

 
void  CALCULATOR_EQUATION_HANDLE::appendParen(string& choi, size_t& nIndex)           //Appends parenthesis around x variable for associativity 
{
	//cout << "nIndex in appendParen is " << nIndex << endl << endl;
	size_t left = nIndex;
	size_t right = nIndex;
	bool isPower = false;

	findRightBound(choi, right);
	choi.insert(right, 1, ')');

	nIndex = nIndex + 1;

	while (!(IsOperatorWithoutMult(choi[left-1])) && (left >= 0) && isdigit(choi[left-1]) || choi[left-1] == '*' || choi[left-1] == '#'|| choi[left-1] == '.' || choi[left-1] == 'x')
	{
	//	cout << "Inside left while" << endl;

		left = left - 1;

		if (left == 0)
			break;
	}

	//findLeftBound(choi, left);
	choi.insert(left, 1, '(');
	nIndex = nIndex + 1;


	/*if (choi[right] != '/0')                                             This part is for expressions with exponents, still unfinished; need to turn expressions like
	*																		23x^3 to 23(x^3)
	{
		if (choi[right + 1] == '^' && choi[right + 2] == '(')
		{

			do
			{

				right++;


			} while (choi[right] != ')');

			//findRightBound(choi, right, ' ');
			choi.insert(right, 1, ')');

			//nIndex++;

			choi.insert(left - 1, 1, '(');

			//nIndex++;
			isPower = true;
		}
		else
		{
			right++;

			findRightBound(choi, right, ' ');

			choi.insert(right, 1, ')');
			nIndex++;
			choi.insert(left - 1, 1, '(');
			isPower = true;
			nIndex++;

		}
	}*/


	/*	do
	{
	cout << "Right before do is " << right << endl;
	right++;
	cout << "right after do is " << right << endl;

	} while (!(IsOperator(choi[right])) && (right > choi.length()));

	cout << "Final Right is " << right << endl;
	if (choi[right] == '^')
	{
	do
	{
	right++;
	} while (!(IsOperator(choi[right])) && (right < choi.length()));

	cout << "Right found at " << right << endl;
	choi.insert(right, 1, ')');
	}
	else*/


	/*if (isPower == false)
	{

		choi.insert(right, 1, ')');

		cout << "Right choi is " << choi << endl;

		nIndex++;


		findLeftBound(choi, left, ' ');
		choi.insert(left, 1, '(');
		nIndex++;
	}*/

}




void CALCULATOR_EQUATION_HANDLE::appendSharp(string& choi, size_t& nIndex)     //Appends # sign around numbers to help in RPN evaluation
{
	size_t left = nIndex;
	size_t right = nIndex;
	bool isX = false;

	//cout << "INside sharp " << endl;

	if (choi[left-1] == '(')                        //Special cases such as if it starts with (x...
	{
		if (choi[left] == 'x' && isdigit(choi[left + 1])){
			choi.insert(left+1, 1, '#');
			nIndex = nIndex + 1;
			isX = true;
		}
		else if(choi[left] == 'x' && isdigit(choi[left - 1]))
		{
			while (!(IsOperator(choi[left - 1])) && (left >= 0) && isdigit(choi[left - 1]) || choi[left - 1] == '.')
			{
				left = left - 1;

				if (left == 0)
					break;
			}

			//findLeftBound(choi, left);

			//cout << "Left for # is " << left << endl;

			choi.insert(left, 1, '#');
			//cout << "left choi is " << choi << endl;
			nIndex = nIndex + 1;
		//	cout << "nIndex now is " << nIndex << endl;
			isX = true;
		}
		isX = true;
	}
	else
	{
		while (!(IsOperator(choi[left-1])) && (left >= 0) && isdigit(choi[left-1]) || choi[left-1] == '.')
		{
			left = left - 1;

			if (left == 0)
				break;
		}

		//findLeftBound(choi, left);

		//cout << "Left for # is " << left << endl;

		choi.insert(left, 1, '#');
		//cout << "left choi is " << choi << endl;
		nIndex = nIndex + 1;
		//cout << "nIndex now is " << nIndex << endl;
	}

	if (isX == false)
	{

	//	cout << "nindex is " << nIndex << endl;

		findRightBound(choi, right);
	//	cout << "RIght for # is " << right << endl;
		choi.insert(right, 1, '#');
	//	cout << "Right choi is " << choi << endl;

   //   cout << "New index after right is " << right << endl;


		nIndex = right;
		/*do
		{
			nIndex++;
		} while (!(IsOperator(choi[nIndex])) || choi[nIndex] != '#' || choi[nIndex] != '\0');*/
	//	cout << "Nindex after leaving sharp is " << nIndex << endl;
	}

}
