#include "circulararray.h"
#include <memory>

template <typename T>
class StackArray : public CircularArray<T> {
private:
    unique_ptr<T[]> cA;
    int head, size=0;
public:
    StackArray(T size) : CircularArray<T>(make_unique<T[]>(size)), size(size) {}
    void push (T data) {
        cA[head] = data;
        head = (head+1) % size;
    }
    T pop() {
        head = (head-1+size)%size;
        return cA[head];
    }
};