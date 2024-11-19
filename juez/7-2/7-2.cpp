// Nombre del alumno ..... Cynthia Tristán y Carmen Gómez
// Usuario del Juez ...... EDA-GDV73 y EDA-GB27

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
using namespace std;

using Diccionario = map<string, int>;

// O(n), siendo n el número de eltos del diccionario 2
void compararDiccionarios(Diccionario& d1, const Diccionario& d2)
{
	set<string> nuevos, quitados, cambios;
	for (auto e = d2.begin(); e != d2.end(); ++e)
	{
		auto it = d1.find(e->first); // busco en d1 la palabra del iterador de d2
		if (it != d1.end())
		{ // si la he encontrado
			if (e->second != it->second) // y son distintas
				cambios.emplace(e->first); // la añado a los cambios
			d1.erase(it); // borro de d1 la palabra
		}
		else nuevos.emplace(e->first);
	}

	for (auto& e : d1)
		quitados.insert(e.first);

	if (!quitados.empty() || !nuevos.empty() || !cambios.empty())
	{
		if (!nuevos.empty())
		{
			cout << "+ ";
			for (const auto& e : nuevos)
				cout << e << " ";
			cout << endl;
		}

		if (!quitados.empty())
		{
			cout << "- ";
			for (const auto& i : quitados)
				cout << i << " ";
			cout << std::endl;
		}

		if (!cambios.empty())
		{
			cout << "* ";
			for (const auto& a : cambios)
				cout << a << " ";
			cout << endl;
		}
	}
	else std::cout << "Sin cambios" << std::endl;
}

void leerDiccionario(Diccionario& diccionario)
{
	char c;
	string clave;
	int valor;
	cin.get(c);
	while (c != '\n')
	{
		cin.unget();
		cin >> clave >> valor;
		diccionario.insert({clave, valor});
		cin.get(c);
	}
}

void resuelveCaso()
{
	Diccionario antiguo;
	Diccionario nuevo;
	leerDiccionario(antiguo);
	leerDiccionario(nuevo);
	compararDiccionarios(antiguo, nuevo);
	cout << "---" << endl;
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
	char c;
	std::cin >> numCasos;
	cin.get(c);
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}
