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
	// Mueve al elemento b de su posicion a la posicion inmediatamente detras del elemento a
	// => En caso de haber multiples apariciones de los elementos a y/o b se consideraran:
	//      - La primera aparicion de a, y la primera aparicion de b tras la primera aparicion de a
	// Si alguno de los elementos no se encuentra en la cola, si b no aparece detras de a -> No se hace nada
	// Requisitos: No se puede crear ni destruir memoria dinamica, ni tampoco modificar los valores almacenados en la cola.
	// Coste:
	void cuela(const T& a, const T& b)
	{
		// Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult
		if (this->empty()) return;

		Nodo* actA = this->prim;
		while (actA != this->ult && actA->elem != a) // buscar A
			actA = actA->sig;
		if (actA == this->ult || actA->elem != a)
			return; // si has encontrado A

		Nodo* actB = actA->sig;
		bool ultimo = false;
		while (actB != this->ult && actB->elem != b) // buscar B -> buscar a partir de a
			actB = actB->sig;
		if (actB->elem != b) return; // si has encontrado B
		if (actB == this->ult)
			ultimo = true;


		Nodo* sigB = actA->sig; // siguiente a a
		Nodo* sigAntB = nullptr; // siguiente a b
		if (!ultimo)
			sigAntB = actB->sig;
		Nodo* antB = actA->sig; // encontrar anterior a b
		while (antB != this->ult && antB->sig != actB)
			antB = antB->sig;

		actA->sig = actB; // el siguiente de a es b
		actB->sig = sigB; // el siguiente a b es el antiguo siguiente de aç
		if (!ultimo)
			antB->sig = sigAntB; // y el siguiente al antiguo anterior de b es el siguiente a b

		if (ultimo)
			this->ult = antB;
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada
	int n, a, b;
	queue_plus<int> q;
	cin >> n;
	if (n == -1) return false;
	while (n != -1)
	{
		q.push(n);
		cin >> n;
	}
	cin >> a >> b;

	// llamada a metodo
	q.cuela(a, b);

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
	std::ifstream in("input.txt");
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
