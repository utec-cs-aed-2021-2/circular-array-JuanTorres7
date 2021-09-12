#include <iostream>
#include <vector>
using namespace std;

void merge (int *array, int ini, int mid, int fin) {
    int i, j, k;
    int elementosIzq = mid-ini+1;
    int elementosDer = fin-mid;
    vector<int>v_izq (elementosIzq);
    vector<int>v_der (elementosDer);
    for (int i=0; i<elementosIzq; i++) v_izq[i] = array[ini+i];
    for (int j=0; j<elementosDer; j++) v_der[j] = array[mid+1+j];

    i = 0; j = 0;
    k = ini;
    int *i_ptr = &i; int *j_ptr = &j;
    int *k_ptr = &k;

    while (*i_ptr < elementosIzq && *j_ptr < elementosDer) {
        if (v_izq[*i_ptr] <= v_der[*j_ptr]) {
            array[*k_ptr] = v_izq[*i_ptr];
            ++*i_ptr;
        }
        else {
            array[*k_ptr] = v_der[*j_ptr];
            ++*j_ptr;
        }
        ++*k_ptr;
    }
    while (*j_ptr < elementosDer) {
        array[*k_ptr] = v_der[*j_ptr];
        ++*j_ptr;
        ++*k_ptr;
    }
    while (*i_ptr < elementosIzq) {
        array[*k_ptr] = v_izq[*i_ptr];
        ++*i_ptr;
        ++*k_ptr;
    }
}

void merge_sort (int *array, int ini, int fin) {
    if (ini < fin) {
        int mid = ini + (fin-ini)/2;
        merge_sort(array, ini, mid);
        merge_sort(array, mid+1, fin);
        merge(array, ini, mid, fin);
    }
}

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <typename T>
void CircularArray<T>::push_front(T data) {
    if (front == -1) {
        front = back = 0;
        array[front] = data;
    }
    else if (front == 0) {
        front = capacity-1;
        array[front] = data;
    }
    else {
        front = front-1;
        array[front] = data;
    }
}

template <typename T>
void CircularArray<T>::push_back(T data) {
    if (front == -1) {
        front = back = 0;
        array[back] = data;
    }
    else if (back == capacity-1 && front != 0) {
        back = 0;
        array[back] = data;
    }
    else {
        back = back+1;
        array[back] = data;
    }
}

template <typename T>
void CircularArray<T>::insert(T data, int pos) {
    capacity++;
    for(int i=capacity; i >= pos; i--) {
        array[i] = array[i-1];
    }
    array[pos-1] = data;
}

template <typename T>
T CircularArray<T>::pop_front() {
    if (front == back) {
        front = back = -1;
    }
    else {
        if (front == capacity-1) {front = 0;}
        else {front++;}
    }
}

template <typename T>
T CircularArray<T>::pop_back() {
    if (front == back) {
        front = back = -1;
    }
    else if (back == 0) back = capacity-1;
    else back = back-1;
}

template <class T>
bool CircularArray<T>::is_full() {
    return ((front==0 && back == capacity-1)||front == back+1);
}

template <class T>
bool CircularArray<T>::is_empty() {
    return (front == -1);
}

template <class T>
int CircularArray<T>::size() {
    return capacity;
}

template <typename T>
T &CircularArray<T>::operator[](int pos) {
    return array[pos];
}

template <typename T>
void CircularArray<T>::sort() {
    front = capacity;
    back = front-1;

    int array1[capacity];
    for (int i=0; i<capacity; i++) array1[i] = array[i];

    merge_sort(array1, 0, capacity-1);
    for (int i=0; i<capacity; i++) array[i] = array1[i];
}

template <typename T>
bool CircularArray<T>::is_sorted() {
    if (capacity == 1 || capacity == 0) return 1;
    for (int i=1; i<capacity; i++) if (array[i-1] > array[i]) {return false;}
    return true;
}

template <typename T>
void CircularArray<T>::reverse() {
    int start = 0;
    int end = capacity-1;
    while (start < end) {
        int temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}

/*
template<typename T>
string CircularArray<T>::to_string(string sep) {
    string out;
    if (back >= front) {
        for (int i= front; i<=back; i++) out += std::__cxx11::to_string(array[i]) + sep;
    }
    else {
        for (int i=front; i<capacity; i++) out += std::__cxx11::to_string(array[i]) + sep;
        for (int i=0; i<=back; i++) out += std::__cxx11::to_string(array[i]) + sep;
    }
    return out;
}
*/

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;
}
