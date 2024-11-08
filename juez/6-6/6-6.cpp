// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;
using Par = std::pair<bool, int>;


Par zurdo(const bintree<char>& arbol,  int &nelems)
{
	if (arbol.empty())
		return {true, 0};
	if (arbol.left().empty() && arbol.right().empty())
		return {true, 1};
	if (arbol.left().empty())
	{
		int nelemsright;
		return {false, zurdo(arbol.right(), nelemsright).second + 1};
	}

	if (arbol.right().empty())
	{
		int nelemsleft;
		Par izq = zurdo(arbol.left(), nelemsleft);
		return { izq.first, izq.second + 1} ;
	}

	int nelemsleft, nelemsright;
	Par der = zurdo(arbol.right(), nelemsright);
	Par izq = zurdo(arbol.left(), nelemsleft);

	return {(der.first && izq.first && izq.second > (nelems - 1) / 2), der.second + izq.second + 1};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	// leer los datos de la entrada
	bintree<char> tree;
	tree = leerArbol('.');
	int nelems;
	Par sol = zurdo(tree, nelems);
	cout << (sol.first ? "SI" : "NO") << endl;
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
