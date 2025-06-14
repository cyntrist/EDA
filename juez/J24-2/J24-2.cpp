// Cynthia Tristán Álvarez
// EDA-GDV73

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// parametros:
// --- entrada
// soluc    -> vector solucion
// k        -> recorrer
// i de for -> +/-
// n        ->
// m        ->
// v        ->
// --- marcadores
// suma     -> 

// tupla sol: [0, 1, ..., 1] (sumar / restar)
// función que resuelve el problema
void resolver(std::vector<char>& soluc, int k, int n, const int m, 
	int suma, bool& r, std::vector<int>& v, std::vector<int>& sumaDesde)
{
	// ---- ESQUEMA DE BACKTRACKING ----

	// !!!! marcar en el mismo ambito en el que se desmarca

	// 1) for de candidatos     -> candidatos 
	// --- 2) guardar el indice del for que se va probando en el vect solucion
	// --- 3) if esValida       -> 
	// ------ 4) if esSolucion o llega al final  -> solo puedes comprobar la solucion si k == n - 1
	// --------- 5) if esMejor  -> 
	// ------ 6) else noSolucion
	// --------- 7) if poda     -> 
	// ------------ 8) llamada recursiva k+1

	// el primero siempre suma
	// k+1

	//for (int i = 0; i < 2; i++) // candidatos
	//{
	//	soluc[k] = i; // lo que voy a probar ahora
	//	// marcar
	//	if (i == 0) suma += v[k];
	//	else suma -= v[k];

	//	if ((k == 0 && i == 0) || k != 0) // es valida
	//	{
	//		if (k >= n - 1) // es solucion
	//		{
	//			if (suma == m) 
	//				r = true;
	//			return;
	//		}
	//		if (k == n - 2)
	//		{
	//			int optimista = 0;
	//			if (suma < m) 
	//				optimista = suma + v[k + 1];
	//			else 
	//				optimista = suma - v[k + 1];
	//			if (optimista == m) 
	//				resolver(soluc, k + 1, n, m, suma, r, v);
	//		}
	//		else
	//			resolver(soluc, k + 1, n, m, suma, r, v);
	//	}

	//	// desmarcar si no es sol
	//	if (i == 0) suma -= v[k];
	//	else suma += v[k];
	//}

	if (n == 0)
	{
		r = true;
		return;
	}

	soluc[k] = '+';
	suma += v[k];
	if (k == n - 1)
	{
		if (suma == m)
			r = true;
	}
	else
	{
		if (suma < m) // ahora mismo esta por debajo del objetivo (hay que sumar)
		{
			if ((suma + sumaDesde[k]) >= m) // si puede llegar o pasarse se continua si no no
				resolver(soluc, k + 1, n, m, suma, r, v, sumaDesde);
		}
		else // ahora mismo esta por encima del objetivo (hay que restar)
		{
			if (suma - sumaDesde[k] <= m) // si puede llegar o pasarse continua si no no
				resolver(soluc, k + 1, n, m, suma, r, v, sumaDesde);
		}
	}
	suma -= v[k];

	if (k > 0 && !r)
	{
		soluc[k] = '-';
		suma -= v[k];
		if (k == n - 1)
		{
			if (suma == m)
				r = true;
		}
		else
		{
			if (suma < m) // ahora mismo esta por debajo del objetivo (hay que sumar)
			{
				if ((suma + sumaDesde[k]) >= m) // si puede llegar o pasarse se continua si no no
					resolver(soluc, k + 1, n, m, suma, r, v, sumaDesde);
			}
			else // ahora mismo esta por encima del objetivo (hay que restar)
			{
				if (suma - sumaDesde[k] <= m) // si puede llegar o pasarse continua si no no
					resolver(soluc, k + 1, n, m, suma, r, v, sumaDesde);
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	int n = 0,
		m = 0;
	std::cin >> m >> n;
	std::vector<int> v(n);

	for (int i = 0; i < n; i++)
		std::cin >> v[i];

	std::vector<int>sumaDesde(n, 0);
	if (n > 1)
	{
		sumaDesde[n - 1] = v[n - 1];
		for (int i = n - 2; i >= 0; --i)
		{
			sumaDesde[i] += v[i];
			sumaDesde[i] += sumaDesde[i + 1];
		}
	}

	bool resuelto = false;
	std::vector<char> soluc(n);
	resolver(soluc, 0, n, m, 0, resuelto, v, sumaDesde);
	std::cout << (resuelto ? "SI" : "NO") << "\n";
}

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
	system("PAUSE");
#endif

	return 0;
}
