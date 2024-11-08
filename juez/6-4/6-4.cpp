// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;
using Par = std::pair<int, bool>;


bool esPrimo(int num)
{
	if (num < 2)
		return false;
	for (int i = 2; i * i <= num; ++i)
		if (num % i == 0)
			return false;
	return true;
}


// COMPLEJIDAD: O(n m) siendo n el numero de elementos del arbol y m el numero a saber si es primo
template <class T>
void barrera(const bintree<T>& tree, int& num, int profAux, int& profAct, bool& encontrado)
{
	if (tree.empty()) return;
	if (esPrimo(tree.root())) return;

	if (tree.root() % 7 == 0 && (!encontrado || profAux < profAct))
	{
		encontrado = true;
		num = tree.root();
		profAct = profAux;
	}

	if (!encontrado || profAux + 1 < profAct)
	{
		barrera(tree.left(), num, profAux + 1, profAct, encontrado);
		barrera(tree.right(), num, profAux + 1, profAct, encontrado);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
void resuelveCaso()
{
	// leer los datos de la entrada
	bintree<int> tree;
	int num = -1;
	int prof = 1;
	bool encontrado = false;

	tree = leerArbol(-1);
	barrera(tree, num, prof, prof, encontrado);

	if (encontrado) cout << num << " " << prof << endl;
	else cout << "NO HAY" << endl;
}

int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


	int n = 0;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		resuelveCaso();
	}


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}
