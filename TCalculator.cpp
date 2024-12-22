#include "TCalculator.h"
#include <cmath>
#include <stdexcept>

TCalculator::TCalculator()
    : infix("")
    , postfix("")
    , numberStack()
    , charStack()
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
    std::string number = "";
    int operandCount = 0;
    int operatorCount = 0;
    for (int i = 0; i < infix.size(); i++) {
        char sim = infix[i];
        if (isdigit(sim) || sim == '.') {
            number += sim; // ñîáèðàåì ÷èñëî (âêëþ÷àÿ äåñÿòè÷íóþ òî÷êó)
            if (i == infix.size() - 1 || (!isdigit(infix[i + 1]) && infix[i + 1] != '.')) // ïðîâåðêà, ÷òî ïîñëå ÷èñëà èäåò ïðîáåë èëè ñèìâîë îïåðàöèè
            {
                postfix += number + " ";
                number = "";
                operandCount++; // äîáàâëÿåì îïåðàíä
            }
        } else if (sim == '(') {
            charStack.push(sim);
        } else if (sim == ')') {
            // bool matched = false;
            while (!charStack.isEmpty() && charStack.getTop() != '(') {
                postfix += charStack.pop();
                postfix += " ";
                operatorCount++;
            }
            if (charStack.isEmpty()) {
                throw "Îøèáêà: ëèøíÿÿ çàêðûâàþùàÿ ñêîáêà";
            }
            charStack.pop();
        } else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^') {
            if (sim == '-' && (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/')) {
                postfix += "0 ";
            }
            while (!charStack.isEmpty() && getPriorityOf(charStack.getTop()) >= getPriorityOf(sim)) {
                postfix += charStack.pop();
                postfix += " ";
                operatorCount++;
            }
            charStack.push(sim);
        } else if (!isspace(sim)) {
            throw -1;
        }
    }
    while (!charStack.isEmpty()) {
        char op = charStack.pop();
        if (op == '(') {
            throw std::invalid_argument("Unmatched opening parenthesis.");
        }
        postfix += op;
        postfix += " ";
        operatorCount++;
    }
    if (operandCount - operatorCount != 1) {
        throw std::invalid_argument("Too much operands.");
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

            numberStack.push(stringToDouble(number));
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

    if (!charStack.check(infix)) {
        throw -1;
    }

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

            while (!charStack.isEmpty() && charStack.getTop() != '(') {
                char currentChar = charStack.pop();
                double b = numberStack.pop();
                double a = numberStack.pop();
                numberStack.push(operations[currentChar](a, b));
            }
            charStack.pop();
        } else if (operations.count(tmp)) {
            while (!charStack.isEmpty() && getPriorityOf(charStack.getTop()) >= getPriorityOf(tmp)) {
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
