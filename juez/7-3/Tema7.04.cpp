#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
using Lista = map<string, int>;
using OrdenSalida = map<int, vector<string>, greater<int>>;

void resolver(string const& primerDeporte, Lista& deportes, OrdenSalida& sal){
    string deporte, alumno;
    deporte = primerDeporte;
    map<string, string> alumnos;
    while (deporte != "_FIN_") {
       
        cin >> alumno;
        deportes[deporte] = 0;
        //isupper(comprueba si la primera letra es mayúscula)
        while (!isupper(alumno[0]) && alumno != "_FIN_") {
            
            //pone a 0 la lista de alumnos en el deporte
            //si no estaba ya en el alumno lo añade
            if (alumnos.count(alumno) == 0) {
                alumnos[alumno] = deporte;
                deportes[deporte]++;
            }
            else {
                //El alumno ya tiene un deporte asi que lo borra de los dos
                //Comprueba que no sea el deporte actual y que no esté mas de dos veces el alumno para borrar solo una vez
                if (alumnos[alumno] != deporte && alumnos[alumno] != "borrado") {
                    deportes[alumnos[alumno]]--;
                    alumnos[alumno] = "borrado";
                }
            }
            
            cin >> alumno;
        }
        sal[deportes[alumnos[alumno]]].push_back(deporte);
        //El último que ha leido(si no es fin) es el siguiente deporte
        deporte = alumno;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;

    Lista deportes;
    OrdenSalida depOrden;
    resolver(primerDeporte, deportes,depOrden);
    
    for (auto& g : depOrden) {

        for (int i = 0; i < g.second.size(); i++) {
            cout << g.second[i] << " " << g.first << endl;

        }
        
    }
    cout << "---\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}