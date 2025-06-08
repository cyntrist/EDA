/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <unordered_map>
#include <utility>

using namespace std;

using Jugador = string;
using Equipo = string;

using ListaJugadores = std::list<Jugador>;
using Equipos = std::unordered_map<Equipo, ListaJugadores>;

using ListaEquipos = std::list<Equipo>;
using Jugadores = std::unordered_map<Jugador, ListaEquipos>;

class GestorFutbolistas {
private:
    Equipos equipos;
    Jugadores jugadores;

public:
    // Si el jugador (un string) no está dado de alta en el sistema,
    // se registra por primera vez como perteneciente al equipo (otro string).

    // Si el equipo no estaba dado de alta, se le da de alta en ese momento.

    // Si el jugador ya estaba dado de alta, la operación supone un cambio de equipo, pasando a estar fichado por el nuevo equipo.

    // Si el jugador ya estaba fichado por este equipo, la operación no tiene ningún efecto.
    // Coste: 
    void fichar(const Jugador& jugador, const Equipo& equipo)
	{
        // JUGADORES
        // si no ha estado en ningun equipo antes (no le encuentras) -> lo registras
        auto itJu = jugadores.find(jugador);
        bool juEncontrado = false;
        Equipo antiguoEquipo;
        if (itJu == jugadores.end())
        {
            ListaEquipos l = { equipo };
            jugadores.insert({jugador, l});
        }
        // si ya ha estado en un equipo (le encuentras)
        else
        {
            juEncontrado = true;
            antiguoEquipo = *itJu->second.begin();
            auto itEq = itJu->second.begin();
            while (itEq != itJu->second.end() && *itEq != equipo) ++itEq; // buscar al equipo

            // si lo has encontrado y no es el primero
            if (itEq != itJu->second.end() && itEq != itJu->second.begin())
            {
                // lo cambias al principio
                itJu->second.push_front(*itEq);
                itJu->second.erase(itEq);
            }
            else
            {
                itJu->second.push_front(equipo);
            }
        }



        // EQUIPOS
        auto itEq = equipos.find(equipo);
        if (itEq == equipos.end()) // si no existe el equipo
        {
            if (juEncontrado)
            {
                auto itAntiguoEquipo = equipos.find(antiguoEquipo);

                auto it = itAntiguoEquipo->second.begin();
                while (it != itAntiguoEquipo->second.end() && *it != jugador) ++it; // buscar al jugador

                if (it != itAntiguoEquipo->second.end()) itAntiguoEquipo->second.erase(it);
            }

            ListaJugadores l = { jugador };
            equipos.insert({ equipo, l });
        }
        else // si ya existe el equipo
        {
            auto it = itEq->second.begin();
            while (it != itEq->second.end() && *it != jugador) ++it; // buscar al jugador

            // si lo has encontrado y no es el primero
            if (it != itEq->second.end() && it != itEq->second.begin())
            {
                // lo cambias al principio
                itEq->second.push_front(*it);
                itEq->second.erase(it);
            }
            else
            {
                itEq->second.push_front(jugador);
            }
        }
    }

    // Devuelve el equipo actual por el que está fichado este jugador.

    // En caso de que el jugador no esté dado de alta, lanzará una excepción domain_error con el mensaje "Jugador inexistente"
    // Coste:
    Equipo equipoActual(const Jugador& jugador) const
	{
        auto itJu = jugadores.find(jugador);

        if(itJu == jugadores.end()) throw domain_error("Jugador inexistente");

        return itJu->second.front();
    }

    // Devuelve cuántos jugadores tiene fichados actualmente el equipo.

    // En caso de que el equipo no esté dado de alta, lanzará una excepción domain_error con el mensaje "Equipo inexistente".
    // Coste:
    int fichados(const Equipo& equipo) const
	{
        auto itEq = equipos.find(equipo);
        if (itEq == equipos.end()) throw domain_error("Equipo inexistente");

        return itEq->second.size();
    }

    // Devuelve en un tipo de datos lineal los n ultimos jugadores fichados por el equipo (con n > 0) que aún siguen fichados por dicho equipo.
    // El tipo lineal estará ordenado por el momento en que fueron fichados, primero el último fichaje.
    // Si el equipo tiene menos de n jugadores, se devolverán todos, ordenados de la misma manera.

    // En caso de que el equipo no esté dado de alta, lanzará una excepción domain_error con el mensaje "Equipo inexistente"
    // Coste: 
    list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const
	{
        auto itEq = equipos.find(equipo);
        if (itEq == equipos.end()) throw domain_error("Equipo inexistente");

        auto m = 0;
        m = min(n, (int)itEq->second.size());

        auto itJu = itEq->second.begin();
        list<Jugador> ults;
        for (int i = 0; i < m; ++i)
        {
            ults.push_back(*itJu);
            ++itJu;
        }
        return ults;
    }

    // Devuelve el número de equipos distintos por los que ha estado fichado el jugador
    // Si el jugador no está dado de alta en el sistema, devolverá 0
    // Coste:
    int cuantosEquipos(const Jugador& jugador) const
	{
        auto itJu = jugadores.find(jugador);
        if (itJu == jugadores.end()) return 0;

        return itJu->second.size();
    }
};


bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!cin) return false;

    GestorFutbolistas gestor;
    while (operacion != "FIN") {
        try {
            if (operacion == "fichar") {
                string jugador, equipo;
                cin >> jugador >> equipo;
                gestor.fichar(jugador, equipo);
            }
            else if (operacion == "equipo_actual") {
                string jugador;
                cin >> jugador;
                string equipo = gestor.equipoActual(jugador);
                cout << "El equipo de " << jugador << " es " << equipo << endl;
            }
            else if (operacion == "fichados") {
                string equipo;
                cin >> equipo;
                int n = gestor.fichados(equipo);
                cout << "Jugadores fichados por " << equipo << ": " << n << endl;
            }
            else if (operacion == "ultimos_fichajes") {
                string equipo;
                int n;
                cin >> equipo >> n;
                list<string> ultimos = gestor.ultimosFichajes(equipo, n);
                cout << "Ultimos fichajes de " << equipo << ": ";
                for (const auto& jugador : ultimos) {
                    cout << jugador << " ";
                }
                cout << endl;
            }
            else if (operacion == "cuantos_equipos") {
                string jugador;
                cin >> jugador;
                int n = gestor.cuantosEquipos(jugador);
                cout << "Equipos que han fichado a " << jugador << ": " << n << endl;
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> operacion;
    }

    cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
