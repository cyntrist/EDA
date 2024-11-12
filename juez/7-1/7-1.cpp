#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
using namespace std;

using TablaRefs = map<string, list<int>>;

void referencias(int numLineas, TablaRefs& refs)
{
	string palabra;
	char c;
	for (int numLinea = 1; numLinea <= numLineas; numLinea++)
	{
		cin.get(c);
		while (c != '\n')
		{
			cin.unget(); // Se vuelve a dejar c en cin (por si era la 1ª letra de la linea)
			cin >> palabra;

			///
			if (palabra.size() > 2)
			{
				for (auto& c : palabra)
					c = tolower(c);

				if (!refs.count(palabra))
				{
					list<int> l;
					l.push_back(numLinea);
					refs.insert({palabra, l});
				}
				else if (refs[palabra].back() != numLinea)
					refs[palabra].push_back(numLinea);
			}
			///
			
			cin.get(c);
		}
	}
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada
	int n;
	char c;
	cin >> n;
	cin.get(c); // Me salto el \n de detrás del N
	if (n == 0)
		return false;

	TablaRefs refs;
	referencias(n, refs);

	for (const auto& par : refs)
	{
		cout << par.first << " ";

		for (const auto l : par.second)
			cout << l << " ";

		cout << "\n";
	}

	cout << "---\n";
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
#endif

	return 0;
}
