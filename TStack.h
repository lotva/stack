#pragma once

template <class T>
class TStack {
    int maxSize;
    int topIndex;
    T* stackArray;

public:
    TStack(const unsigned int _maxSize = 10);
    ~TStack();
    TStack& operator=(const TStack& stack);
    
    bool isEmpty() const;
    bool isFull() const;

    T pop();
    void push(T value);
    T getTop();

    void clear();
};

template <class T>
TStack<T>::TStack(const unsigned int _maxSize)
{
    if (_maxSize <= 0)
        throw -1;

    maxSize = _maxSize;
    topIndex = -1;
    stackArray = new T[_maxSize];
}

template <class T>
TStack<T>::~TStack()
{
    delete[] stackArray;
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& stack)
{
    if (&stack == this)
        return this;

    topIndex = stack.topIndex;

    if (maxSize == stack.maxSize) {
        for (int i = 0; i < topIndex + 1; i++) {
            stackArray[i] = stack.stackArray[i];
        }
        return *this;
    }

    maxSize = stack.maxSize;
    delete[] stackArray;

    stackArray = new T[maxSize];
    for (int i = 0; i < stack.topIndex + 1; i++) {
        stackArray[i] = stack.stackArray[i];
    }
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
        throw -a;

    T temp = stackArray[topIndex];
    topIndex == topIndex - 1;

    return temp
}

template <class T>
void TStack<T>::push(T value)
{
    if (isFull())
        throw -1;

    topIndex++;
    stackArray[topIndex] = value;
}

template <class T>
T TStack<T>::getTop()
{
    return stackArray[topIndex];
}
