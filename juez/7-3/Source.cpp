#include <iostream>
#include <fstream>
#include <cctype>
#include<map>
#include<string>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
using  Deporte = map<string, int>;
using Alumnos = map<string, string>;
void resolver(string const& primerDeporte, Deporte& dep) {
    string deporte, alumno;
    Alumnos alm;
    set<string>expulsados;
    deporte = primerDeporte;

    while (deporte != "_FIN_") {   
            cin >> alumno;
            dep[deporte] = 0;
        while (!isupper(alumno[0]) && alumno != "_FIN_") {
            auto il = alm.find(alumno);
            if (il!=alm.end()) {
                if (alm[alumno] != deporte) {
                    dep[alm[alumno]]--;
                   il = alm.erase(il);
                   expulsados.insert(alumno);
                }
            }
            else if(!expulsados.count(alumno)) {
                dep[deporte]++;
                alm[alumno] = deporte;
            }


                cin >> alumno;
        }
        deporte = alumno;
        
    }
}
bool orden(pair<string, int> a, pair<string, int> b) {
    if (a.second == b.second)
        return a.first < b.first; // Comparar nombres de los deportes, esta antes el string que sea menor
    else
        return a.second > b.second;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;
    Deporte dep;
    resolver(primerDeporte, dep);
    vector<pair<string, int>>v;
    for (Deporte::iterator it = dep.begin(); it != dep.end(); ++it) {
        v.push_back(make_pair(it->first, it->second));
    }
    sort(v.begin(), v.end(), orden);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i].first << " " << v[i].second << endl;
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