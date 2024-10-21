// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;


template <class T>
class queue_plus : public queue<T>
{
	using Nodo = typename queue<T>::Nodo;

public:
	void cuela(const T& a, queue<T>& b)
	{
		// Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult

		if (this->empty()) return;
		if (b.empty()) return;

		Nodo* actual = this->prim;
		Nodo* siguiente = actual->sig;

		Nodo* actual2 = b->prim; // esto esta mal
		Nodo* siguiente2 = actual2->sig;

		while (actual != nullptr)
		{
			if (actual->elem == a)
			{	// colar // nada de news ni delete
				while (actual2 != nullptr)
				{
					
				}
			}
			// seguir igualmente 
			actual = siguiente;
			siguiente = actual->sig;
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada
	int n, a;
	queue_plus<int> q;
	queue_plus<int> c; // colegas
	cin >> n;
	if (n == -1) return false;
	while (n != -1)
	{
		q.push(n);
		cin >> n;
	}
	cin >> a;
	while (n != -1)
	{
		c.push(n);
		cin >> n;
	}

	// llamada a metodo
	q.cuela(a, c);

	// escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
	for (int i = 0; i < q.size(); ++i)
	{
		n = q.front();
		q.pop();
		q.push(n);
	}
	// Ahora imprimimos la cola y de paso la dejamos vacía
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	return true;
}

//#define DOMJUDGE
int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}
