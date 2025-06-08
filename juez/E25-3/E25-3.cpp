#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <unordered_map>
#include <utility>

using namespace std;

using Jugador = string;
using Equipo = string;

using ListaJugadores = list<Jugador>;
using ListaEquipos = list<Equipo>;
using Equipos = unordered_map<Equipo, ListaJugadores>;
using Jugadores = unordered_map<Jugador, ListaEquipos>;

// Ante el cambio continuo de equipo por parte de los jugadores,
// la Liga de Fútbol Profesional necesita un nuevo gestor de futbolistas más efi￿ciente
// que le permita conocer el equipo actualque tiene ￿chado a cada jugador o ciertos datos
// sobre el historial de ￿chajes. Se pide implementarun TAD GestorFutbolistas que implemente
// las siguientes operaciones:
class GestorFutbolistas {
private:
    Equipos equipos;
    Jugadores jugadores;

public:
    ///  Si el jugador (un string) no está dado de alta en el sistema, se registra por primera vez
    ///  como perteneciente al equipo (otro string).
    ///  Si el equipo no estaba dado de alta, se le da de alta en ese momento.
    ///  Si el jugador ya estaba dado de alta, la operación supone un cambio de equipo, pasando a estar ￿fichado por el nuevo equipo.
    ///  Si el jugador ya estaba fi￿chado por este equipo, la operación no tiene ningún efecto.
    // Coste: 
    void fichar(const Jugador& jugador, const Equipo& equipo) {
        auto itJu = jugadores.find(jugador);
        bool juEncontrado = false;
        Equipo antiguoEquipo;
        if (itJu == jugadores.end()) // si no estaba en un equipo antes aka no estaba registrado
        {
            ListaEquipos l = { equipo };
            jugadores.insert({ jugador, l }); // insertar en el mapa
        }
        else // si tiene algun equipo antes buscamos si ha sido fichado por este antes
        {
            juEncontrado = true;
            antiguoEquipo = *itJu->second.begin();
            auto itEq = itJu->second.begin();
            while (itEq != itJu->second.end() && *itEq != equipo) ++itEq;

            if (itEq != itJu->second.end() && itEq != itJu->second.begin()) // has encontrado al equipo y no es el actual
            {
                itJu->second.push_front(*itEq);
                itJu->second.erase(itEq);
            }
            else itJu->second.push_front(equipo);
        }





        auto itEq = equipos.find(equipo);
        if (itEq == equipos.end()) // si no existe el equipo
        {
	        if (juEncontrado)
	        {
                auto itAntiguoEquipo = equipos.find(antiguoEquipo);

                auto it = itAntiguoEquipo->second.begin();
                while (it != itAntiguoEquipo->second.end() && *it != jugador)
                    ++it;

                if (it != itAntiguoEquipo->second.end())
                    itAntiguoEquipo->second.erase(it);
	        }
			ListaJugadores l = { jugador }; 
            equipos.insert({ equipo, l }); // se da de alta con este unico jugador
        }
        else // si si existe el equipo instertamos el jugador si no existe a en su lista de jugadores
        {
            auto j2 = itEq->second.begin(); // buscamos al jugador en el equipo
            while (j2 != itEq->second.end() && *j2 != jugador) 
                ++j2;

            if (j2 != itEq->second.end() && j2 != itEq->second.begin()) // has encontrado al jugador 
            {
                itEq->second.push_front(*j2);
                itEq->second.erase(j2);
            }
            else
            {
                itEq->second.push_front(jugador);
            }
        }
    }

    /// Devuelve el equipo actual por el que está ￿chado este jugador.
    /// En caso de que el jugador no esté dado de alta, lanzará una excepción domain_error con el mensaje “Jugador inexistente”.
    // Coste:
    Equipo equipoActual(const Jugador& jugador) const {
        auto j = jugadores.find(jugador);
        if (j == jugadores.end())
			throw domain_error("Jugador inexistente");

        return j->second.front();
    }

    // Devuelve cuántos jugadores tiene ￿chados actualmente el equipo.
    // En caso de que el equipo no esté dado de alta, lanzará una excepción domain_error con el mensaje “Equipo inexistente”.
    // Coste:
    int fichados(const Equipo& equipo) const {
        auto e = equipos.find(equipo);
        if (e == equipos.end())
			throw domain_error("Equipo inexistente");

        return e->second.size();
    }

    // Devuelve en un tipo de datos lineal los n últimos jugadores fichados por el equipo (con n > 0)
    // que aún siguen fi￿chados por dicho equipo.
    // El tipo lineal estará ordenado por el momento en que fueron fi￿chados, primero el último ￿fichaje.
    // Si el equipo tiene menos de n jugadores, se devolverán todos, ordenados de la misma manera.
    // En caso de que el equipo no esté dado de alta, lanzará una excepción domain_error con el mensaje “Equipo inexistente”.
    // Coste: 
    list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const {
        auto e = equipos.find(equipo);
        if (e == equipos.end())
            throw domain_error("Equipo inexistente");

        list<Jugador> res;

        auto m = min(n, (int)e->second.size());
        auto j = e->second.begin();

        for (int i = 0; i < m; i++)
        {
            res.push_back(*j);
            ++j;
        }

        return res;
    }

    // Devuelve el número de equipos distintos por los que ha estado fi￿chado el jugador.
    // Si el jugador no está dado de alta en el sistema, devolverá 0.
    // Coste:
    int cuantosEquipos(const Jugador& jugador) const {
        auto j = jugadores.find(jugador);
        if (j == jugadores.end())
            return 0;
        return j->second.size();
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
    ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
