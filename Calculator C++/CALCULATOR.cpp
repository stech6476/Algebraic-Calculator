#include "CALCULATOR.h"



CALCULATOR::CALCULATOR()
{
	result = 0;
}

void CALCULATOR::Input(string choic, int inp) {

	if (inp == 1)
		equation.setEquation(choic);
	else
		equ.setEquation(choic);

}

void CALCULATOR::findSolution(int inp, double eval)                  //Invoke RPN functions
{ 
	if (inp == 1)
	{
		equation.InfixtoPostFix();
		result = equation.postFixEvaluation(eval);
	}
	else
	{
		equ.InfixtoPostFix();
		result = equ.postFixEvaluation(eval);
	}

}
 
void CALCULATOR::derivative(double x)           //Find derivative using difference quotient
{

	double deltaX = 0.0000000001;
	double deriv = 0.0;

	equation.InfixtoPostFix();

	double one = equation.postFixEvaluation(x + deltaX);
	//cout << " Deriv one: " << one << endl;
	double two = equation.postFixEvaluation(x - deltaX); 
	//cout << " Deriv two: " << two << endl;
	result = (one - two) / (2*deltaX);
	//cout << "Deriv result : " << result << endl;



}


void CALCULATOR::printCalc() const
{
	cout << endl;
	cout << "Result is " << result << endl << endl;
}