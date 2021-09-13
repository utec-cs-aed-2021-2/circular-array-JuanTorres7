#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> {
private:
    T* array_q;
    T capacity_q;
    int front, rear, size;

public:
    QueueArray(int _cap) {
        capacity_q = _cap;
        front = size = 0;
        rear = _cap - 1;
        array_q = new T[_cap];
    }
    void enQueue(int data);
    T deQueue();
};

template <typename T>
void QueueArray<T>::enQueue(int data) {
    rear = (rear+1) % capacity_q;
    array_q[rear] = data;
    size++;
}

template <typename T>
T QueueArray<T>::deQueue() {
    T out = array_q[front];
    front = (front+1) % capacity_q;
    size--;
    return out;
}