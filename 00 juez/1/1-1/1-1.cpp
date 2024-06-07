// Nombre del alumno ..... Cynthia Tristán Álvarez
// Usuario del Juez ...... VJ62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
bool resolver(const vector<int>& alturas, const int& n) {
    bool dalton = true;
    int i = n - 1;
    while (dalton && i > 0) 
    {
	    if (alturas[i - 1] <= alturas [i])
            dalton = false;
        i--;
    }

    if (!dalton)
    {
        dalton = true;
        i = 0;
        while (dalton && i < n - 1) 
        {
            if (alturas[i] >= alturas[i + 1])
                dalton = false;
            i++;
        }
    }

    return dalton;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    if (!std::cin)
        return false;

    int n; 
    cin >> n;
    if (n == 0)
        return false;

    vector<int> alturas(n);
    for (int i = 0; i < n; ++i) {
        cin >> alturas[i];
    }
    const bool sol = resolver(alturas, n);

    sol ? cout << "DALTON" : cout << "DESCONOCIDOS";
    cout << "\n";

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
    system("PAUSE");
#endif

    return 0;
}