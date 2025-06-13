#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
#include <ratio>
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
// sumaTotal	-> kg totales
// maxSuma		-> kg totales maximizados
// limpias		-> areas limpiadas hasta el momento

// TUPLA = soluc(n) // cada i es el area (0 a m-1) que le asignas a ese voluntario
// [2, 1, 1, 1, 0] -> i=0 asignado a area 2, i=1 asignado a area 1
void resolver(vector<int>& soluc, int k, int n, int m, int l, vector<int>& kilosPorArea, 
	vector<vector<int>> const& kilosPorVoluntario, 
	int sumaTotal, int limpias, int& maxSuma, vector<int>& kilosPorAreaRestantes, vector<int>& kilosDesde)
{
	// ---- ESQUEMA DE BACKTRACKING ----

	// !!!! marcar en el mismo ambito en el que se desmarca

	// 1) for de candidatos     -> candidatos
	// --- 2) guardar el indice del for que se va probando en el vect solucion
	// --- 3) if				-> ver si lo que acabas de guardar ha sido una eleccion valida
	// ------ 4) if esSolucion  -> 
	// --------- 5) if esMejor  -> 
	// ------ 6) else noSolucion
	// --------- 7) if poda     ->
	// ------------ 8) llamada recursiva k+1

	for (int area = 0; area < m; ++area) // candidatos: areas
	{
		if (soluc[k] == -1) // valida
		{
			soluc[k] = area; // k es el nº de voluntario

			// Marcar
			int kg = kilosPorAreaRestantes[area];
			int restante = kilosPorAreaRestantes[area] - kilosPorVoluntario[k][area];
			if (restante <= 0 )
			{
				sumaTotal += kilosPorAreaRestantes[area];
				kilosPorAreaRestantes[area] = 0;
				limpias++;
			}
			else
			{
				sumaTotal += kilosPorVoluntario[k][area];
				kilosPorAreaRestantes[area] -= kilosPorVoluntario[k][area];
			}

			/// Es solucion
			if (k == n - 1)
			{
				if (limpias >= l) 
				{
					if (sumaTotal > maxSuma) // es mejor
						maxSuma = sumaTotal;
				}
			}
			else if (sumaTotal + kilosDesde[k] > maxSuma) // PODA
			{
				resolver(soluc, k + 1, n, m, l, 
					kilosPorArea, kilosPorVoluntario, sumaTotal,
					limpias, maxSuma, kilosPorAreaRestantes, kilosDesde
				);
			}

			// Desmarcar
			if (restante <= 0)
			{
				limpias--;
				kilosPorAreaRestantes[area] = kg;
				sumaTotal -= kilosPorAreaRestantes[area];
			}
			else
			{
				sumaTotal -= kilosPorVoluntario[k][area];
				kilosPorAreaRestantes[area] += kilosPorVoluntario[k][area];
			}

			soluc[k] = -1;
		}
	}
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	// leer los datos de la entrada
	int n, m, l; // num voluntarios, numero de areas a limpiar >= 1, numero de areas minimas
	cin >> n >> m >> l;

	/// PRECALCULOS
	/// PARA PODA
	vector<int> kilosPorArea(m); // lodo en kilogramos por area
	for (int i = 0; i < m; ++i)
		cin >> kilosPorArea[i];

	vector<vector<int>> kilosPorVoluntario(n, vector<int>(m)); // kg que puede limpiar voluntario por area
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> kilosPorVoluntario[i][j];

	// Precalculos poda
	vector<int> kilosMax(n, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			kilosMax[i] = max(kilosMax[i], kilosPorVoluntario[i][j]);

	vector<int> kilosDesde(n, 0);
	kilosDesde[n - 1] = kilosMax[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		kilosDesde[i] += kilosDesde[i + 1];
		kilosDesde[i] += kilosMax[i];
	}
	
	vector<int> soluc(n, -1);
	int k = 0, maxSuma = 0;
	resolver(soluc, k, n, m, l, kilosPorArea, kilosPorVoluntario,
		0, 0, maxSuma, kilosPorArea, kilosDesde);
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
