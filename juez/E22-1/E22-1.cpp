#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;

void adelantar(list<char>& l, int pos, int lon, int k)
{
	if (l.empty()
		|| k == 0
		|| lon == 0
		|| k > pos
		|| k >= l.size()
		|| pos >= l.size()
		|| pos - k < 0)
		return;

	if (pos + lon > l.size())
		lon = l.size() - pos;

	auto sigDest = l.begin();
	int i = 0;
	while (sigDest != l.end() && i < pos - k)
	{
		++sigDest;
		i++;
	}

	auto j = sigDest;
	while (j != l.end() && i < l.size())
	{
		if (i < pos || i >= pos + lon) // si no esta dentro del segmento 
		{
			l.push_back(*j);
			j = l.erase(j);
		}
		else ++j;
		
		i++;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	char e;
	int n, pos, lon, k;
	list<char> l;

	// leer los datos de la entrada
	cin >> n >> pos >> lon >> k;
	for (int i = 1; i <= n; ++i)
	{
		cin >> e;
		l.push_back(e);
	}

	//l.adelantar(pos, lon, k);
	adelantar(l, pos, lon, k);

	// Le damos una vuelta para comprobar que la lista está bien formada
	for (int i = 0; i < l.size(); ++i)
	{
		e = l.back();
		l.pop_back();
		l.push_front(e);
	}

	// Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
	while (!l.empty())
	{
		cout << l.front() << " ";
		l.pop_front();
	}
	cout << endl;
}

//#define DOMJUDGE
int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("input.txt");
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
