#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    map<string, int> diccionarioAntiguo, diccionarioNuevo;
    vector<string> agregadas, eliminadas, modificadas;

    // Leer el diccionario antiguo
    string line;
    getline(cin, line);
    stringstream ss(line);
    string clave;
    int valor;
    while (ss >> clave >> valor) {
        diccionarioAntiguo[clave] = valor;
    }

    // Leer el diccionario nuevo
    getline(cin, line);
    stringstream ss2(line);
    while (ss2 >> clave >> valor) {
        diccionarioNuevo[clave] = valor;
    }

    // Buscar claves agregadas, eliminadas y modificadas
    for (auto const& p : diccionarioNuevo) {
        auto it = diccionarioAntiguo.find(p.first);
        if (it == diccionarioAntiguo.end())
            agregadas.push_back(p.first);
        else if (it->second != p.second) 
            modificadas.push_back(p.first);

    }

    for (auto const& p : diccionarioAntiguo) {
        auto it = diccionarioNuevo.find(p.first);
        if (it == diccionarioNuevo.end()) 
            eliminadas.push_back(p.first);
    }

    // Escribir los cambios
    if (agregadas.size() > 0) {
        sort(agregadas.begin(), agregadas.end());
        cout << "+";
        for (auto const& clave : agregadas) 
            cout << " " << clave;

        cout << endl;
    }

    if (eliminadas.size() > 0) {
        sort(eliminadas.begin(), eliminadas.end());
        cout << "-";
        for (auto const& clave : eliminadas) 
            cout << " " << clave;

        cout << endl;
    }

    if (modificadas.size() > 0) {
        sort(modificadas.begin(), modificadas.end());
        cout << "*";
        for (auto const& clave : modificadas)
            cout << " " << clave;

        cout << endl;
    }

    if (agregadas.size() == 0 && eliminadas.size() == 0 && modificadas.size() == 0)
        cout << "Sin cambios" << endl;

    cout << "---" << endl;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    cin.ignore();
    for (int i = 0; i < numCasos; i++)
        resuelveCaso();

        // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
