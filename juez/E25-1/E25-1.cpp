/*
Qué has conseguido hacer y qué no:

Tupla solución:

Marcadores:

Ejemplo de aplicación de poda por estimación:

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, vector<T> const& v)
{
	for (auto& e : v) out << e << " ";
	return out;
}

/// función que resuelve el problema
// parametros:
// --- entrada
// soluc		-> vector solucion
// k			-> area
// i de for		-> candidatos
// n			-> n voluntarios
// m			-> n areas a limpiar
// l			-> n areas minimas a limpiar
// kilosPorArea	-> kg a limpiar por area
// --- marcadores
// suma			-> kg totales
// maxSuma		-> kg totales maximizados
// limpias		-> areas limpiadas hasta el momento
// asignados	-> vector de areas según voluntario
void resolver(vector<int>& soluc, int k, int n, int m, int l, vector<int>& kilosPorArea, 
	vector<vector<int>> const& kilosPorVoluntario, 
	int suma, vector<int>& asignados, int limpias, int& maxSuma)
{
	// ---- ESQUEMA DE BACKTRACKING ----

	// !!!! marcar en el mismo ambito en el que se desmarca

	// 1) for de candidatos     -> candidatos
	// --- 2) guardar el indice del for que se va probando en el vect solucion
	// --- 3) if esValida       -> ver si lo que acabas de guardar ha sido una eleccion valida
	// ------ 4) if esSolucion  -> 
	// --------- 5) if esMejor  -> 
	// ------ 6) else noSolucion
	// --------- 7) if poda     ->
	// ------------ 8) llamada recursiva k+1

	if (k >= m) return;
	for (int i = 0; i < n; i++) // ciclar voluntarios
	{
		// marcar
		suma += kilosPorVoluntario[k][i]; /// guardar maximo por area 

		soluc[k] = suma;

		if (asignados[i] == -1) // es valida
		{
			// marcar
			asignados[i] = k;
			if (soluc[k] >= kilosPorArea[k]) 
				limpias++;

			if (limpias >= l) // es solucion
			{
				if (suma >= maxSuma) // es mejor
					maxSuma = suma;
			}
			else if (k < n - 1)
			{
				//if () // poda
				resolver(soluc, k + 1, n, m, l, kilosPorArea, kilosPorVoluntario, suma, asignados, limpias, maxSuma);
			}
			// desmarcamos
			if (soluc[k] >= kilosPorArea[k])
				limpias++;
			asignados[i] = -1;
		}

		// desmarcamos
		suma -= kilosPorVoluntario[k][i];
	}
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	// leer los datos de la entrada
	int n, m, l; // num voluntarios, numero de areas a limpiar >= 1, numero de areas minimas
	cin >> n >> m >> l;
	vector<int> kilosPorArea(m); // lodo en kilogramos por area
	for (int i = 0; i < m; ++i)
		cin >> kilosPorArea[i];
	vector<vector<int>> kilosPorVoluntario(n, vector<int>(m)); // kg que puede limpiar voluntario por area
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> kilosPorVoluntario[i][j];

	vector<int> soluc(m);
	vector<int> asignados(n, -1);
	int k = 0, maxSuma = 0;
	resolver(soluc, k, n, m, l, kilosPorArea, kilosPorVoluntario, 0, asignados, 0, maxSuma);
	if (maxSuma <= 0) cout << "IMPOSIBLE" << endl;
	else cout << maxSuma << endl;
}

//#define DOMJUDGE
int main()
{
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
