/**
 * Nombre: Juan Enrique Ayala Zapata
 * Matricula: A01711235
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>

template <class T>
class Heap {
private:
    T *data;
    unsigned int count;
    unsigned int capacity;
    unsigned int parent(unsigned int) const;
    unsigned int left(unsigned int) const;
    unsigned int right(unsigned int) const;
    void heapify(unsigned int);
    void swap(unsigned int, unsigned int);

public:
    Heap(unsigned int);
    ~Heap();
    bool empty() const;
    unsigned int size() const;
    void push(T value);
    void pop();
    T top() const;
    bool full() const;
    void add(T);
    T remove();
    void clear();
    std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int cap) : capacity(cap), count(0) {
    data = new T[capacity];
    if (data == nullptr) {
        throw std::runtime_error("Out of memory");
    }
}

template <class T>
Heap<T>::~Heap() {
    delete[] data;
    data = nullptr;
    capacity = 0;
    count = 0;
}

template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

template <class T>
unsigned int Heap<T>::size() const {
    return count;
}

template <class T>
void Heap<T>::push(T value) {
    if (count < capacity) {
        data[count] = value;
        count++;
        unsigned int pos = count - 1;
        while (pos > 0 && data[pos] < data[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    } else {
        throw std::overflow_error("Heap is full");
    }
}

template <class T>
void Heap<T>::pop() {
    if (count > 0) {
        data[0] = data[count - 1];
        count--;
        heapify(0);
    } else {
        throw std::underflow_error("Heap is empty");
    }
}

template <class T>
T Heap<T>::top() const {
    if (count > 0) {
        return data[0];
    }
    throw std::underflow_error("Heap is empty");
}

template <class T>
bool Heap<T>::full() const {
    return (count == capacity);
}

template <class T>
void Heap<T>::add(T val) {
    push(val);
}

template <class T>
T Heap<T>::remove() {
    T topValue = top();
    pop();
    return topValue;
}

template <class T>
void Heap<T>::clear() {
    count = 0;
}

template <class T>
std::string Heap<T>::toString() const {
    std::stringstream aux;
    aux << "[";
    for (unsigned int i = 0; i < count; i++) {
        if (i != 0) {
            aux << " ";
        }
        aux << data[i];
    }
    aux << "]";
    return aux.str();
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    return (2 * pos) + 1;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    return (2 * pos) + 2;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int le = left(pos);
    unsigned int ri = right(pos);
    unsigned int min = pos;
    if (le < count && data[le] < data[min]) {
        min = le;
    }
    if (ri < count && data[ri] < data[min]) {
        min = ri;
    }
    if (min != pos) {
        swap(pos, min);
        heapify(min);
    }
}

#endif // HEAP_H_