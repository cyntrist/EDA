// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"

// que recibe un entero pivote y reorganiza los nodos dinámicos de la lista enlazada de tal forma
// que al principio aparezcan aquellos que contengan enteros menores o iguales que el pivote y
// al ￿final aparezcan los que contengan enteros mayores que el pivote.
template <class T>
class list_eda_plus : public list<T>
{
    using Nodo = typename list<T>::Nodo;
public:
    void partition(int pivote)
    {
        if (!this->empty() &&  this->nelems > 1)
        {
            Nodo* act = this->fantasma->sig; // primer nodo de la lista
            Nodo* antAct = act->ant;
            Nodo* sigAct = act->sig;
            Nodo* last = this->fantasma->ant;

            for (int i = 0; i < this->size(); i++)
            {
                if (act->elem > pivote && act != last)
                {
                    act->sig = this->fantasma;
                    act->ant = this->fantasma->ant;

                    antAct->sig = sigAct;
                    sigAct->ant = antAct;

                    this->fantasma->ant = act;
                    act->ant->sig = act;
                }

                act = sigAct;
                sigAct = act->sig;
                antAct = act->ant;
                last = this->fantasma->ant;
            }
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n = 0;
    std::cin >> n;
    if (!std::cin)
        return false;

    int pivote = 0;
    std::cin >> pivote;

    int m = 0;
    list_eda_plus<int> list;
    for (int i = 0; i < n; i++)
    {
        std::cin >> m;
        list.push_back(m);
    }

	list.partition(pivote);
    for (const auto& i : list)
        std::cout << i << " ";
    std::cout << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
