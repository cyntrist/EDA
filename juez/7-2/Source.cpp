#include <iostream>
#include <fstream>
#include <string>
#include<map>
#include <iomanip>
#include<set>
using namespace std;
using Diccionario = map<string, int>;

void leerDiccionario(Diccionario& diccionario) {
	char c;
	string clave;
	int valor;
	cin.get(c);
	while (c != '\n') {
		cin.unget();
		cin >> clave >> valor;
		diccionario[clave] = valor;
		cin.get(c);
	}
}

void resuelveCaso() {
	Diccionario antiguo, nuevo;
	leerDiccionario(antiguo);
	leerDiccionario(nuevo);
	set<string>nuevasclaves, desaparecido, modificadas;
	map<string, int>::iterator il = antiguo.begin();
	while (il != antiguo.end()) {
		map<string, int>::iterator  s = nuevo.find(il->first);
		if (s != nuevo.end()) {
			if (il->second != s->second) {
				modificadas.insert(il->first);
				s = nuevo.erase(s);
			}
			else {
				s = nuevo.erase(s);
			}
		}
		else {
			desaparecido.insert(il->first);
		}
		++il;
	}
	map<string, int>::iterator it = nuevo.begin();
	while (it != nuevo.end()) {
		nuevasclaves.insert(it->first);
		++it;
	}

	if (!nuevasclaves.size() && !desaparecido.size() && !modificadas.size() )cout << "Sin cambios" << endl;
	else {

		if (nuevasclaves.size() > 0) {
			cout << "+ ";
			for (set<string>::iterator il = nuevasclaves.begin(); il != nuevasclaves.end(); ++il) {
				cout << *il << " ";
			}
			cout << endl;
		}
		if (desaparecido.size() > 0) {
			cout << "- ";
			for (set<string>::iterator il = desaparecido.begin(); il != desaparecido.end(); ++il) {
				cout << *il << " ";
			}
			cout << endl;
		}
		if (modificadas.size() > 0) {
			cout << "* ";
			for (set<string>::iterator il = modificadas.begin(); il != modificadas.end(); ++il) {
				cout << *il << " ";
			}
			cout << endl;
		}
	}

	cout << "---" << endl;
}


int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	int numCasos; char c;
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
