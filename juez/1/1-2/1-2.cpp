// Nombre del alumno ..... Cynthia Tristán Álvarez  
// Usuario del Juez ...... VJ62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
vector<int> resolver(const int numTemps, const vector<int>& temps) {
    int max = 0;
    int min = 0;

    for (int i = 1; i < numTemps - 1; i++)
    {
        if (temps[i - 1] < temps[i] && temps[i + 1] < temps[i])
            max++;
        else if (temps[i - 1] > temps[i] && temps[i + 1] > temps[i])
            min++;
    }

    vector<int> mym = { max, min };
    return mym;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    if (!std::cin)
        return false;

    int numTemps; // numero de temperaturas en el caso
    cin >> numTemps;
    vector<int> temps;

    for (int j = 0; j < numTemps; j++)
    {
        int temp;
        cin >> temp;
        temps.insert(temps.end(), temp);
    }

    const vector<int> mym = resolver(numTemps, temps);
    cout << mym[0] << " " << mym[1] << "\n";

    return true;
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