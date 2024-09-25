// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// T(n) = O(log n)

// función que resuelve el problema
int resolver(const vector<int>& v, int ini, int fin) {
    const int mitad = (ini + fin) / 2;
    const int n = fin - ini; // numero 

    if (n < 2) // si tiene un elemento
	    return ini;

    /* Segunda versión */
    if (mitad%2 == 0) // si las mitades son pares
    { 
        if (v[mitad] == v[mitad - 1]) // si la posicion mitad es igual al anterior
			fin = mitad;	       
        else  // si la posicion mitad no es igual a la anterior, mitad der
	        ini = mitad;
    } // si las mitades son impares
	else  
	{
		if (v[mitad] == v[mitad - 1]) // si la posicion mitad es igual al anterior
			ini = mitad;	        
        else  // si la posicion mitad no es igual a la anterior, mitad der
	        fin = mitad;
    }

    return resolver(v, ini, fin); // si la posicion mitad no es igual a la anterior, mitad izq
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& e : v) cin >> e;
    
    // Mostrar el resultado
    cout <<  resolver(v, 0, v.size()) << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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