#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

// Función que procesa una línea del texto
void procesarLinea(int numLinea, const string& linea, map<string, set<int>>& apariciones) {
    string palabra = "";
    for (char c : linea) {
        if (isalpha(c))
            palabra += tolower(c);
        else {
            if (palabra.size() > 2)
                apariciones[palabra].insert(numLinea);
            palabra = "";
        }
    }
    if (palabra.size() > 2)
        apariciones[palabra].insert(numLinea);
}

map<string, set<int>> procesarCaso(int n) {
    map<string, set<int>> apariciones; // Diccionario de palabras y sus apariciones
    for (int i = 1; i <= n; i++) {
        string linea;
        getline(cin, linea);
        procesarLinea(i, linea, apariciones);
    }

    return apariciones;
}

void mostrar_sol(const map<string, set<int>>& apariciones) {
    // Imprimir resultados
    for (auto it = apariciones.begin(); it != apariciones.end(); it++) {
        string palabra = it->first;
        set<int> lineas = it->second;

        // Imprimir palabra y sus apariciones
        cout << palabra << " ";
        for (int linea : lineas)
            cout << linea << " ";
        cout << endl;
    }
    cout << "---" << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n;
    // Leer los datos de la entrada
    cin >> n;
    cin.ignore(); // Para el caracter de fin de línea
    if (n == 0)
        return false;

    // Resolver problema y mostrar solución
    auto sol = procesarCaso(n);
    mostrar_sol(sol);

    return true;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

        // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
