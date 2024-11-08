// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;
using Par = std::pair<int, bool>;

Par zurdo(const bintree<char>& arbol)
{
	if (arbol.empty())
		return {0, true};
	if (arbol.left().empty() && arbol.right().empty())
		return {1, true};

	Par iz = zurdo(arbol.left());
	Par der = zurdo(arbol.right());

	if (iz.second && der.second && iz.first > der.first)
		return {iz.first + der.first + 1, true};
	return {iz.first + der.first + 1, false};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	// leer los datos de la entrada
	bintree<char> tree;
	tree = leerArbol('.');
	Par sol = zurdo(tree);
	cout << (sol.second ? "SI" : "NO") << endl;
}

int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
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
