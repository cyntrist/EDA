#include <iostream>
#include <fstream>
#include <cctype>
#include<map>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;
using Alum = map<string,list< string>>;
using Hey  = map<int ,list<string>>;
using Expulsados = map<string, string>;

struct hey {
    string deporte;
    list<string>::iterator il;
};
using alumssados = map<string, hey>;
using vectorDeportes = vector<pair<string, int>>;
void resolver(string const& primerDeporte, Alum& alum) {
    string deporte, alumno;
    deporte = primerDeporte;
    vector<string>reps;
    Expulsados exp;
    alumssados als;
    while (deporte != "_FIN_") {

        cin >> alumno;
        alum[deporte];
        while (!isupper(alumno[0]) && alumno != "_FIN_") {
            if (als.count(alumno)) {
                string dep = als[alumno].deporte;
                if (dep != deporte) {
                    list<string>::iterator it = als[alumno].il;
                    if (!exp.count(alumno)) {
                        it = alum[dep].erase(it);
                        exp[alumno] = deporte;
                    }
                    
                }
            }
            else {
                alum[deporte].push_front(alumno);
                als[alumno].deporte = deporte;
                als[alumno].il = alum[deporte].begin();
            }
            cin >> alumno;

        }
        deporte = alumno;
    }




            /*map<string, list<string>>::iterator it = alum.begin();
            bool hey = true;
            while (it != alum.end() && hey) {
                int i = 0;
                list<string>::iterator il =it-> second.begin();
                while ( il !=it->second.end()&&hey ) {
                    if (*il == alumno) {
                        if (it->first != deporte) {
                      
                            il = it->second.erase(il);
                            reps.push_back(alumno);                           
                        }
                        else {
                            ++il;
                        }
                        hey = false;
                    }
                    else ++il;
                    i++;
                }
                ++it;
            }
            if (hey) {
                int i = 0;
                while (i < reps.size() && reps[i] != alumno)i++;
                if (i == reps.size()) {
                    alum[deporte].push_back(alumno);
                 
                }
            }
              
                     cin >> alumno;
        }
      
        deporte = alumno;
    
    }

   /* for (map<string, list<string>>::iterator it = alum.begin(); it != alum.end(); ++it) {
        h[it->second.size()].push_back(it->first);
    }*/
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
    Alum alum;
    cin >> primerDeporte;
    if (!cin) return false;

    resolver(primerDeporte,alum);
    vectorDeportes v;
    for (auto it : alum)
        v.push_back({ it.first, it.second.size()});
 
    sort(v.begin(), v.end(),orden);
    for (auto i : v) {
        cout << i.first<<" "<<i.second<<endl;
    }
    cout << "---" << endl;
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