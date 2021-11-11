#include "RPN_for_Equation.h"




RPN_for_Equation::RPN_for_Equation()													//Default Constructor
{	

	choi = " ";


}

RPN_for_Equation::RPN_for_Equation(string choic)									//Parametrized Constructor
{

	choi = choic;


}

void RPN_for_Equation::setEquation(string choic)									//Set equation
{
	choi = choic;
}



int RPN_for_Equation::operatorWeight(char ch) const											//Set operator weight, power has highest weight
{
	int power(0);
	switch (ch)
	{
	case '+':
	case '-':
		power = 1;
		break;
	case '*':
	case '/':
		power = 2;
		break;
	case '^':
		power = 3;
		break;
	default:
		cout << "invalid operator" << endl;
	}
	return power;
}

int RPN_for_Equation::HasHigherPrecedence(char op1, char op2) const								//Find highest precedence operator
{
	int op1Weight = operatorWeight(op1);
	int op2Weight = operatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative.
	// return false, if right associative.
	// if operator is left-associative, left one should be given priority.
	if (op1Weight == op2Weight)
	{
		return true;
	}
	return op1Weight > op2Weight ? true : false;
}


void RPN_for_Equation::InfixtoPostFix()											//Append operands to a postfix string, then operators with precedence
{

	size_t nIndex;
	
	// cout << "evaluating to postfix" << endl;

	for (nIndex = 0; nIndex < choi.length(); nIndex++)
	{
		// cout << "Inside for loop " << endl;

		switch (choi[nIndex])
		{
		case 'x':
			//cout << "Since choi[ " << nIndex << "] is equal to x " << endl;
	//	cout << "Pushing  " << choi[nIndex] << "into postfix stack " << endl; 
			postfix += choi[nIndex]; break;
			//cout << "Since choi[ " << nIndex << "] is equal to x " << endl;
		//	cout << "Pushing  " << choi[nIndex] << "into postfix stack " << endl; 
		case '(':
		//	cout << "Pushing " << choi[nIndex] << " to stack " << endl;
			sta.push(choi[nIndex]); break;
		case '#':
		//	cout << "Pushing " << choi[nIndex] << " to stack " << endl;
			postfix += choi[nIndex]; break;
		case '+':
		case '-':
		case '*':
		case '^':
		case '/':
			while ((!sta.empty()) && (sta.top() != '(') && (HasHigherPrecedence((sta.top()), choi[nIndex])))
			{
			//	cout << "Appending  " << sta.top() << "to postfix stack " << endl;
		
				postfix += sta.top();
				sta.pop();
			}
		//	cout << "Pusing operator:  " << choi[nIndex] << "to postfix stack " << endl;
			sta.push(choi[nIndex]); break;
		case ')':
			while (sta.top() != '(')
			{
				//cout << "Pusing operator ) " << endl;
				
				postfix += sta.top();
				
				//cout << "Sta top " << sta.top() << " popped to postfix string" << endl;
				sta.pop();
			}
			sta.pop(); break;
		default:

		//	cout << "Pushing operand " << choi[nIndex] << " to postfix string " << endl;
			postfix += choi[nIndex];
			break;


		}




	}

	while (!sta.empty())
	{
		postfix += sta.top();
		sta.pop();

	}
	cout << "postfix is " << postfix << endl;
}


double RPN_for_Equation::postFixEvaluation(double x)									//Pop a stack of operators and operands until a single value or final result is found	
{
	size_t nIndex;

	cout << "double x: " << x << endl;

	//postfix = std::regex_replace(postfix, std::regex("^ +| +$|( ) +"), "$1"); //Removes leading and ending whitespaces

	//cout << "calling postfix eval" << endl;
	double a, b, temp;
	stringstream ss;

	for (nIndex = 0; nIndex < postfix.size(); nIndex++)
	{

//	cout << "CURRENT for loop is " << nIndex << endl << endl;

		if (postfix[nIndex] == '#')
		{
		//	cout << "POSTFIX 0 IS " << postfix[0] << endl;
		//	cout << "# sign found:  " << postfix[nIndex] << "  at position " << nIndex << endl;


			int before = nIndex + 1;
			double number = 0.0;
			ss.str(" ");             
			ss.clear();

			do
			{
		//		cout << "Nindex before do is " << nIndex << endl;
				if ((postfix[nIndex] == '.'))
				{
		//			cout << "point found " << endl;
					nIndex++;
					continue;

				}

				nIndex++;
		//		cout << "Nindex incrementing nIndex is " << nIndex << endl;


		//		cout << "Postfix after nIndex incrementing is [" << postfix[nIndex] << "] is " << postfix[nIndex] << endl;

			} while ((postfix[nIndex] != '#'));

		//	cout << "The spot where the second # sign ends is " << nIndex << endl;

			ss << (postfix.substr(before, nIndex - 1));                                          //Convert a string to a number using stringstream
			ss >> number;

		//	cout << "number is " << number << endl;

		//	cout << "Pushing " << number << " to postcalculation stack " << endl;
			postcalculation.push(number);
		//	cout << "Top is checking " << postcalculation.top() << endl;
		}
		else if (postfix[nIndex] == 'x')															//If the string has x letter, sustitute it with parameter double x
		{
		//	cout << "Pushing " << x << " to postcalc stack " << endl;
			postcalculation.push(x);
		}
		else if (isdigit(postfix[nIndex]))
		{
			double chur = 0.0;
			ss.str(" ");
			ss.clear();
		//	cout << "posfix[" << nIndex << "]: " << postfix[nIndex] << " is a digit " << endl;
			ss << postfix[nIndex];
			ss >> chur;
	//		cout << "Pushing exponent " << chur << " to postcalc stack " << endl;
			postcalculation.push(chur);
		}
		else
		{
			
			a = postcalculation.top();
			
			postcalculation.pop();
			b = postcalculation.top();
		
			postcalculation.pop();

			switch (postfix[nIndex])
			{
			case '+':
			//	cout << " adding " << a << " and " << b << " : result is ";
				temp = b + a;
				//cout << temp << endl; 
				break;
			case '-':
			//	cout << " subtracting " << a << " and " << b << " : result is ";
				temp = b - a;
				//cout << temp << endl; 
				break;
			case '*':
			//	cout << " multplying " << a << " and " << b << ": result is ";
				temp = b * a;
				//cout << temp << endl; 
				break;
			case '/':
			//	cout << " dividing " << a << " and " << b << ": result is ";
				temp = b / a;
				//cout << temp << endl;
				break;
			case '^':
			//	cout << " powering " << a << " and " << b << " : result is ";
				temp = pow(b, a);
				//cout << temp << endl;
				break;
			}
			postcalculation.push(temp);

		}																				
			

	}
	//cout << "Top is " << postcalculation.top() << endl;
	return postcalculation.top();

}

