// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

// interno
template <class T>
class tree_plus : public bintree<T>
{
	using Link = typename bintree<T>::Link;

public:
	T getMinimo() const
	{
		return getMinimo(this->raiz);
	}

private:
	static T getMinimo(Link raiz)
	{
		return 0;
	}
};

// externo
template <class T>
T elemMinimo(const bintree<T>& tree)
{

}

void resuelveCaso()
{
	tree_plus<int> tree_plus;
	static_cast<bintree<int>>(tree_plus) = leerArbol(-1);
	cout << tree_plus.getMinimo() << "\n";

	/*
	bintree<int> tree;
	tree = leerArbol(-1);
	cout << elemMinimo(tree) << "\n";
	*/
}


int main()
{
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
