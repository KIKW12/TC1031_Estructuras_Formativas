/*
* Nombre: Juan Enrique Ayala Zapata
* Matrícula: A01711235
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include<iostream>
#include<bits/stdc++.h>

class Funciones{
public:

    //Constructor por defecto
    Funciones() {}

    //Funcion iterativa
    int sumaIterativa(int n){
        int sum = 0;

        //Bucle para iterar desde 0 a n, para hacer la suma
        for (int i = 0; i <= n; i++){
        sum += i;
    }
    return sum;
    }

    //Funcion recursiva
    int sumaRecursiva(int n){

        //Caso base: si n == 0, devuelve 0
        if (n == 0){
            return 0;
        }

        //Caso recursivo: si n != 0, devuelve n + la suma de n-1
        else{
            return n + sumaRecursiva(n-1);
        }
    }

    //Funcion de suma directa
    int sumaDirecta(int n){

        //Formula de Gauss para la suma de los primeros n numeros naturales
        return (n*(n+1))/2;
    }

};



#endif