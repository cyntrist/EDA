// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

using Heroe = string;
using Villano = string;

class SistemaBatallas
{
private:
	struct infoVillano
	{
		int vida = 0;
		int damg = 0;
		list<pair<string, int>>::iterator it; // puntero a la lista de turnos
	};

	unordered_map<Villano, infoVillano> villanos; // mapa no ordenado con la informacion de todos los villanos

	struct infoHeroe
	{
		int vida = 0;
		map<string, int> ataques; // <nombre ataque, daño ataque>
		// mapa ordenado para que mostrar_ataques no tenga que hacer sort cada vez que es llamado
		list<pair<string, int>>::iterator it; // puntero a la lista de turnos
	};

	unordered_map<Heroe, infoHeroe> heroes; // mapa no ordenado con la informacion de todos los heroes
	list<pair<string, int>> turnos; // cola para saber el orden de los turnos

public:
	// O(1) 
	void aparece_villano(const Villano& v, int puntos, int valor)
	{
		if (villanos.find(v) != villanos.end())
			throw invalid_argument("Personaje ya existente");
		turnos.emplace_back(v, puntos); // se añade su turno a la cola
		villanos[v].vida = puntos;
		villanos[v].damg = valor;
		villanos[v].it = --turnos.end();
	}

	// O(1)
	void aparece_heroe(const Heroe& h, int puntos)
	{
		if (heroes.find(h) != heroes.end())
			throw invalid_argument("Personaje ya existente");
		turnos.emplace_back(h, puntos); // se añade su turno a la cola
		heroes[h].vida = puntos; // el operador [] inserta si no existe
		heroes[h].it = --turnos.end();
	}

	// O(log n) por find
	void aprende_ataque(const Heroe& h, const string& ataque, int valor)
	{
		if (heroes.find(h) == heroes.end()) // O(1)
			throw invalid_argument("Heroe inexistente");

		auto& atqH = heroes[h].ataques; // mapa ordenado de ataques del heroe
		if (atqH.find(ataque) != atqH.end()) // log(n)
			throw invalid_argument("Ataque repetido");

		atqH[ataque] = valor;
	}

	// O(n) siendo n el numero de ataques registrados para el heroe h
	vector<pair<string, int>> mostrar_ataques(const Heroe& h)
	{
		if (heroes.find(h) == heroes.end()) // O(1)
			throw invalid_argument("Heroe inexistente");

		vector<pair<string, int>> res;
		auto ataquesH = heroes[h].ataques; // mapa ordenado

		for (auto& atqH : ataquesH) // recorrer mapa ordenado
			res.emplace_back(atqH.first, atqH.second); // insertar en vector

		return res;
	}

	// O(n) siendo n los elementos de la lista turnos
	vector<pair<string, int>> mostrar_turnos()
	{
		vector<pair<string, int>> res;
		for (auto it : turnos)
			res.emplace_back(it.first, it.second);
		return res;
	}

	// O(1)
	// con el uso de iteradores nos ahorramos bucles de busqueda
	bool villano_ataca(const Villano& v, const Heroe& h)
	{
		const auto villano = villanos.find(v); // O(1)
		if (villano == villanos.end())
			throw invalid_argument("Villano inexistente");

		const auto heroe = heroes.find(h); // O(1)
		if (heroe == heroes.end())
			throw invalid_argument("Heroe inexistente");

		if (v != turnos.front().first)
			// si el nombre del villano no es el primero de la lista de turnos, no es su turno
			throw invalid_argument("No es su turno");

		turnos.pop_front();
		heroe->second.vida -= villano->second.damg; // el heroe h pierde vida segun el daño del villano
		heroe->second.it->second = heroe->second.vida; // se actualiza la vida tambien en la lista de turnos

		turnos.emplace_back(v, villano->second.vida); // pide turno de nuevo
		villano->second.it = --turnos.end();

		if (heroe->second.vida <= 0)
		{
			turnos.erase(heroe->second.it);
			heroes.erase(heroe); // teniendo el iterador ya al heroe, coste constante
			return true;
		}

		return false;
	}

	//  O(log n) siendo n el numero de ataques del heroe h
	bool heroe_ataca(const Heroe& h, const string& ataque, const Villano& v)
	{
		const auto villano = villanos.find(v); // O(1)
		if (villano == villanos.end())
			throw invalid_argument("Villano inexistente");

		const auto heroe = heroes.find(h); // O(1)
		if (heroe == heroes.end())
			throw invalid_argument("Heroe inexistente");

		if (h != turnos.front().first) // si el nombre del heroe no es el primero de la lista de turnos, no es su turno
			throw invalid_argument("No es su turno");

		const auto ataqueHeroe = heroe->second.ataques.find(ataque);
		if (ataqueHeroe == heroe->second.ataques.end()) // si no tiene el ataque aprendido O(log n) porque es ordenado
			throw invalid_argument("Ataque no aprendido");

		turnos.pop_front();
		villano->second.vida -= ataqueHeroe->second; // el villano v pierde vida segun el daño del ataque ataqueHeroe
		villano->second.it->second = villano->second.vida; // se actualiza la vida en la lista de turnos

		turnos.emplace_back(h, heroe->second.vida); // pide turno de nuevo
		heroe->second.it = --turnos.end();

		if (villano->second.vida <= 0)
		{
			// si el villano es completamente derrotado se elimina de la batalla
			turnos.erase(villano->second.it); // se elimina de la lista de turnos
			villanos.erase(villano); // se elimina del diccionario de villanos / teniendo el iterador, coste constante
			return true;
		}

		return false;
	}
};

bool resuelveCaso()
{
	string comando;
	cin >> comando;
	if (!cin) return false;

	SistemaBatallas sistema;
	Villano v;
	Heroe h;
	string ataque;
	int ptos;
	int valor;
	while (comando != "FIN")
	{
		try
		{
			if (comando == "aparece_villano")
			{
				cin >> v >> ptos >> valor;
				sistema.aparece_villano(v, ptos, valor);
			}
			else if (comando == "aparece_heroe")
			{
				cin >> h >> ptos;
				sistema.aparece_heroe(h, ptos);
			}
			else if (comando == "aprende_ataque")
			{
				cin >> h >> ataque >> valor;
				sistema.aprende_ataque(h, ataque, valor);
			}
			else if (comando == "mostrar_ataques")
			{
				cin >> h;
				auto ataques = sistema.mostrar_ataques(h);
				cout << "Ataques de " << h << endl;
				for (auto& [ataque, valor] : ataques)
					cout << ataque << " " << valor << "\n";
			}
			else if (comando == "mostrar_turnos")
			{
				cout << "Turno: " << endl;
				auto turnos = sistema.mostrar_turnos();
				for (auto& [pers, puntos] : turnos)
					cout << pers << " " << puntos << "\n";
			}
			else if (comando == "villano_ataca")
			{
				cin >> v >> h;
				bool derrotado = sistema.villano_ataca(v, h);
				cout << v << " ataca a " << h << endl;
				if (derrotado)
					cout << h << " derrotado" << endl;
			}
			else if (comando == "heroe_ataca")
			{
				cin >> h >> ataque >> v;
				bool derrotado = sistema.heroe_ataca(h, ataque, v);
				cout << h << " ataca a " << v << endl;
				if (derrotado)
					cout << v << " derrotado" << endl;
			}
		}
		catch (std::exception& e)
		{
			cout << "ERROR: " << e.what() << "\n";
		}
		cin >> comando;
	}

	cout << "---\n";
	return true;
}

int main()
{
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso())
	{
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
