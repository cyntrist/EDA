#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int NUM_MONEDAS = 8;
const int valores[NUM_MONEDAS] = { 1,2,5,10,20,50,100,200 };

// función que resuelve el problema
void resolver(int monedas[NUM_MONEDAS], int& res, int pos, int act, int cantidad, int& precio) {
    //creo que se puede cambiar
    if (pos >= NUM_MONEDAS)
        return;
    for (int i = 0; i <= monedas[pos]; i++) {

        int aux = act;
        aux += valores[pos] * i;

        if (aux == precio) {
            if (res < cantidad + i)
                res = cantidad + i;
            return;
        }
        if (aux > precio)
            return;

        resolver(monedas, res, pos + 1, aux, cantidad+i, precio);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int precio;
    int monedas[NUM_MONEDAS];
    cin >> precio;
    for (int i = 0; i < NUM_MONEDAS; ++i)
        cin >> monedas[i];
    //vector<int> sol(NUM_MONEDAS);
    int res = 0;
    resolver(monedas, res, 0, 0, 0, precio);
    // Mostrar salida
    if (res == 0)
        cout << "IMPOSIBLE\n";
    else
        cout << res << "\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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
