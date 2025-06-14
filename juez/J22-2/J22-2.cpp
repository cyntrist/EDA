#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;

template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    // pos  -> primera posición del segmento a mover
    // lon  -> longitud del segmento
    // k    -> cantidad de posiciones a adelantar
    //  Si la posicion de origen o destino del segmento no es valida (lo que incluye el caso de la lista vacıa),
    //  o si lon = 0 o k = 0, la operacion no tendra efecto (ver cuarto caso).
    //  Si el segmento se sale de la lista, es decir, si pos + lon > n,
    //  se tomara el segmento de los ultimos n − pos elementos (ver segundo caso)
    void adelantar(int pos, int lon, int k)
    {
        if (this->empty() 
            || k == 0 
            || lon == 0 
            || k > pos 
            || k >= this->size() 
            || pos >= this->size() 
            || pos - k < 0)
            return;

        if (pos + lon > this->size())
            lon = this->size() - pos;

        Nodo* antDest = this->fantasma;
        Nodo* antSeg = this->fantasma->sig;
        Nodo* ultSeg = this->fantasma->sig;
        int posAntK = pos - k;
        int i = 0;

        while (i < this->size())
        {
            if (i < posAntK) // anterior al destino
                antDest = antDest->sig;
            if (i < pos - 1) // anterior al segmetno
                antSeg = antSeg->sig;
            if (i < pos + lon - 1) // ultimo del segmento
                ultSeg = ultSeg->sig;
            ++i;
        }
        
        Nodo* sigDest = antDest->sig; // siguiente a la pos destino
        Nodo* priSeg = antSeg->sig; // el inicio del segmento
        Nodo* sigSeg = ultSeg->sig; // siguiente al ultimo del segmento

        antDest->sig = priSeg;
        priSeg->ant = antDest;

        sigDest->ant = ultSeg;
        ultSeg->sig = sigDest;

        antSeg->sig = sigSeg;
        sigSeg->ant = antSeg;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, lon, k;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> lon >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, lon, k);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i) {
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;
}

//#define DOMJUDGE
int main() {
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

