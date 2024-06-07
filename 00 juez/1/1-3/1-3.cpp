// Nombre del alumno ..... Cynthia Tristán Álvarez  
// Usuario del Juez ...... VJ62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
bool resolver(const vector<int> &valores, const unsigned int p) {
    bool dividido = true;

    int max = valores[0];
    unsigned int i;

    for (i = 1; i <= p; i++)
        if (valores[i] > max) 
            max = valores[i];

    i = p + 1;
    while (i < valores.size() && max < valores[i])
        i++;

    if (i < valores.size())
        dividido = false;

    return dividido;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	unsigned int num, p;
    cin >> num >> p;
    vector< int> valores;

    for (unsigned int i = 0; i < num; i++)
    {
        int n;
        cin >> n;
        valores.push_back(n);
    }

    const bool sol = resolver(valores, p);
    sol ? cout << "SI\n" : cout << "NO\n";
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