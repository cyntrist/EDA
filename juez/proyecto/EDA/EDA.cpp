#include <iostream>
#include <vector>
using namespace std;

// binary search
template <typename T>
bool memberOrd(const vector<T>& v, int ini, int fin, const T& e)
{
	int n = fin - ini;
	if (n < 2)
	{
		// caso base
		return (n == 0) ? false : (v[ini] == e);
	}
	int mit = (ini + fin) / 2;
	if (e < v[mit]) // esta a la izquierda
		return memberOrd(v, ini, mit, e);
	// esta a la derecha
	return memberOrd(v, mit, fin, e);
}


// subvector de suma maxima
vector<int> max_tuple(const vector<int>& a, const vector<int>& b, const vector<int>& c)
{
	if (a[0] >= b[0] && a[0] >= c[0])
		return a;
	if (b[0] >= a[0] && b[0] >= c[0])
		return b;
	return c;
}

vector<int> max_crossing_v0(const vector<int>& v, int ini, int fin, int mit)
{
	int sum = 0;
	int left_sum = 0;
	int max_left = mit;

	for (int i = mit - 1; i >= ini; --i)
	{
		sum += v[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	sum = 0;
	int right_sum = 0;
	int max_right = mit;

	for (int i = mit; i < fin; ++i)
	{
		sum += v[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = i; // +1 para incluir el elemento actual
		}
	}

	return {left_sum + right_sum, max_left, max_right};
}

vector<int> max_crossing(const vector<int>& v, int ini, int fin, int mit)
{
	// suponemos ini < mit < fin, luego fin - ini >= 2
	int max_left = mit - 1,
	    left_sum = v[mit - 1],
	    sum = v[mit - 1];

	for (int i = mit - 2; i >= ini; --i) // de la mitad hacia la izq
	{
		sum += v[i]; // actualiza el contador
		if (sum > left_sum)
		{
			left_sum = sum; // actualiza el contador especifico de la parte
			max_left = i; // actualiza el indice
		}
	}

	int max_right = mit + 1,
	    right_sum = v[mit];
	sum = v[mit];
	for (int j = mit + 1; j < fin; ++j)
	{
		sum += v[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = j + 1;
			// si v[j] se ha sumado, max_right debe ser j + 1
		}
	}

	return {left_sum + right_sum, max_left, max_right};
}


vector<int> max_subvector(const vector<int>& v, int ini, int fin)
{
	const int n = fin - ini;
	if (n == 0)
		return {0, ini, ini};
	if (n == 1)
		return {max(0, v[ini]), ini, fin};
	const int mit = (ini + fin) / 2;
	const auto l = max_subvector(v, ini, mit);
	const auto r = max_subvector(v, mit, fin);
	const auto cross = max_crossing(v, ini, fin, mit);
	return max_tuple(l, r, cross);
}

void print_max_sub()
{
	const vector<int> v = {1, -3, 2, 1, -1, 3, -2, 3, 0, 0, 0};
	auto result = max_subvector(v, 0, v.size());
	cout << "Maxima suma: " << result[0] << endl;
	cout << "Indice de inicio: " << result[1] << endl;
	cout << "Indice de fin: " << result[2] << endl;
}

template <typename T>
void merge(vector<T>& v, int p, int q, int r)
{
	// Suponemos p<=q<=r, v[p..q) y v[q..r) ordenados
	// Genera una mezcla ordenada de ambas partes en v[p.. r)
	auto nl = q - p,
	     nr = r - q;
	auto vl = vector<T>().reserve(nl), // memoria adicional
	     vr = vector<T>().reserve(nr);

	int i, j;
	for (i = 0; i < nl; i++) // copia de v[p..q) en vl[o..nl)
		vl[i] = v[p + i];
	for (j = 0; j < nr; j++) // copia de v[q..r) en vr[o..nr)
		vr[j] = v[q + j];
	i = 0, j = 0;

	for (int k = p; k < r; k++)
	{
		// mezclamos vl y vr en v
		if (j >= nr || (i < nl && vl[i] <= vr[j]))
		{
			// vr se ha agotado o vr y vl no agotados y vl[i] < vr[j]
			v[k] = vl[i];
			i += 1;
		}
		else
		{
			v[k] = vr[j];
			j += 1;
		}
	}

	// O(2n) = O(n)
}

template <typename T>
void mergesort(vector<T>& v, int ini, int fin)
{
	// no devuelve nada, solo ordena el vector
	if (ini < fin - 1) // longitud > 1
	{
		int mid = (ini + fin) / 2;
		mergesort(v, ini, mid);
		mergesort(v, mid, fin);
		merge(v, ini, mid, fin); // falta concretar
	} // si es de 1 elemento o menos, ya esta ordenado
	// merge tiene O(n) ---> mergesort tiene O(n * log n)
}

template <typename T>
int elige_pivote(vector<T>& v, int ini, int fin)
{
	return rand() % (fin - ini) + ini; // ? XD
}

template <typename T>
pair<int, int> partition(vector<T>& v, int pivote, int ini, int fin)
{
	// importante que su coste sea O(n) siendo n = fin - ini
	// Problema de la bandera holandesa − Edsger Dijkstra (este tio que conyo dice)
	// Reordena v[ini .. fin ) en 3 segmentos contiguos
	auto i = ini,
	     j = ini,
	     k = fin;
	// MENORES → [ini..i); IGUALES → [i..j)
	// MAYORES → [k..fin); SIN PROCESAR → [j..k)
	while (j < k)
	{
		if (v[j] < pivote)
		{
			swap(v, i, j);
			i += 1;
			j += 1;
		}
		else if (v[j] > pivote)
		{
			swap(v, j, k - 1);
			k -= 1;
		}
		else
			j += 1;
	}
}

template <typename T>
void quicksort(vector<T>& v, int ini, int fin)
{
	if (ini < fin - 1) // longitud > 1
	{
		auto pivote = elige_pivote(v, ini, fin); // supuesta funcion O(1)
		auto par = partition(v, pivote, ini, fin);
		quicksort(v, ini, par.first);
		quicksort(v, par.second, fin);
	}
}

int main()
{
	print_max_sub();
	return 0;
}
