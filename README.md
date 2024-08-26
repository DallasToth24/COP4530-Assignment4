# COP4530-Assignment4
List, Stacks, and Queues

Educational Objectives:

Understanding stacks and their applications 

Understand the stack Abstract Data Type (ADT) and its applications. Understand infix to post-fix conversion and post-fix expression evaluation.
Statement of Work: 

Write and implement a generic stack container as an adapter class template or use an existing C++ STL. .
Write and implement a program that converts infix expression to post-fix expression and implement a program that evaluates post-fix expression using the stack container you develop.
For this assignment you may use any predefined C++ Templates or you may use your own code.  If you do use your own code,  I would suggest using your assignment #3 as a starting point. 
Project Description: 

A Stack is a type of data container/ data structure that implements the LAST-IN-FIRST-OUT (LIFO) strategy for inserting and recovering data. This is a very useful strategy, related to many types of natural programming tasks as we have discussed in class. Remember that in the generic programming paradigm, every data structure is supposed to provide encapsulation of the data collection, enabling the programmer to interact with the entire data structure in a meaningful way as a container of data. By freeing the programmer from having to know its implementation details and only exporting the interface of its efficient operations, a generic Stack provides separation of data access/manipulation from internal data representation. Programs that access the generic Stack only through the interface can be reused with any other Stack implementation. This results in modular programs with clear functionality and that are more manageable.
Goals:

Implement  a  Stack as an adapter class template using your own code or one of the C++ STL libraries. 
Write a program that parses infix arithmetic expressions to post-fix arithmetic expressions using a Stack
Write a program that evaluates post-fix arithmetic expressions using a Stack
Task1: Implement Stack adapter class template: 

Stack MUST store elements internally using a proper C++ STL container.
Your Stack implementation MUST: 
be able to store elements of an arbitrary type.
Every Stack instance MUST accept insertions as long as the system has enough free memory.
Stack MUST implement the full interface specified below
Your stack implementation MUST be in the namespace cop4530.
Interface:  If you are going to use your own Stack template, the following features of the Stack class must be implemented exactly as stated: 

Stack(): zero-argument constructor.
~Stack (): destructor.
bool empty() const: returns true if the Stack contains no elements, and false otherwise.
void clear(): delete all elements from the stack.
void push(const T& x): adds x to the Stack. copy version.
void push(T && x): adds x to the Stack. move version.
void pop(): removes and discards the most recently added element of the Stack.
T& top(): returns a reference to the most recently added element of the Stack (as a modifiable L-value).
constT& top() const: accessor that returns the most recently added element of the Stack (as a const reference)
int size() const: returns the number of elements stored in the Stack.
void print(std::ostream& os, char ofc = ' ') const: print elements of Stack to ostream os. ofc is the separator between elements in the stack when they are printed out. Note that print() prints elements in the opposite order of the Stack (that is, the oldest element should be printed first).
YOU MAY ADD ADDITIONAL MEMBER FUNCTIONS AT YOUR DISCRETION. 
Task 2:   Analysis 

Analyze the worst-case run-time complexity of the member function clear() of Stack.
Give the complexity in the form of Big-O. Your analysis can be informal; however, it must be clearly understandable by others. Note that the time complexity of the function clear() depends on the underlying adaptee class you use for the implementation of Stack.
Name the file containing the complexity analysis as "analysis.txt", in which, you should state the time complexity of clear() in the Big-O notation, your discussions on why it is so, in particular, you need to include the information on the underlying adaptee class you used in the implementation of the Stack.
Task 3: Convert Infix Notation to Postfix notation and evaluate ( if possible) 

The following are guidelines to be used in writing the infix->postfix routine
For the sake of this exercise, an arithmetic expression is a sequence of space-separated strings. Each string can represent an operand, an operator, or parentheses.
Operands: can be either a numerical value or a variable. A variable name only consists of alphanumerical letters and the underscore letter "_". A variable name starts with an alphabetical letter(upper or lower case). Numerical operands can be either integer or floating point values.
Examples of operands: "34", "5", "5.3", "a", "ab", "b1", and "a_1"
Operators are one of the characters '+', '-', '*', or '/'. As usual, '*' and '/' are regarded as having higher precedence than '+' or '-'. Note that all supported operators are binary, that is, they require two operands. There will be no unary operators. 
Parentheses: '(' or ')' raise the precedence of the operand or operation within it.  
Examples of infix notations: 
( 5 + 3 ) * 12 - 7 is an infix arithmetic expression that evaluates to 89
5 + 3 * 12 - 7 is an infix arithmetic expression that evaluates to 34
Examples of postfix notation: 
a + b1 * c + ( dd * e + f ) * G in Infix notation becomes
a b1 c * + dd e * f + G * + in Postfix notation
The initial infix notation expression is evaluated from left to right as a series of space separated tokens ( each parenthesis, operand or operation is a token).   I read everything in as strings and store them as strings. When I need to I convert the strings to integers and floats when needed.    Follow the rules below which are based upon Dijkstra's Shunting Yard Algorithm:
When an operand is read in through the input, it is immediately output. 
If an input symbol is '(', push it into stack.
If an input operator is '+', '-', '*', or '/', repeatedly print the top of the stack to the output and pop the stack until the stack is either (i) empty ; (ii) a '(' is at the top of the stack; or (iii) a lower-precedence operator is at the top of the stack. Then push the input operator into the stack. 
If input operator is ')' and the last input processed was an operator, report an error. Otherwise, repeatedly print the top of the stack to the output and pop the stack until a '(' is at the top of the stack. Then pop the stack discarding the parenthesis. If the stack is emptied without a '(' being found, report error.
If end of input is reached and the last input processed was an operator or '(', report an error. Otherwise print the top of the stack to the output and pop the stack until the stack is empty. If an '(' is found in the stack during this process, report error.
Evaluating Postfix Notations: 

After converting a given expression in infix notation to post-fix notation, you will evaluate the resulting arithmetic expression IF all the operands are numeric (int, float, etc.) values. Otherwise, if the resulting post-fix expression contains characters, your output should be the same as the input ( just the post-fix expression itself).
Example post-fix notations:
5 3 + 12 * 7 -
5 3 12 * + 7 -
3 5 * c - 10 /
What the previous output should be for each of the above: 
89
34
3 5 * c - 10 /
Algorithm to evaluate Post-fix Notations:
If the expression contains variables it cannot be evaluated. 
To achieve this, you will have an operand stack, initially empty. Assume that the expression contains only numeric operands (no variable names).
Operands are pushed into the stack as they are ready from the input.
When an operator is read from the input, remove the two values on the top of the stack, apply the operator to them, and push the result onto the stack.
If an operator is read and the stack has fewer than two elements in it, report an error.
If end of input is reached and the stack has more than one operand left in it, report an error.
If end of input is reached and the stack has exactly one operand in it, print that as the final result, or 0 if the stack is empty.
Summary of Task 3: 
Your program should expect as input from (possibly re-directed) stdin a series of space-separated strings.
If you read a1 (no space) this is the name of the variable a1 and not "a" followed by "1".
Similarly, if you read "bb 12", this is a variable "bb" followed by the number "12" and not "b" ,"b", "12" or "bb", "1" ,"2". The resulting post-fix expression should be printed to stdout.
Your program should evaluate the computed post-fix expressions that contain only numeric operands, using the above algorithm, and print the results to stdout.
Restrictions: 

The infix to post-fix conversion MUST be able to convert expressions containing both numbers and variable names.
Your program MUST be able to produce floating number evaluation (i.e., deal with floats correctly). For the sake of simplicity we will not mix integer and floating point expressions. 
Your program MUST NOT attempt to evaluate post-fix expressions containing variable names. It should print the post-fix-converted result to stdout and MAY NOT throw an exception nor reach a run time error in that case.
Your program MUST check for mismatched parentheses (this should be taken care of if you infix to post-fix expression conversion is performed properly.
Your program MUST check invalid infix expressions and report errors. We consider the following types of infix expressions as invalid expressions:
1) an operator does not have the corresponding operands,
2) an operand does not have the corresponding operator; or ) mismatched parentheses. 
Note that some checks can be performed in the expression conversion or post-fix evaluation. Your program MUST re-prompt the user for the next infix expression. Your program must be able to process several inputs before terminating (check the provided executable in2post.x to see the behavior of the program).
