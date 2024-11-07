#include "Calculator.h"
#include <cmath>

double Calculator::calculatePostfix()
{
    numberStack.clear();

    for (int i = 0; i < postfix.length(); i++) {
        char currentChar = postfix[i];

        if (currentChar >= '0' && currentChar <= '9') {
            numberStack.push(currentChar - '0');
        }

        if (!(currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '^')) {
            throw -1;
        }

        double a = numberStack.pop();
        double b = numberStack.pop();

        switch (postfix[i]) {
        case '+':
            numberStack.push(a + b);
        case '-':
            numberStack.push(a - b);
        case '*':
            numberStack.push(a * b);
        case '/':
            numberStack.push(a / b);
        case '^':
            numberStack.push(pow(a, b));
        default:
            break;
        }
    }
}

int Calculator::getPriorityOf(char operation)
{
    switch (operation) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}