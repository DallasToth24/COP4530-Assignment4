#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "Stack.h"
#include <vector>

using namespace std;
using namespace cop4530;


// ***********************************************************************
// * Function Name: bool isOperator(const string& token)                  *
// * Description: Checks if token is one of the basic operators           *
// *                                                                      *
// * Parameter Description:                                               *
// * - token: reference to a string representing the token to check       *
// * Date: 6/18/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
bool isOperator(const string& token) {
    return token == "-" || token == "+" || token == "/" || token == "*";
}

// ***********************************************************************
// * Function Name: int precedence(const string& op)                      *
// * Description: Determines the precedence level of the given operator.  *
// * Parameter Description:                                               *
// * - op: constant reference to a string representing the op             *
// * Date: 6/18/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
int precedence(const string& op) {
    switch (op[0]) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        
        default:
            return 0;
    }
}

// ***********************************************************************
// * Function Name: bool leftAssociative(const string& op)                *
// * Description: Determines if the given operator is left associative.   *
// *             all operators except '^' are left associative            *
// * Parameter Description:                                               *
// * - op: constant reference to a string representing the operator       *
// * Date: 6/20/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
bool leftAssociative(const string& op) {
    return op != "^";
}

// ***********************************************************************
// * Function Name: vector<string> tokenize(const string& expression)     *
// * Description: Tokenizes a string expression into individual           *
// *              tokens based on whitespace given                        *
// * Parameter Description:                                               *
// * - expression: A constant reference to a string representing the expression*
// * Date: 6/20/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    istringstream iss(expression);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// ***********************************************************************
// * Function Name: vector<string> infixToPostfix(const vector<string>& infix_tokens) *
// * Description: Converts an infix expression represented by a vector   *
// *              of tokens into a postfix expression                    *
// * Parameter Description:                                              *
// * - infix_tokens: constant reference to a vector of strings           *
// *                  representing the infix expression                  *
// * Date: 6/20/2024                                                     *
// * Author: Dallas Toth                                                 *
// * References: Shunting Yard Algorithm                                 *
// ***********************************************************************
vector<string> infixToPostfix(const vector<string>& infix_tokens) {
    vector<string> output;
    Stack<string> operators;

    for (const string& token : infix_tokens) {
        if (isalnum(token[0]) || (token.length() > 1 && token[0] == '.' && isdigit(token[1]))) {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
        }
            
        if (operators.empty() || operators.top() != "(") {
                throw runtime_error("Mismatched parentheses");
            }
            operators.pop();
        } else if (isOperator(token)) {
            
            while (!operators.empty() && isOperator(operators.top()) 
                &&
                   ((leftAssociative(token) && precedence(token) <= precedence(operators.top())) 
                ||
                    (!leftAssociative(token) && precedence(token) < precedence(operators.top())))) 
            {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
            
        } else {
            throw runtime_error("Invalid token: " + token);
        }
    }

    while (!operators.empty()) {
        if (operators.top() == "(") {
            throw runtime_error("Mismatched parentheses");
        }
        
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

// ***********************************************************************
// * Function Name: bool isNumeric(const string& token)                  *
// * Description: Checks if string token represents a numeric value      *
// * Parameter Description:                                              *
// * - token: constant reference to a string token to be checked         *
// * Date: 6/20/2024                                                     *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
bool isNumeric(const string& token) {
    if (token.empty()) return false;
    
    for (char c : token) {
        if (!isdigit(c) && c != '.') {
        return false;
        }
    }
return true;
}


// ***********************************************************************
// * Function Name: double evaluate_postfix(const vector<string>& postfix_tokens) *
// * Description: Evaluates a postfix expression represented by tokens   *
// * Parameter Description:                                              *
// * - postfix_tokens: A vector of strings representing tokens in the    *
// *                   postfix expression                                *
// * Date: 6/18/2024                                                     *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
double evaluate_postfix(const vector<string>& postfix_tokens) {
    Stack<double> operands;

    for (const string& token : postfix_tokens) {
        if (isNumeric(token)) {
            operands.push(stod(token));
            
        } else if (isOperator(token)) {
            
            if (operands.size() < 2) {
                throw runtime_error("Wrong operands for operator: " + token);
            }
            
            double right = operands.top(); 
            operands.pop();
            double left = operands.top(); 
            operands.pop();
            if (token == "+") operands.push(left + right);
            else if (token == "-") operands.push(left - right);
            else if (token == "*") operands.push(left * right);
            else if (token == "/") {
                
                if (right == 0) {
                    throw runtime_error("Dividing by zero");
                }
                
                operands.push(left / right);
            }
        } else {
            throw runtime_error("Invalid token in Postfix expression: "+ token);
        }
    }

    if (operands.size() != 1) {
        throw runtime_error("Invalid Postfix expression");
    }

    return operands.top();
}

int main() {
    string infix_expression;

    while (true) {
        try {
            cout << "Enter in an expression ";
            getline(cin, infix_expression);

            if (infix_expression == "exit") {
                break;
            }

            if (infix_expression.empty()) break;

            vector<string> infix_tokens = tokenize(infix_expression);
            vector<string> postfix_tokens = infixToPostfix(infix_tokens);

            cout << "The InFix Notation is: ";
            for (const string& token : infix_tokens) {
                cout << token << " ";
            }
            
            cout << endl;

            cout << "The PostFix Notation is: ";
            for (const string& token : postfix_tokens) {
                cout << token << " ";
            }
            
            cout << endl;

            bool hasVariable = false;
            for (const string& token : postfix_tokens) {
                if (!isNumeric(token) && !isOperator(token)) {
                    hasVariable = true;
                    break;
                }
            }

            if (hasVariable) {
                cout << "Results are: ";
                for (const string& token : postfix_tokens) {
                    cout << token << " ";
                }
                cout << endl;
            } else {
                double result = evaluate_postfix(postfix_tokens);
                cout << "Results are: " << result << endl;
            }

        } catch (const exception& e) {
            cerr << "Error is " << e.what() << endl;
        }
    }

    return 0;
}

