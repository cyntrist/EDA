#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int resolver(std::vector<int> v, int ini, int fin)
{
    int tam = fin - ini;
    int mit = (ini + fin) / 2;

    if (tam == 1) 
        return v[ini];

    if (v[mit] == v[0] + mit) // esta a la derecha
        return resolver(v, mit, fin);
    return resolver(v, ini, mit);
}

void resuelveCaso() {

    int n = 0;
    std::cin >> n;

    std::vector<int> v(n);
    int e = 0;
    for (int i = 0; i < n; i++) 
    {
        std::cin >> e;
        v[i] = e;
	}

    int r = resolver(v, 0, n);
    std::cout << r << '\n';
}

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
    system("PAUSE");
#endif

    return 0;
}