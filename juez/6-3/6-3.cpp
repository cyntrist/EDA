// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"
using namespace std;


template <class T>
T minimo(const bintree<T>& tree)
{
	T min = tree.root();
	if (tree.left().empty() && tree.right().empty()) 
		return min;
	if (tree.left().empty())
		if (min > minimo(tree.right())) 
			min = tree.right().root();
	if (tree.right().empty())
		if (min > minimo(tree.left())) 
			min = tree.left().root();
	return min;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada
	char tipo;
	cin >> tipo;
	if (!cin) return false;
	if (tipo == 'N')
	{
		bintree<int> tree = leerArbol(-1);
		cout << minimo(tree) << endl;
	}
	else if (tipo == 'P')
	{
		bintree<string> tree = leerArbol(string("#"));
		cout << minimo(tree) << endl;
	}
	return true;
}

int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}
