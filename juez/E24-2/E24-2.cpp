// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//*******************************
// Explicacion del algoritmo empleado
// Coste del algoritmo. Incluye recurrencia y desplegado de la recurrencia
//
// Y no olvides poner comentarios en el codigo
//*******************************

// Coste: O()
// v1 ascendente v2 descendente
bool corte(const std::vector<int>& v1, const std::vector<int>& v2, std::pair<int, int>& punto, int ini, int fin)
{
	int n = fin - ini;
	int mit = (ini + fin) / 2;

	//caso base
	//se cortan
	if (n == 1)
	{
		if (v1[ini] == v2[ini])
		{
			punto = { ini, -1 };
			return true;
		}
		if (v1[ini] > v2[ini])
		{
			punto = { -1, 0};
		}
		else
		{
			punto = { ini, fin };
		}

		return false;
	}

	if (v1[mit] == v2[mit])
	{
		punto = {mit, -1};
		return true;
	}

	//corte izq
	if (v1[mit] > v2[mit])
	{
		return corte(v1, v2, punto, ini, mit);
	}

	//corte der
	if (v2[mit] > v1[mit])
	{
		return corte(v1, v2, punto, mit, fin);
	}

	return false;
}

bool resuelveCaso()
{
	int numElem;
	std::cin >> numElem;
	if (numElem == 0) return false;
	std::vector<int> v1(numElem);
	std::vector<int> v2(numElem);
	for (int& i : v1) std::cin >> i;
	for (int& i : v2) std::cin >> i;

	// funcion
	std::pair<int, int> punto(-1, 0);
	bool resultado = corte(v1, v2, punto, 0, numElem);

	// salida
	std::cout << (resultado ? "SI " : "NO ")
		<< punto.first << " "
		<< (!resultado ? std::to_string(punto.second) : "")
		<< "\n";

	return true;
}

int main()
{
#ifndef DOMJUDGE
	std::ifstream in("input.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
