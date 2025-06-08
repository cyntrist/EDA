#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;

using paciente = string;
using gravedad = int;

using enfermo = pair<paciente, gravedad>;
using lista = list<enfermo>;
using registro = unordered_map<paciente, gravedad>;
using curados = map<paciente, gravedad>;
using listas = vector<lista>;

// Queremos gestionar la sala de espera del servicio de urgencias de un hospital muy especial,
// donde los pacientes suelen mejorar solo por esperar.
// La implementación del sistema se realizará mediante un TAD urgencias con las siguientes operaciones:
class urgencias {
protected:
    lista graves;
    lista medias;
    lista leves;
	listas listados = {leves, medias, graves};
    registro reg;
    curados sanos;

public:
    // registra a un nuevo paciente (un string), que ya ha sido preevaluado por un médico
    // que le ha asignado cierta gravedad(un int) : leve(￿), media(￿) o grave(￿).
    // El paciente pasa a la sala de espera.
    // Si el paciente ya estaba registrado, lanzará una excepción domain_error con mensaje Paciente repetido.
    // Si la gravedad dada no es un número entre 1 ￿y 3, se lanzará una excepción domain_error con el mensaje Gravedad incorrecta.
    // coste: O(n) en caso peor siendo n el tamaño del registro
    void nuevo_paciente(paciente p, gravedad g) {
        auto search = reg.find(p);
        if (search != reg.end())
            throw domain_error("Paciente repetido");
        if (g < 1 || g > 3)
            throw domain_error("Gravedad incorrecta");

        //listados[g - 1].emplace_back(p, g);

        switch (g)
        {
        case 1: leves.emplace_back(p, g); break;
        case 2: medias.emplace_back(p, g); break;
        case 3: graves.emplace_back(p, g); break;
        }

        reg[p] = g;
    }

    // devuelve el entero que representa la gravedad actual de paciente.
    // Si el paciente no está en la sala de espera, se lanzará una excepción domain_error con mensaje Paciente inexistente.
    // coste: O(n) en caso peor siendo n el tamaño del registro
    int gravedad_actual(paciente p) const {
        auto search = reg.find(p);
        if (search == reg.end())
            throw domain_error("Paciente inexistente");

        return search->second;
    }

    // devuelve el nombre del paciente al que le toca ser atendido, que abandona la sala de espera.
    // Los pacientes se atienden teniendo en cuenta su gravedad:
    // primero los graves, luego los de gravedad media y por último los leves.
    /// Dentro de la misma gravedad se tiene en cuenta el orden de llegada (el primero que llega es el más prioritario),
    /// o el que provoca la operación mejora de cambio de gravedad, explicada a continuación.
    // Si no hay pacientes se lanzará una excepción domain_error con mensaje No hay pacientes.
    // coste: O(n) por erase
    paciente siguiente() {
        if (!graves.empty()) 
        {
            auto first = graves.front().first;
            graves.pop_front();
            reg.erase(first);
            return first;
        }
        if (!medias.empty()) 
        {
            auto first = medias.front().first;
            medias.pop_front();
            reg.erase(first);
            return first;
        }
        if (!leves.empty())
        {
            auto first = leves.front().first;
            leves.pop_front();
            reg.erase(first);
            return first;
        }
    	throw domain_error("No hay pacientes");
    }

    // registra el hecho de que un paciente mejora estando en la sala de espera.
    // Si estaba grave pasa a gravedad media y si tenía gravedad media pasa a leve.
    // Para el orden de atención se coloca como el más prioritario de los que tienen la nueva gravedad.
    // Si el paciente estaba leve, entonces se recupera y abandona las urgencias.
    // Si el paciente no existe, se lanzará una excepción domain_error con mensaje Paciente inexistente.
    // coste: O(n) por find, erase
    void mejora(paciente p) {
        auto search = reg.find(p);
        if (search == reg.end())
            throw domain_error("Paciente inexistente");

        //paciente p = search->first;
        gravedad g = search->second;
        switch (g)
        { // Para el orden de atención se coloca como el más prioritario de los que tienen la nueva gravedad.
        case 1: // Si el paciente estaba leve, entonces se recupera y abandona las urgencias.
	        {
				if (leves.empty()) break;
	            auto i = leves.begin();
	            while (i != leves.end() && i->first != p) ++i;
                if (i != leves.end())
                {
		            leves.erase(i);
		            reg.erase(p);
	                sanos[p] = g;
                }
	        }
            break;
        case 2: //  si tenía gravedad media pasa a leve.
	        {
	            if (medias.empty()) break;
	            auto i = medias.begin();
	            while (i != medias.end() && i->first != p) ++i;
                if (i != medias.end())
                {
		            leves.push_front(*i);
	                medias.erase(i);
                    reg[p] = g - 1;
                }
	        }
            break;
        case 3: // Si estaba grave pasa a gravedad media 
	        {
	            if (graves.empty()) break;
				auto i = graves.begin();
                while (i != graves.end() && i->first != p) ++i;
                if (i != graves.end())
                {
	                medias.push_front(*i);
	                graves.erase(i);
                    reg[p] = g - 1;
                }
	        }
            break;
        }
    }

    // devuelve un tipo de datos lineal ordenado alfabéticamente (y sin repeticiones)
    // con los pacientes que han pasado alguna vez por el servicio de urgencias
    // y se han recuperado del todo mientras esperaban.
    // coste: O(n) siendo n la cantidad de sanos
    list<paciente> recuperados() const {
        list<paciente> res;

        auto it = sanos.begin();
        while (it != sanos.end())
        {
            res.emplace_back( it->first );
            ++it;
        }

        return res;
    }
};

bool resuelveCaso() { // No tocar esta función
    string orden, pac;
    int grav;
    cin >> orden;
    if (!cin) return false;

    urgencias sala;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> pac >> grav;
                sala.nuevo_paciente(pac, grav);
            }
            else if (orden == "gravedad_actual") {
                cin >> pac;
                int g = sala.gravedad_actual(pac);
                cout << "La gravedad de " << pac << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                string p = sala.siguiente();
                cout << "Siguiente paciente: " << p << '\n';
            }
            else if (orden == "recuperados") {
                auto lista = sala.recuperados();
                cout << "Lista de recuperados:";
                for (auto& p : lista)
                    cout << ' ' << p;
                cout << '\n';
            }
            else if (orden == "mejora") {
                cin >> pac;
                sala.mejora(pac);
            }
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
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
