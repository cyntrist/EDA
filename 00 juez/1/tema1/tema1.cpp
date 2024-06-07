// Nombre del alumno ..... Cynthia Tristán Álvarez  
// Usuario del Juez ...... VJ62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// com. asin:  O(n), número de edificios de alturas.size().

// función que resuelve el problema
pair<int, int> resolver(const vector<int> &alturas, const int altura, const int num) {
    pair<int, int> secuencia;

    int i = 0, actual = 0, mayor = 0;
    while (i < num) 
    {             
        if (altura < alturas[i]) 
            actual++;
        else 
        {
            if (actual > mayor) 
            { 
                mayor = actual;
                secuencia.second = i - 1;     
                secuencia.first = secuencia.second - actual + 1;   
            }
            actual = 0;     
        }
        i++;
    }

    if (actual > mayor) 
    {     
        secuencia.second = i - 1;    
        secuencia.first = secuencia.second - actual + 1;    
    }

    return secuencia;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n, t;
    cin >> n >> t;
    vector<int> alturas(n);

    for (int i = 0; i < n; i++)
        cin >> alturas[i];

    pair<int, int> secuencia = resolver(alturas, t, n);
    cout << secuencia.first << " " << secuencia.second << "\n";
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