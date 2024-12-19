// Amparo Rubio Bellon
// VJ54


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <climits>
using namespace std;

const int NUM_MONEDAS = 8;
const int valores[NUM_MONEDAS] = { 1,2,5,10,20,50,100,200 };

//Estructura que utilizamos para almacenar la informacion necesaria para resolver el problema:
struct Solucion {
    int monedas; // la cantidad de monedas que he usado
    int maxMonedas; //la cantidad maxima de monedas que he usado en una solucion (ESTO ES LO QUE BUSCAMOS)
    int suma; // el dinero que levo acumulado con las monedas que he usado
    std::vector<int> combinacion; // vector de tantas componentes como tipos de moneda, en la que apuntamos cuantas hemos usado de cada tipo

    Solucion() : suma(0), monedas(0), maxMonedas(INT_MIN), combinacion(vector<int>(NUM_MONEDAS, 0)) {};
};

//NO SE REPITEN SOLUCIONES, ya que comprobamos si es mejorable

void resolver(Solucion& sol, int k, int precio, vector<int> const& calderilla) {
    //Recorremos tantas veces como monedas pueda usar [0 - numero disponible]
    for (int i = 0; i <= calderilla[k]; i++) {

        //Si no me paso de dinero usando el numero de monedas que me toca
        if (sol.suma + (valores[k] * i) <= precio) {

            // usamos i monedas del tipo k-esimo, aumentamos la solucion
            sol.combinacion[k] = i;
            sol.monedas += i;
            sol.suma += (valores[k] * i);

            //Si he llegado al precio y mejoro --> actualizo el maximo
            if (sol.suma == precio) {
                if (sol.maxMonedas < sol.monedas) sol.maxMonedas = sol.monedas;
            }

            //Si quedan tipos de moneda que visitar y puedo mejorar el numero de monedas (con las que son del mismo tipo como minimo)
            else if (k < NUM_MONEDAS - 1) {
                if (sol.monedas + (precio - sol.suma) / valores[k] > sol.maxMonedas) 
                    resolver(sol, k + 1, precio, calderilla);
            }

            //Desmarcamos la solucion y seguimos probando
            sol.monedas -= i;
            sol.suma -= (valores[k] * i);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int precio;
    std::vector<int> monedas(NUM_MONEDAS);
    std::cin >> precio;
    for (int i = 0; i < NUM_MONEDAS; ++i)
        std::cin >> monedas[i];

    //solucionamos
    Solucion sol = Solucion();
    resolver(sol, 0, precio, monedas);
    
    // Mostrar salida
    if (sol.maxMonedas > INT_MIN) 
        std::cout << sol.maxMonedas << "\n";
    else 
        std::cout << "IMPOSIBLE" << "\n";
}

#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}