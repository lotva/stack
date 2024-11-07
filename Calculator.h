#pragma once

#include "TStack.h"
#include <functional>
#include <string>
#include <unordered_map>

using namespace std;

class Calculator {
    TStack<double> numberStack;
    TStack<char> charStack;

    string infix;
    string postfix;

    unordered_map<char, int> operationPriority = {
        { '+', 1 },
        { '-', 1 },
        { '*', 2 },
        { '/', 2 },
        { '^', 3 }
    };

    unordered_map<char, function<double(double, double)>> operations = {
        { '+', [](double a, double b) { return a + b; } },
        { '-', [](double a, double b) { return a - b; } },
        { '*', [](double a, double b) { return a * b; } },
        { '/', [](double a, double b) { return a / b; } },
        { '^', [](double a, double b) { return pow(a, b); } }
    };

public:
    Calculator();

    string getInfix();
    void setInfix(string);

    int getPriorityOf(char operation);

    string getPostfix();
    void setPostfix(string);

    void toPostfix();

    double calculatePostfix();

    double calculate();

    int stringToInt(char*);
    double stringToDouble(char*);
};
