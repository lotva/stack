#pragma once

#include "TStack.h"
#include <cctype>
#include <functional>
#include <stack>
#include <unordered_map>

class TCalculator {
    TStack<double> numberStack;
    TStack<char> charStack;

    std::string infix, postfix;

    std::unordered_map<char, int> operationPriority = {
        { '+', 1 },
        { '-', 1 },
        { '*', 2 },
        { '/', 2 },
        { '^', 3 }
    };

    std::unordered_map<char, std::function<double(double, double)>> operations = {
        { '+', [](double a, double b) { return std::round((a + b) * 100.0) / 100.0; } },

        { '-', [](double a, double b) { return std::round((a - b) * 100.0) / 100.0; } },

        { '*', [](double a, double b) { return std::round((a * b) * 100.0) / 100.0; } },

        { '/', [](double a, double b) {
            if (b == 0) {
                throw std::runtime_error("Division by zero!");
            }
            
            return std::round((a / b) * 100.0) / 100.0; } },

        { '^', [](double a, double b) { return pow(a, b); } }
    };

public:
    TCalculator();

    int getPriorityOf(char operation);

    std::string getInfix();
    void setInfix(std::string);

    std::string getPostfix();
    void setPostfix(std::string);

    void toPostfix();
    double calculatePostfix();
    double calculate();

    bool isUnaryMinus(size_t i) const
    {
        if (i == 0)
            return 0;

        std::string s = "(" + infix + ")";
        return (s[i] == '-') && (i == 0 || (i > 0 && s[i - 1] == '('));
    };

    double stringToDouble(const std::string& str)
    {
        double result = 0.0;
        bool negative = false;
        size_t i = 0;

        if (i < str.size() && str[i] == '-') {
            negative = true;
            i++;
        } else if (i < str.size() && str[i] == '+') {
            i++;
        }

        while (i < str.size() && isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');
            i++;
        }

        if (i < str.size() && str[i] == '.') {
            i++;
            double fraction = 1.0;
            while (i < str.size() && isdigit(str[i])) {
                fraction /= 10;
                result += (str[i] - '0') * fraction;
                i++;
            }
        }

        if (i < str.size()) {
            throw std::invalid_argument("Invalid input string");
        }
        return negative ? -result : result;
    }

    bool isExpressionValid(const std::string& expression)
    {
        std::stack<char> parentheses;
        bool lastWasOperator = true;
        bool hasDigit = false;

        for (size_t i = 0; i < expression.length(); ++i) {
            char ch = expression[i];

            if (isspace(ch)) {
                continue;
            }

            if (isdigit(ch)) {
                lastWasOperator = false;
                hasDigit = true;
            } else if (ch == '(') {
                parentheses.push(ch);
                lastWasOperator = true;
            } else if (ch == ')') {
                if (parentheses.empty()) {
                    return false;
                }
                parentheses.pop();
                lastWasOperator = false;
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                if (lastWasOperator && ch != '-') {
                    return false;
                }
                lastWasOperator = true;
            } else {
                return false;
            }
        }

        if (!parentheses.empty() || lastWasOperator || !hasDigit) {
            return false;
        }

        return true;
    }
};
