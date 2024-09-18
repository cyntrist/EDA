// Nombre del alumno ..... Cynthia Tristán Álvarez  
// Usuario del Juez ...... VJ62
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// com. asin: O(n) lineal, remove y erase

// función que resuelve el problema
vector<long long int> resolver(vector<long long int> &valores) {
    for (unsigned int i = 0; i < valores.size(); i++)
	    if (valores[i] % 2 == 1)
            valores[i] = 0;

    valores.erase( std::remove( valores.begin(), valores.end(), 0), valores.end() ) ;

    return valores;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    vector<long long int> valores;
    unsigned int num;
    cin >> num;

    for (unsigned int i = 0; i < num; i++)
    {
        long long int valor;
        cin >> valor;
        valores.push_back(valor);
    }

    valores = resolver(valores);

    for (const int i : valores) 
        cout << i << ' ';

    cout << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}