/**
 * Nombre: Juan Enrique Ayala Zapata
 * Matricula: A01711235
 */

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
    unsigned int size;
    unsigned int count;
    
    Key *keys;
    Value *values;
    Key initialValue;
    unsigned int (*func)(const Key);

    long indexOf(const Key) const;

public:
    Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
    ~Quadratic();
    bool full() const;
    void put(Key, Value);
    Value get(const Key);
    void clear();
    std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f)(const Key)) {
    size = sze;
    initialValue = init;
    count = 0;
    func = f;
    
    keys = new Key[size];
    values = new Value[size];
    
    for (unsigned int i = 0; i < size; i++) {
        keys[i] = initialValue;
    }
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
    delete [] keys;
    delete [] values;
    keys = NULL;
    values = NULL;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
    return (count >= size);
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
    unsigned int i, start;
    
    start = func(k) % size;
    
    for (i = 0; i < size; i++) {
        unsigned int probe = (start + i * i) % size;
        if (keys[probe] == k) {
            return probe;
        }
        if (keys[probe] == initialValue) {
            return -1;
        }
    }
    return -1;
}

template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v) {
    unsigned int i, start;
    
    if (full()) {
        return;
    }
    
    start = func(k) % size;
    
    for (i = 0; i < size; i++) {
        unsigned int probe = (start + i * i) % size;
        if (keys[probe] == initialValue || keys[probe] == k) {
            if (keys[probe] == initialValue) {
                count++;
            }
            keys[probe] = k;
            values[probe] = v;
            return;
        }
    }
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
    long pos = indexOf(k);
    if (pos != -1) {
        return values[pos];
    }
    return Value();
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
    count = 0;
    for (unsigned int i = 0; i < size; i++) {
        keys[i] = initialValue;
    }
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
    std::stringstream aux;
    for (unsigned int i = 0; i < size; i++) {
        if (keys[i] != initialValue) {
            aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
        }
    }
    return aux.str();
}

#endif