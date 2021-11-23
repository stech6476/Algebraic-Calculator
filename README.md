# Algebraic-Calculator
# Calculator with Different iation
C++ Calculator using Classes/ADT/RPN

The user has the ability to evaluate an infix expression by invoking Reverse Polish Notation algorithm. This will convert the infix expression to postfix following PEMDAS.<br>

Addition, Subtraction, Multiplication, Evaluation, Division <br>

A simple calculator that evaluates algebraic expressions in one variable with multiple error checking. For example, if the user typed 3.14x, the program will convert it to (3.14*x).<br>

One extra button on the calculator is the Derivative which evaluates the derivative of a literal mathematical expression at any given number using difference quotient. 
Some expressions that don't work:<br>

1) power (exponents): 2.12x^3 -> 2.12(x^3) <br>
2) adjacent checking checks for incorrect expressions such as 22\*\*22, but outputs error for 22 \* 22 <br>
3) scope creep caused some bugs for function to differentiate between user typing 3x\*3x vs program doing it automatically (3x)(3x) -> (3\*x)\*(3\*x) <br>
4) 2^(x+3); etc
5) signed numbers, exponents
