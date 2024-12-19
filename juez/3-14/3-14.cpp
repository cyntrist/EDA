// Nombre del alumno ..... Nieves Alonso Gilsanz
// Usuario del Juez ...... EDA-GDV03 
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

constexpr int NUM_MONEDAS = 8;
const int valores[NUM_MONEDAS] = {1, 2, 5, 10, 20, 50, 100, 200};

// Tupla solucion: [M0, M1, M2, ..., Mn-1] n el numero total de tipos de monedas que se tienen, en este caso NUM_MONEDAS
// [n 1c, n 2c, n 5c, n 10, n 20c, n 50c, n 1€, n 2€]

// función que resuelve el problema
void resolver(vector<int>& soluc, const int monedas[NUM_MONEDAS], int precio,  int k, int usadas, int restantes, int& max_monedas)
{
	// CASOS BASE:
	// si hemos alcanzado el precio
	if (precio == 0)
	{
		max_monedas = max(max_monedas, usadas);
		return;
	}

	// si hemos agotado k o no podemos pagar justo
	if (k == NUM_MONEDAS || precio < 0 || usadas + restantes <= max_monedas)
		return;

	// número máximo de monedas restantes que podemos usar
	const int max_usables = min(precio / valores[k], monedas[k]);

	for (int i = 0; i <= max_usables; ++i)
	{
		soluc[k] = i;
		resolver(soluc, monedas, precio - i * valores[k], k + 1, usadas + i, restantes - monedas[k], max_monedas);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuest
void resuelveCaso()
{
	// leer los datos de la entrada
	int precio;
	cin >> precio;
	int monedas[NUM_MONEDAS];
	int total_monedas = 0;
	for (int i = 0; i < NUM_MONEDAS; ++i)
	{
		cin >> monedas[i];
		total_monedas += monedas[i];
	}

	vector<int> soluc(NUM_MONEDAS, 0);
	int max_monedas = -1;

	// Llamar al algoritmo de vuelta atrás
	resolver(soluc, monedas, precio, 0, 0, total_monedas, max_monedas);

	// Mostrar salida
	if (max_monedas == -1)
		cout << "IMPOSIBLE" << endl;
	else
		cout << max_monedas << endl;
}

//#define DOMJUDGE
int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("input1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	// system("PAUSE");
#endif

	return 0;
}
