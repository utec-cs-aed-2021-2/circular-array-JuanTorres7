#include "circulararray.h"
#include <memory>

template <typename T>
class StackArray : public CircularArray<T> {
private:
    T *array_s;
    T capacity_s;
    T top;
public:
    StackArray(int _size) {
        array_s = new T[_size];
        capacity_s = _size;
        top = -1;
    }
    void push (T data);
    T pop ();
    bool isEmpty();
    bool isFull();
};

template <typename T>
void StackArray<T>::push(T data) {
    array_s[++top] = data;
}

template <typename T>
T StackArray<T>::pop() {
    return array_s[top--];
}

template <typename T>
bool StackArray<T>::isEmpty() {
    return top == -1;
}

template <typename T>
bool StackArray<T>::isFull() {
    return top == capacity_s-1;
}