#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cassert>
#include <list>
#include <utility>

using namespace std;

using paciente = string;
using gravedad = int;

using enfermo = pair<paciente, gravedad>;
using lista = list<enfermo>;

// Queremos gestionar la sala de espera del servicio de urgencias de un hospital muy especial,
// donde los pacientes suelen mejorar solo por esperar.
// La implementación del sistema se realizará mediante un TAD urgencias con las siguientes operaciones:

class urgencias {
protected:
    lista graves;
    lista media;
    lista leve;

public:
    // registra a un nuevo paciente (un string), que ya ha sido preevaluado por un médico
    // que le ha asignado cierta gravedad(un int) : leve(￿), media(￿) o grave(￿).
    // El paciente pasa a la sala de espera.
    // Si el paciente ya estaba registrado, lanzará una excepción domain_error con mensaje Paciente repetido.
    // Si la gravedad dada no es un número entre 1 ￿y 3, se lanzará una excepción domain_error con el mensaje Gravedad incorrecta.
    // coste:
    void nuevo_paciente(paciente p, gravedad g) {
        
            throw domain_error("Paciente repetido");
        
            throw domain_error("Gravedad incorrecta");
        
    }


    // devuelve el entero que representa la gravedad actual de paciente.
    // Si el paciente no está en la sala de espera, se lanzará una excepción domain_error con mensaje Paciente inexistente.
    // coste:
    int gravedad_actual(paciente p) const {
        
            throw domain_error("Paciente inexistente");
        
    }

    // devuelve el nombre del paciente al que le toca ser atendido, que abandona la sala de espera.
    // Los pacientes se atienden teniendo en cuenta su gravedad :
    // primero los graves, luego los de gravedad media y por último los leves.
    // Dentro de la misma gravedad se tiene en cuenta el orden de llegada (el primero que llega es el más prioritario),
    // o el que provoca la operación mejora de cambio de gravedad, explicada a continuación.
    // Si no hay pacientes se lanzará una excepción domain_error con mensaje No hay pacientes.
    // coste:
    paciente siguiente() {
        
            throw domain_error("No hay pacientes");
        
    }

    // registra el hecho de que un paciente mejora estando en la sala de espera.
    // Si estaba grave pasa a gravedad media y si tenía gravedad media pasa a leve.
    // Para el orden de atención se coloca como el más prioritario de los que tienen la nueva gravedad.
    // Si el paciente estaba leve, entonces se recupera y abandona las urgencias.
    // Si el paciente no existe, se lanzará una excepción domain_error con mensaje Paciente inexistente.
    // coste:
    void mejora(paciente p) {
        
    }

    // devuelve un tipo de datos lineal ordenado alfabéticamente (y sin repeticiones)
    // con los pacientes que han pasado alguna vez por el servicio de urgencias
    // y se han recuperado del todo mientras esperaban.
    // coste:
    list<paciente> recuperados() const {
        
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
