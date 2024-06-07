#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    void adelantar(int pos, int length, int dif) {
        if (pos < 0 || length < 1 || dif <= 0 || dif > this->nelems || pos - dif < 0)
            return;
        if (pos + length > this->nelems)
            length = this->nelems - pos;

        auto nuevo = this->fantasma;
        auto ini = nuevo;
        auto fin = nuevo;

		int i = 0;
		while (i < pos - dif) {
		   i++; 
		   nuevo = nuevo->sig;
		}
		ini = nuevo;
		while (i < pos) {
		    i++;
			ini = ini->sig;
		}
		fin = ini;
		while (i < pos + length && i < this->nelems) {
		    i++;
			fin=fin->sig;
		}

        auto auxNuevoSig = nuevo->sig;
    	nuevo->sig = ini->sig;
    	ini->sig = fin->sig;
    	fin->sig = auxNuevoSig;
        nuevo->sig->ant = nuevo;
        ini->sig->ant = ini;
        fin->sig->ant = fin;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, length, dif);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i){
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()){
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
    std::ifstream in("input1.txt");
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
