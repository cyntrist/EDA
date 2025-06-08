// E25-2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
int acumuladores(bintree<T> const& tree, int& acc) {
    if (tree.empty()) 
        return 0;
    if (tree.right().empty() && tree.left().empty())
    {
        if (tree.root() == 0)
            acc++;
        return tree.root();
    }

    int totalDescendientes = 0;
    if (!tree.left().empty() && tree.right().empty()) // si solo tiene rama izquierda
        totalDescendientes = acumuladores(tree.left(), acc);
    
    if (!tree.right().empty() && tree.left().empty()) // si solo tiene rama derecha
        totalDescendientes = acumuladores(tree.right(), acc);
    
    if (!tree.right().empty() && !tree.left().empty()) // si tiene ambas ramas
    {
        int descIzq = acumuladores(tree.left(), acc);
        int descDer = acumuladores(tree.right(), acc);
        totalDescendientes = descIzq + descDer;
    }

	if (tree.root() == totalDescendientes)
        acc++;
    return totalDescendientes + tree.root();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    int acc = 0;
    acumuladores(tree, acc);
    cout << acc << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}

