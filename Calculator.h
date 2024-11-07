#pragma once

#include "String"
#include "TStack.h"

using namespace std;

class Calculator {
    TStack<double> numberStack;
    TStack<char> charStack;

    string infix;
    string postfix;

public:
    Calculator();

    string getInfix();
    void setInfix(string);

    int getPriorityOf(char operation);

    string getPostfix();
    void setPostfix(string);

    void convert();

    double calculatePostfix();

    double calculate();

    int stringToInt(char*);
    double stringToInt(char*);
};
