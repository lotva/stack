#include "Calculator.h"
#include <cmath>
#include <stdexcept>

Calculator::Calculator()
{
    infix = "";
    postfix = "";
}

int Calculator::getPriorityOf(char operation)
{
    auto it = operationPriority.find(operation);
    return it != operationPriority.end() ? it->second : 0;
}

void Calculator::toPostfix()
{
    postfix = "";
    charStack.clear();

    string withParentheses = "(" + infix + ")";
    for (int i = 0; i < withParentheses.length(); i++) {
        if (withParentheses[i] == '(') {
            charStack.push('(');
        }

        else if (isdigit(withParentheses[i])) {
            postfix += withParentheses[i];
        }

        else if (withParentheses[i] == ')') {
            char a = charStack.pop();
            while (a != '(') {
                postfix += a;
                postfix += ' ';
                a = charStack.pop();
            }
        }

        else if (operations.count(withParentheses[i])) {
            while (!charStack.isEmpty() && getPriorityOf(charStack.getTop()) >= getPriorityOf(withParentheses[i])) {
                postfix += charStack.pop();
                postfix += ' ';
            }

            charStack.push(withParentheses[i]);
        }
    }
}

double Calculator::calculatePostfix()
{
    numberStack.clear();

    for (int i = 0; i < postfix.length(); i++) {
        char currentChar = postfix[i];

        if (isdigit(currentChar)) {
            numberStack.push(currentChar - '0');
        } else if (operations.count(currentChar)) {
            double b = numberStack.pop();
            double a = numberStack.pop();
            double result = operations[currentChar](a, b);
            numberStack.push(result);
        } else {
            throw invalid_argument("Unknown operator in postfix expression");
        }
    }

    return numberStack.pop();
}