#pragma once

#include <iostream>
#include <string>

template <class T>
struct Node {
    T data;
    Node* next;
};

template <class T>
class TStack {
    Node<T>* top;

public:
    TStack();
    ~TStack();
    TStack(const TStack&);

    bool isEmpty() const;

    TStack& operator=(const TStack&);
    bool operator==(const TStack&) const;
    bool operator!=(const TStack&) const;

    void push(T);
    T pop();
    T getTop() const;
    void clear();
    bool check(std::string);

    friend std::istream& operator>>(std::istream& in, TStack& s)
    {
        T value;
        in >> value;
        s.push(value);
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const TStack& s)
    {
        if (s.isEmpty())
            throw std::out_of_range("Stack is empty");
        out << s.top->data;
        return out;
    }
};

template <class T>
TStack<T>::TStack()
    : top(nullptr)
{
}

template <class T>
TStack<T>::~TStack()
{
    clear();
}

template <class T>
TStack<T>::TStack(const TStack<T>& s)
    : top(nullptr)
{
    if (s.top == nullptr) {
        top = nullptr;
    } else {
        Node<T>* current = s.top;
        Node<T>* last = nullptr;
        while (current != nullptr) {
            Node<T>* temp = new Node<T>;
            temp->data = current->data;
            temp->next = nullptr;

            if (last == nullptr) {
                top = temp;
            } else {
                last->next = temp;
            }

            last = temp;
            current = current->next;
        }
    }
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s)
{
    if (this == &s)
        return *this;

    clear();

    if (s.top == nullptr) {
        top = nullptr;
    } else {
        Node<T>* current = s.top;
        Node<T>* last = nullptr;
        while (current != nullptr) {
            Node<T>* temp = new Node<T>;
            temp->data = current->data;
            temp->next = nullptr;

            if (last == nullptr) {
                top = temp;
            } else {
                last->next = temp;
            }

            last = temp;
            current = current->next;
        }
    }

    return *this;
}

template <class T>
bool TStack<T>::isEmpty() const
{
    return top == nullptr;
}

template <class T>
T TStack<T>::pop()
{
    if (isEmpty())
        throw std::out_of_range("Stack is empty");

    Node<T>* temp = top;
    T tempData = top->data;
    top = top->next;
    delete temp;

    return tempData;
}

template <class T>
void TStack<T>::push(T value)
{
    Node<T>* temp = new Node<T>;
    temp->data = value;
    temp->next = top;
    top = temp;
}

template <class T>
T TStack<T>::getTop() const
{
    if (isEmpty())
        throw std::underflow_error("Stack is empty. Cannot retrieve top element.");

    return top->data;
}

template <class T>
void TStack<T>::clear()
{
    while (!isEmpty()) {
        pop();
    }
}

template <class T>
bool TStack<T>::check(std::string str)
{
    TStack<char> s;
    bool res = true;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            s.push('(');
        }
        if (str[i] == ')') {
            if (s.isEmpty()) {
                return false;
            }
            s.pop();
        }
    }
    return true;
}

template <class T>
bool TStack<T>::operator==(const TStack<T>& other) const
{
    Node<T>* currentTop = top;
    Node<T>* otherCurrentTop = other.top;
    while (currentTop != nullptr && otherCurrentTop != nullptr) {
        if (currentTop->data != otherCurrentTop->data) {
            return false;
        }
        currentTop = currentTop->next;
        otherCurrentTop = otherCurrentTop->next;
    }

    if (currentTop == otherCurrentTop) {
        return true;
    }

    return false;
}

template <class T>
bool TStack<T>::operator!=(const TStack<T>& stack) const
{
    return !(*this == stack);
}