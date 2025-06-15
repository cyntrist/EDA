#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
// O(log n)
char resolver(const vector<char>& sec, int ini, int fin, char prim, char ult) {
    int tam = fin - ini;
    int mit = (ini + fin) / 2;
    char c = (prim + ult) / 2;

    if (tam == 1)
        return sec[ini] == prim ? ult : prim;
    if (sec[mit] == c) // si es el esperado buscas a la derecha
		return resolver(sec, mit, fin, c, ult);
    return resolver(sec, ini, mit, prim, c); // si no buscas a la izquierda
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char prim, ult, n;
    cin >> prim >> ult;
    n = ult - prim;
    vector<char> sec(n);
    for (char& e : sec) cin >> e;
    cout << resolver(sec, 0, n, prim, ult) << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
