#pragma once

#include <iostream>
#include <string>

template <class T>
class TStack {
    int maxSize;
    int topIndex;
    T* stackArray;

public:
    TStack(int _maxSize = 10);
    ~TStack();
    TStack(const TStack&);

    bool isEmpty() const;
    bool isFull() const;

    TStack& operator=(const TStack&);
    bool operator==(const TStack<T>&) const;
    bool operator!=(const TStack<T>&) const;

    void push(T value);
    T pop();
    T top() const;
    void clear();

    int getCurrentSize();

    friend std::istream& operator>>(std::istream& in, TStack& s)
    {
        T value;

        std::cout << "Введите элементы стека (введите 0 для завершения): ";
        while (in >> value && value != 0) {
            s.push(value);
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const TStack& s)
    {
        for (int i = 0; i <= s.topIndex; i++) {
            out << s.stackArray[i] << " ";
        }
        return out;
    }
};

template <class T>
TStack<T>::TStack(int _maxSize)
{
    if (_maxSize <= 0)
        throw std::exception("Negative size.");

    maxSize = _maxSize;
    topIndex = -1;
    stackArray = new T[_maxSize];
}

template <class T>
TStack<T>::~TStack()
{
    delete[] stackArray;
    stackArray = nullptr;
}

template <class T>
TStack<T>::TStack(const TStack<T>& st)
{
    maxSize = st.maxSize;
    topIndex = st.topIndex;
    stackArray = new T[maxSize];

    for (int i = 0; i <= topIndex; i++) {
        stackArray[i] = st.stackArray[i];
    }
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& stack)
{
    std::swap(maxSize, stack.maxSize);
    std::swap(topIndex, stack.topIndex);
    std::swap(stackArray, stack.stackArray);
    return *this;
}

template <class T>
bool TStack<T>::isEmpty() const
{
    return topIndex == -1;
}

template <class T>
bool TStack<T>::isFull() const
{
    return topIndex + 1 == maxSize;
}

template <class T>
T TStack<T>::pop()
{
    if (isEmpty())
        throw std::exception("Stack is empty.");

    T temp = stackArray[topIndex];
    topIndex--;

    return temp;
}

template <class T>
void TStack<T>::push(T value)
{
    if (isFull())
        throw std::exception("Stack is full");

    topIndex++;
    stackArray[topIndex] = value;
}

template <class T>
T TStack<T>::top() const
{
    if (isEmpty())
        throw std::underflow_error("Stack is empty. Cannot retrieve top element.");

    return stackArray[topIndex];
}

template <class T>
void TStack<T>::clear()
{
    topIndex = -1;
}

template <class T>
int TStack<T>::getCurrentSize()
{
    return topIndex;
}

template <class T>
bool TStack<T>::operator==(const TStack<T>& st) const
{
    if (topIndex != st.topIndex) {
        return false;
    }

    for (int i = 0; i <= topIndex; i++) {
        if (stackArray[i] != st.stackArray[i])
            return false;
    }

    return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack<T>& st) const
{
    return !(*this == st);
}