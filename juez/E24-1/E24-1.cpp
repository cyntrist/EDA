// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "bintree_eda.h"

// función que resuelve el problema
std::pair<std::string, int> resolver(const bintree<std::string>& tree)
{
	if (tree.empty())
        return { "Ninguno", 0 };

    if (tree.left().empty() && tree.right().empty())
        return { tree.root(), 1 };

    auto izq = resolver(tree.left());
    auto der = resolver(tree.right());

    std::string lider = "";
    if (izq.second > der.second)
        lider = izq.first; // lider es el de la izquierda
    else if (izq.second < der.second)
        lider = der.first; // lider es del de la derecha
    else // mismo n enanos
        lider = std::min(izq.first, der.first);

    int seguidores = izq.second + der.second;
    if (tree.root() == "Orcos")
        seguidores /= 2;
    if (seguidores <= 0)
        lider = "Ninguno";

    return { lider, seguidores };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    bintree<std::string> tree;

	tree = leerArbol((std::string)".");
    std::pair<std::string, int> sol = resolver(tree);

    // escribir sol
    std::cout << sol.first << " " << (sol.first == "Ninguno" ? "" : std::to_string(sol.second)) << "\n";
}

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
     system("PAUSE");
#endif
    
    return 0;
}
