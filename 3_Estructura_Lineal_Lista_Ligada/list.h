/**
 * Nombre: Juan Enrique Ayala Zapata
 * Matricula: A01711235
 */


#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <string>
#include <sstream>

template <class T>
class List {
private:
    struct Link {
        T value;
        Link* next;
        Link(T val, Link* nxt = nullptr) : value(val), next(nxt) {}
    };
    
    Link* head;
    int size;

public:
    List() : head(nullptr), size(0) {}
    ~List();
    
    void insertion(T value);
    int search(T value) const;
    void update(int index, T value);
    void deleteAt(int index);
    std::string toString() const;
};

template <class T>
List<T>::~List() {
    Link* current = head;
    while (current != nullptr) {
        Link* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

template <class T>
void List<T>::insertion(T value) {
    if (head == nullptr) {
        head = new Link(value);
    } else {
        Link* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Link(value);
    }
    size++;
}

template <class T>
int List<T>::search(T value) const {
    Link* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;  // Return -1 if value is not found
}

template <class T>
void List<T>::update(int index, T value) {
    if (index < 0 || index >= size) return;  // Check for valid index
    Link* current = head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }
    current->value = value;
}

template <class T>
void List<T>::deleteAt(int index) {
    if (index < 0 || index >= size) return;  // Check for valid index

    Link* current = head;
    if (index == 0) {
        head = head->next;
        delete current;
    } else {
        Link* prev = nullptr;
        int i = 0;
        while (i < index) {
            prev = current;
            current = current->next;
            i++;
        }
        prev->next = current->next;
        delete current;
    }
    size--;
}

template <class T>
std::string List<T>::toString() const {
    std::stringstream aux;
    Link* current = head;

    aux << "[";
    while (current != nullptr) {
        aux << current->value;
        if (current->next != nullptr) {
            aux << ", ";
        }
        current = current->next;
    }
    aux << "]";
    return aux.str();
}

#endif  // LIST_H_
