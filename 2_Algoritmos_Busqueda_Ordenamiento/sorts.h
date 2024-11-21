/*
* Nombre: Juan Enrique Ayala Zapata
* Matricula: A01711235
*/

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
using namespace std;

template <class T>
class Sorts {
private:
    /**
    * Intercambia dos elementos en un vector.
    *
    * @param v: referencia al vector donde se realizará el intercambio.
    * @param i: índice del primer elemento a intercambiar.
    * @param j: índice del segundo elemento a intercambiar.
    */
    void swap(vector<T>& v, int i, int j);

    /**
    * Copia los elementos de un subarreglo de un vector a otro.
    *
    * @param A: referencia al vector de destino.
    * @param B: referencia al vector de origen.
    * @param low: índice inferior del rango a copiar.
    * @param high: índice superior del rango a copiar.
    */
    void copyArray(vector<T>& A, vector<T>& B, int low, int high);

    /**
    * Combina dos subarreglos ordenados en un solo arreglo.
    *
    * @param A: referencia al vector que contiene los subarreglos ordenados.
    * @param B: referencia al vector donde se almacenará la combinación.
    * @param low: índice inferior del primer subarreglo.
    * @param mid: índice superior del primer subarreglo y límite inferior del segundo.
    * @param high: índice superior del segundo subarreglo.
    */
    void mergeArray(vector<T>& A, vector<T>& B, int low, int mid, int high);

    /**
    * Divide un arreglo en subarreglos recursivamente y luego los combina de forma ordenada.
    *
    * @param A: referencia al vector original.
    * @param B: referencia a un vector temporal para almacenar las combinaciones.
    * @param low: índice inferior del rango a dividir.
    * @param high: índice superior del rango a dividir.
    */
    void mergeSplit(vector<T>& A, vector<T>& B, int low, int high);

public:
    /**
    * Ordena un vector utilizando el algoritmo de selección.
    *
    * @param v: referencia al vector a ordenar.
    * @return vector<T>: vector ordenado.
    */
    vector<T> ordenaSeleccion(vector<T>& v);

    /**
    * Ordena un vector utilizando el algoritmo de burbuja.
    *
    * @param v: referencia al vector a ordenar.
    * @return vector<T>: vector ordenado.
    */
    vector<T> ordenaBurbuja(vector<T>& v);

    /**
    * Ordena un vector utilizando el algoritmo de merge sort.
    *
    * @param v: referencia al vector a ordenar.
    * @return vector<T>: vector ordenado.
    */
    vector<T> ordenaMerge(vector<T>& v);

    /**
    * Realiza una búsqueda secuencial en un vector.
    *
    * @param v: referencia constante al vector en el cual se buscará.
    * @param val: valor de tipo T que se desea encontrar.
    * @return int: índice del elemento encontrado o -1 si no se encuentra.
    */
    int busqSecuencial(const vector<T>& v, T val);

    /**
    * Realiza una búsqueda binaria en un vector.
    *
    * @param v: referencia constante al vector en el cual se buscará
    * @param val: valor de tipo T que se desea encontrar.
    * @return int: índice del elemento encontrado o -1 si no se encuentra.
    */
    int busqBinaria(const vector<T>& v, T val);
};

template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j) {
    // Intercambia los elementos v[i] y v[j]
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T> &v) {
    /**
    * Recorre el vector para encontrar el elemento más pequeño y lo intercambia
    * con el elemento en la posición actual (i) en cada iteración
    */ 
    for(int i = 0; i < v.size(); i++){
        int mid = i;

        for(int j = i + 1; j < v.size(); j++){
            // Encuentra el elemento más pequeño en el subarreglo
            if(v[j] < v[mid]){
                mid = j;
            }
        }

        /**
        * Intercambia el elemento más pequeño encontrado con el 
        * elemento en la posición actual (i)
        */
        swap(v, i, mid);
    }
    return v;
}

template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T> &v) {
    /*
    * Recorre el vector varias veces, intercambiando elementos 
    * si están en el orden incorrecto
    */
    for(int i = v.size() - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(v[j] > v[j + 1]){
                // Intercambia elementos si están en el orden incorrecto
                swap(v, j, j + 1);
            }
        }
    }
    return v;
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high){
    // Copia los elementos de B a A desde low hasta high
    for(int i = low; i <= high; i++){
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high){
    // Combina dos subarreglos ordenados (A[low..mid] y A[mid+1..high]) en el arreglo B
    int i = low;     // Índice para el primer subarreglo
    int j = mid + 1; // Índice para el segundo subarreglo
    int k = low;     // Índice para el arreglo combinado

    // Combina los subarreglos en B
    while(i <= mid && j <= high){
        if(A[i] < A[j]){
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    // Copia los elementos restantes del primer subarreglo (si los hay)
    if(i > mid){
        for(; j <= high; j++){
            B[k++] = A[j];
        }
    } else {
        // Copia los elementos restantes del segundo subarreglo (si los hay)
        for(; i <= mid; i++){
            B[k++] = A[i];
        }
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
    // Divide el arreglo recursivamente hasta que los subarreglos tengan un tamaño de 1
    if((high - low) < 1){
        return;
    }

    int mid = (high + low) / 2;
    // Divide el subarreglo izquierdo
    mergeSplit(A, B, low, mid);
    // Divide el subarreglo derecho
    mergeSplit(A, B, mid + 1, high);
    // Combina los subarreglos
    mergeArray(A, B, low, mid, high);
    // Copia el resultado combinado de vuelta a A
    copyArray(A, B, low, high);
}

template <class T>
vector<T> Sorts<T>::ordenaMerge(vector<T> &v) {
    // Inicializa un arreglo temporal y llama a la función recursiva para ordenar
    vector<T> tmp(v.size());
    mergeSplit(v, tmp, 0, v.size() - 1);
    return v;
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &v, T val) {
    // Recorre el vector secuencialmente para buscar el valor val
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == val) {
            return i;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<T> &v, T val) {
    // Realiza una búsqueda binaria en el vector ordenado
    int low = 0;
    int high = v.size() - 1;
    int mid;

    while(low <= high){
        mid = (high + low) / 2;

        if(v[mid] == val){
            return mid;
        } else if(v[mid] > val){
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

#endif // !SORTS_H_
