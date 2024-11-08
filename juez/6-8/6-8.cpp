// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <fstream>
#include <iostream>
#include "bintree_eda.h"

using namespace std;
using Par = pair<int, int>; // altura, diametro

template <typename T>
class bintree_plus : public bintree<T>
{
	using Link = typename bintree<T>::Link;

public:
	bintree_plus() : bintree<T>()
	{
	}

	bintree_plus(const bintree_plus<T>& l, const T& e, const bintree_plus<T>& r)
		: bintree<T>(l, e, r)
	{
	}

	int diametro()
	{
		Par sol = diametro(this->raiz);
		return sol.second;
	}

private:
	Par diametro(Link r)
	{
		if (r == nullptr)
			return {0, 0};

		Par izq = diametro(r->left);
		Par der = diametro(r->right);

		return
		{
			std::max(izq.first, der.first) + 1,
			max(max(izq.second, der.second),
			    izq.first + der.first + 1)
		};
	}
};

template <typename T>
bintree_plus<T> leerArbol_plus(T vacio)
{
	T raiz;
	cin >> raiz;
	if (raiz == vacio)
		return {};
	auto iz = leerArbol_plus(vacio);
	auto dr = leerArbol_plus(vacio);
	return {iz, raiz, dr};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	bintree_plus<char> tree;

	// Leer los datos de la entrada
	tree = leerArbol_plus('.');

	cout << tree.diametro() << endl;
}

int main()
{
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
