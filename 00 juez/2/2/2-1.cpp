// Nombre del alumno ..... Cynthia Tristán Álvarez
// Usuario del Juez ...... VJ62

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// T(n) = O(n)

// función que resuelve el problema
int complementario(const int& num) { // calcula el complementario
    if (num < 10)
	    return 9 - num;
    return complementario(num/10) * 10 + (9 - num % 10);
}

int inverso(const int& num, const int& inv) // invierte el sentido de un int
{
	if (num == 0) 
        return inv;
	return inverso(num / 10, inv * 10 + num % 10);
}

int primerDigito(const int& n)
{
    if (n < 10) 
        return n;
    return primerDigito(n/10);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    if (!std::cin)
        return false;

    int num = 0;
    cin >> num;
    const int resp = complementario(num);
    if (primerDigito(num) == 9) // caso especial si empieza con 9
        cout << resp << " " << inverso(resp, 0) << "0" << endl;
    else
    	cout << resp << " " << inverso(resp, 0) << endl;
    return true;
}

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
     system("PAUSE");
     #endif
    
    return 0;
}