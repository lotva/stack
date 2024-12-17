#include "TCalculator.h"
#include <cmath>
#include <stdexcept>

TCalculator::TCalculator()
    : infix("")
    , postfix("")
    , numberStack(100)
    , charStack(100)
{
}

std::string TCalculator::getInfix()
{
    return infix;
}

void TCalculator::setInfix(std::string in)
{
    infix = in;
}

int TCalculator::getPriorityOf(char operation)
{
    auto it = operationPriority.find(operation);
    return it != operationPriority.end() ? it->second : 0;
}

std::string TCalculator::getPostfix()
{
    return postfix;
}

void TCalculator::setPostfix(std::string p)
{
    postfix = p;
}

void TCalculator::toPostfix()
{
    postfix = "";
    charStack.clear();

    int balance = 0;

    std::string withParentheses = "(" + infix + ")";
    for (int i = 0; i < withParentheses.length(); i++) {
        if (withParentheses[i] == '(') {
            charStack.push('(');
            balance++;
        }

        else if (isdigit(withParentheses[i]) || withParentheses[i] == '.' || (i < withParentheses.length() && isUnaryMinus(i))) {
            size_t index = i;
            while (index < withParentheses.length() && ((withParentheses[index] >= '0' && withParentheses[index] <= '9') || withParentheses[index] == '.' || isUnaryMinus(index))) {
                postfix += withParentheses[index];
                index++;
            }
            postfix += " ";
            i = index - 1;
        }

        else if (withParentheses[i] == ')') {
            char a = charStack.pop();
            while (a != '(') {
                postfix += a;
                postfix += ' ';
                a = charStack.pop();
            }
            balance--;
            if (balance < 0) {
                throw std::invalid_argument("Unmatched closing parenthesis");
            }
        }

        else if (operations.count(withParentheses[i])) {
            while (!charStack.isEmpty() && getPriorityOf(charStack.top()) >= getPriorityOf(withParentheses[i])) {
                postfix += charStack.pop();
                postfix += ' ';
            }

            charStack.push(withParentheses[i]);
        }
    }
}

double TCalculator::calculatePostfix()
{
    numberStack.clear();

    for (int i = 0; i < postfix.length(); i++) {
        char currentChar = postfix[i];

        if (isdigit(currentChar) || currentChar == '.' || (currentChar == '-' && (i == 0 || postfix[i - 1] == ' '))) {
            size_t index = i;
            std::string number;
            while (index < postfix.length() && ((postfix[index] >= '0' && postfix[index] <= '9') || postfix[index] == '.' || postfix[index] == '-')) {
                number += postfix[index];
                index++;
            }

            numberStack.push(std::stod(number));
            i = index;
        }

        else if (operations.count(currentChar)) {
            double b = numberStack.pop();
            double a = numberStack.pop();
            double result = operations[currentChar](a, b);
            numberStack.push(result);
        }
    }

    return numberStack.pop();
}

double TCalculator::calculate()
{
    std::string str = "(" + infix + ")";
    numberStack.clear();
    charStack.clear();

    int balance = 0;

    for (int i = 0; i < str.length(); i++) {
        char tmp = str[i];

        if (tmp == '(') {
            charStack.push(tmp);
            balance++;
        }

        else if (isdigit(tmp) || tmp == '.' || (i < str.length() && isUnaryMinus(i))) {
            size_t idx = i;
            std::string number;
            while (idx < str.size() && ((str[idx] >= '0' && str[idx] <= '9') || str[idx] == '.' || isUnaryMinus(idx))) {
                number += str[idx];
                idx++;
            }
            numberStack.push(stringToDouble(number));
            i = idx - 1;
        }

        else if (tmp == ')') {
            balance--;
            if (balance < 0) {
                throw std::invalid_argument("Unmatched closing parenthesis");
            }

            while (!charStack.isEmpty() && charStack.top() != '(') {
                char currentChar = charStack.pop();
                double b = numberStack.pop();
                double a = numberStack.pop();
                numberStack.push(operations[currentChar](a, b));
            }
            charStack.pop();
        } else if (operations.count(tmp)) {
            while (!charStack.isEmpty() && getPriorityOf(charStack.top()) >= getPriorityOf(tmp)) {
                char currentChar = charStack.pop();
                double b = numberStack.pop();
                double a = numberStack.pop();
                numberStack.push(operations[currentChar](a, b));
            }
            charStack.push(tmp);
        }
    }

    if (balance != 0) {
        throw std::invalid_argument("Unmatched opening parenthesis");
    }

    return numberStack.pop();
}
