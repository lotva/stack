# Изящный калькулятор с использованием стека

Арифметическое выражение задано строкой. Строка содержит в себе операнды в виде целых и вещественных чисел или переменных.

Операции: сложение, вычитание, умножение, возведение в степень, скобки.

Калькулятор переводит выражение в постфиксную запись и вычисляет выражение.

```cpp
class TStack {
    int maxSize; // Глубина стека
    int topIndex; // Номер текущего элемента / длина стэка
    T* stackArray;
```