#include <iostream>
#include <stdexcept>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

/*
Debemos simular un sistema de batallas por turnos entre héroes y villanos para un video-
juego. Cuando un héroe o un villano aparecen en la batalla, tienen que esperar a que todos los
personajes que estuvieran presentes anteriormente en la batalla ataquen. El personaje al que le
toca el turno, ya sea héroe o villano, realiza un ataque y vuelve a esperar su turno para volver a
atacar. Si el ataque derrota al adversario, éste desaparece de￿nitivamente de la batalla. Los villa-
nos tienen un nombre, una determinada cantidad de puntos de vida y un valor de dano al atacar.
Los héroes, por otro lado, además de su nombre y sus puntos de vida, tienen una lista de ataques
que van aprendiendo a lo largo de la batalla, cada uno con su valor de dano correspondiente. El
nombre de cada personaje es único, es decir, no puede existir un villano y un héroe con el mismo
nombre.
*/

using HeroeNombre = string;
using VillanoNombre = string;

using Nombre = string;
using Vida = int;
using Dano = int;
using Ataque = string;
using Ataques = map<Ataque, Dano>;
using Contador = int;
using Vivo = bool;

struct Entidad
{
	Nombre nombre;
	Vida vida;
	Vivo vivo = true;
};

struct Heroe : Entidad
{
	Ataques ataques;
};

struct Villano : Entidad
{
	Dano dano;
};

using Heroes = std::map<string, Heroe>;
using Villanos = std::map<string, Villano>;
using Turnos = queue<Entidad>;

class SistemaBatallas
{
	Heroes heroes;
	Villanos villanos;
	Contador entidades = 0;
	Turnos turnos;

public:
	// Registra el nuevo villano v en la batalla con s puntos de vida y valor
	// de ataque a. Si el villano no había aparecido en la batalla, se registra.
	// Si el personaje ya había aparecido anteriormente en la batalla, se lanza
	// una excepción del tipo invalid_argument con el mensaje Personaje ya existente.
	// Coste: O(log n) 
	void aparece_villano(VillanoNombre const& v, int puntos, int valor)
	{
		const auto search = villanos.find(v);
		const auto search2 = heroes.find(v);
		if (search != villanos.end() && search->second.vivo
			|| search2 != heroes.end() && search2->second.vivo)
			throw invalid_argument("Personaje ya existente");

		entidades++;
		Villano villano;
		villano.nombre = v;
		villano.vida = puntos;
		villano.dano = valor;
		villanos[v] = villano;
		turnos.push(villano);
	}

	// Registra el nuevo héroe h en la batalla con s puntos de vida. Si el héroe
	// no había aparecido en la batalla, se registra. Si el personaje ya había aparecido
	// anteriormente en la batalla, se lanza una excepción del tipo invalid_argument
	// con el mensaje Personaje ya existente.
	// Coste: O(log n)
	void aparece_heroe(HeroeNombre const& h, int puntos)
	{
		const auto search = heroes.find(h);
		const auto search2 = villanos.find(h);
		if (search != heroes.end() && search->second.vivo
			|| search2 != villanos.end() && search2->second.vivo)
			throw invalid_argument("Personaje ya existente");

		entidades++;
		Heroe heroe;
		heroe.nombre = h;
		heroe.vida = puntos;

		heroes[h] = heroe;
		//if (heroes.count(h) > 0)
		//	heroes.erase(h);
		//heroes.insert({h, heroe});
		turnos.push(heroe);
	}

	//  Añade el ataque a con dano v a la lista de ataques del héroe h.
	//  Si el héroe no está en la batalla, se lanza una excepción del tipo invalid_argument con el mensaje Heroe inexistente.
	//  Si el héroe conoce ya ese ataque, se lanza una excepción del tipo invalid_argument con el mensaje Ataque repetido.
	// Coste: O(log n)
	void aprende_ataque(HeroeNombre const& h, string const& ataque, int valor)
	{
		const auto heroSearch = heroes.find(h);
		if (heroSearch == heroes.end())
			throw invalid_argument("Heroe inexistente");

		const auto attackSearch = heroSearch->second.ataques.find(ataque);
		if (attackSearch != heroSearch->second.ataques.end())
			throw invalid_argument("Ataque repetido");

		heroSearch->second.ataques.insert({ataque, valor});
	}

	// Devuelve un vector de pares (nombre, dano) ordenadados lexicográ￿cament con aquellos ataques aprendidos por el héroe h.
	// Si el héroe no está registrado, se lanza una excepción del tipo invalid_argument con el mensaje Heroe inexistente.
	// Coste: O(n)
	vector<pair<string, int>> mostrar_ataques(HeroeNombre const& h)
	{
		const auto heroSearch = heroes.find(h);
		if (heroSearch == heroes.end())
			throw invalid_argument("Heroe inexistente");

		auto it = heroSearch->second.ataques.begin();
		vector<pair<string, int>> res;

		while (it != heroSearch->second.ataques.end())
		{
			res.emplace_back(it->first, it->second);
			++it;
		}

		return res;
	}

	//  Devuelve un vector de pares con el nombre de todos los héroes y villanos
	//  acompañados de su cantidad correspondiente de puntos de vida, ordenados según su turno.
	//  Coste:
	vector<pair<string, int>> mostrar_turnos()
	{
		vector<pair<string, int>> res;
		Turnos aux = turnos;
		size_t size = aux.size();

		//res.reserve(entidades);
		for (int i = 0; i < size; i++)
		{
			auto villSearch = villanos.find(aux.front().nombre);
			if (villSearch != villanos.end() && aux.front().vivo)
			{
				aux.front().vida = villSearch->second.vida; // actualiza la cola con su vida
				aux.front().vivo = villSearch->second.vivo;
			}

			auto heroSearch = heroes.find(aux.front().nombre);
			if (heroSearch != heroes.end() && aux.front().vivo)
			{
				aux.front().vida = heroSearch->second.vida; // actualiza la cola con su vida
				aux.front().vivo = heroSearch->second.vivo;
			}

			if (aux.front().vivo)
				res.emplace_back(aux.front().nombre, aux.front().vida);
			aux.pop();
		}

		return res;
	}

	//  El villano v ataca al héroe h, restándole a los puntos de vida del héroe el valor de dano de v.
	//  Tras el ataque, v vuelve a pedir turno cuando corresponda.
	//  Si el villano o el héroe no están registrados, se lanza una excepción con el mensaje Villano inexistente
	//  y Heroe inexistente, respectivamente.
	//  Si no es el turno del villano pasado como parámetro, se lanza una excepción con el mensaje No es su turno.
	//  Si el héroe atacado es derrotado, es decir, pierde todos sus puntos de vida, desaparece completamente
	//  de la batalla y la función devuelve el valor cierto.
	// Coste:
	bool villano_ataca(VillanoNombre const& v, HeroeNombre const& h)
	{
		const auto actualSearch = villanos.find(turnos.front().nombre);
		if (actualSearch != villanos.end())
		{
			turnos.front().vida = actualSearch->second.vida; // actualiza la cola con su vida
			turnos.front().vivo = actualSearch->second.vivo;
			if (!turnos.front().vivo)
				turnos.pop();
		}

		// Si el villano o el héroe no están registrados, se lanza una excepción con el mensaje
		// Villano inexistente y Heroe inexistente, respectivamente.
		const auto villSearch = villanos.find(v);
		if (villSearch == villanos.end())
			throw invalid_argument("Villano inexistente");

		const auto heroSearch = heroes.find(h);
		if (heroSearch == heroes.end())
			throw invalid_argument("Heroe inexistente");

		//  Si no es el turno del villano pasado como parámetro, se lanza una excepción con el mensaje No es su turno.
		if (turnos.front().nombre != villSearch->first)
			throw invalid_argument("No es su turno");

		// Ambos tienen que estar vivos
		// Si el héroe atacado es derrotado, es decir, pierde todos sus puntos de vida, desaparece completament
		// de la batalla y la función devuelve el valor cierto.
		bool derrotado = false;

		if (villSearch->second.vivo) // si el villano esta vivo
		{
			turnos.front().vida = villSearch->second.vida; // actualiza la cola con su vida
			turnos.front().vivo = villSearch->second.vivo;

			if (heroSearch->second.vivo) // si el heroe esta vivo
			{
				/// ataque!!!!!!!!!!!!!!!
				heroSearch->second.vida -= villSearch->second.dano;
				if (heroSearch->second.vida <= 0) // si muerte por el ataque
				{
					heroSearch->second.vivo = false;
					//heroes.erase(heroSearch);
					derrotado = true;
				}
			}
			else derrotado = true; // si el heroe esta muerto cuenta como derrota
		}
		else // si el villano no esta vivo se saca de la cola definitivamente y se devuelve false
		{
			turnos.pop(); // se elimina de la cola
			return derrotado;
		}

		turnos.push(villSearch->second); // se vuelve a poner al final de la cola
		turnos.pop(); // se acaba su turno
		return derrotado;
	}

	//  El héroe h ataca al villano v, restándole a los puntos de vida del villano el valor de dano del ataque a.
	//  Tras el ataque, h vuelve a pedir turno cuando corresponda.
	//  Si el villano o el héroe no están registrados, se lanza una excepción con el mensaje Villano inexistente y Heroe inexistente, respectivamente.
	//  Si no es el turno del héroe pasado como parámetro, se lanza una excepción con el mensaje No es su turno.
	//  Si el héroe h no conoce el ataque a, se lanza una excepción con el mensaje Ataque no aprendido.
	//  Si el villano atacado es derrotado, desaparece completamente de la batalla y la función devuelve el valor cierto.
	// Coste:
	bool heroe_ataca(HeroeNombre const& h, string const& ataque, VillanoNombre const& v)
	{
		const auto actualSearch = heroes.find(turnos.front().nombre);
		if (actualSearch != heroes.end())
		{
			turnos.front().vida = actualSearch->second.vida; // actualiza la cola con su vida
			turnos.front().vivo = actualSearch->second.vivo;
			if (!turnos.front().vivo)
				turnos.pop();
		}

		const auto villSearch = villanos.find(v);
		if (villSearch == villanos.end())
			throw invalid_argument("Villano inexistente");

		const auto heroSearch = heroes.find(h);
		if (heroSearch == heroes.end() || !heroSearch->second.vivo)
			throw invalid_argument("Heroe inexistente");

		if (turnos.front().nombre != heroSearch->first)
			throw invalid_argument("No es su turno");

		// Ambos tienen que estar vivos
		//  El héroe h ataca al villano v, restándole a los puntos de vida del villano el valor de dano del ataque a.
		//  Tras el ataque, h vuelve a pedir turno cuando corresponda.
		//	Si el villano atacado es derrotado, desaparece completamente de la batalla y la función devuelve el valor cierto.
		bool derrotado = false;

		if (heroSearch->second.vivo) // si el heroe esta vivo
		{
			turnos.front().vida = heroSearch->second.vida; // actualiza la cola con su vida
			turnos.front().vivo = heroSearch->second.vivo; // actualiza la cola con su vida

			if (villSearch->second.vivo) // si el villano esta vivo
			{
				/// ataque!!!!!!!!!!!!!!!
				const auto attSearch = heroSearch->second.ataques.find(ataque);
				if (attSearch == heroSearch->second.ataques.end())
					throw invalid_argument("Ataque no aprendido");

				villSearch->second.vida -= attSearch->second;
				if (villSearch->second.vida <= 0) // si muerte por el ataque
				{
					villSearch->second.vivo = false;
					//villanos.erase(villSearch);
					derrotado = true;
				}
			}
			else derrotado = true; // si el villano esta muerto cuenta como derrota
		}
		else // si el heroe no esta vivo se saca de la cola definitivamente y se devuelve false
		{
			turnos.pop(); // se elimina de la cola
			return derrotado;
		}

		turnos.push(heroSearch->second); // se vuelve a poner al final de la cola
		turnos.pop(); // se acaba su turno
		return derrotado;
	}
};


bool resuelveCaso()
{
	// No tacar nada de esta función!
	string comando;
	cin >> comando;
	if (!cin) return false;

	SistemaBatallas sistema;
	VillanoNombre v;
	HeroeNombre h;
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
				for (auto& [ataque,valor] : ataques)
				{
					cout << ataque << " " << valor << "\n";
				}
			}
			else if (comando == "mostrar_turnos")
			{
				cout << "Turno: " << endl;
				auto turnos = sistema.mostrar_turnos();
				for (auto& [pers, puntos] : turnos)
				{
					cout << pers << " " << puntos << "\n";
				}
			}
			else if (comando == "villano_ataca")
			{
				cin >> v >> h;
				bool derrotado = sistema.villano_ataca(v, h);
				cout << v << " ataca a " << h << endl;
				if (derrotado) cout << h << " derrotado" << endl;
			}
			else if (comando == "heroe_ataca")
			{
				cin >> h >> ataque >> v;
				bool derrotado = sistema.heroe_ataca(h, ataque, v);
				cout << h << " ataca a " << v << endl;
				if (derrotado) cout << v << " derrotado" << endl;
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

//#define DOMJUDGE
int main()
{
#ifndef DOMJUDGE
	ifstream in("input.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso())
	{
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
