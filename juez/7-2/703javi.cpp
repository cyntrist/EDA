#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

using Clave = string;
using Apariciones = int;
using Diccionario = map<Clave, Apariciones>;

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

void comparaDiccionarios(Diccionario& antiguo, Diccionario& nuevo, vector<string>& nuevas, vector<string>& eliminadas, vector<string>& modificadas) {
	//Se han quitado si el valor en antiguo es el mismo que el resultante

	for (auto a : nuevo) {
		//Si no encontramos la clave en el antiguo, significa que la clave es nueva
		if (antiguo.count(a.first) == 0)
			nuevas.push_back(a.first);
		//Se ha modificado si al restar los dos valores no da 0
		else if (antiguo[a.first] - nuevo[a.first] != 0) {
			modificadas.push_back(a.first);
		}
	}
	for (auto a : antiguo) {
		//Si no encontramos la clave en el nuevo, significa que la clave se ha eliminado
		if (nuevo.count(a.first) == 0)
			eliminadas.push_back(a.first);
	}
}

void resuelveCaso() {
	Diccionario antiguo;
	Diccionario nuevo;
	leerDiccionario(antiguo);
	leerDiccionario(nuevo);
	//Creamos vectores de strings para almacenar las claves
	std::vector<string> nuevas;
	std::vector<string> eliminadas;
	std::vector<string> modificadas;

	comparaDiccionarios(antiguo, nuevo, nuevas, eliminadas, modificadas);

	//Imprimimos la solucion
	if (nuevas.size() == 0 && eliminadas.size() == 0 && modificadas.size() == 0) {
		std::cout << "Sin cambios\n";
	}
	else {
		if (nuevas.size() != 0) {
			std::cout << "+";
			for (int i = 0; i < nuevas.size(); i++) {
				std::cout << " " << nuevas.at(i);
			}
			std::cout << "\n";
		}
		if (eliminadas.size() != 0) {
			std::cout << "-";
			for (int i = 0; i < eliminadas.size(); i++) {
				std::cout << " " << eliminadas.at(i);
			}
			std::cout << "\n";
		}
		if (modificadas.size() != 0) {
			std::cout << "*";
			for (int i = 0; i < modificadas.size(); i++) {
				std::cout << " " << modificadas.at(i);
			}
			std::cout << "\n";
		}
	}
	std::cout << "---\n";
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
