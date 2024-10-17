// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>


// función que resuelve el problema
// O(2n) = O(n) siendo n el tamaño de la pila
void resolver(std::stack<int>& pila) {
    std::stack<int> aux;

    while(!pila.empty())
    {
        aux.push(pila.top());
	    pila.pop();
    }

    while (!aux.empty())
    {
	    pila.push(aux.top());
	    pila.push(aux.top());
        aux.pop();
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n = 0;
    std::cin >> n;
    if (! std::cin)
        return false;

    std::stack<int> pila;
	while (n != 0) {
		pila.push(n);
		std::cin >> n;
	}

	resolver(pila); 

	//// escribir sol (pero antes dar una vuelta para comprobar que la pila está bien formada)
	//for (int i = 0; i < pila.size(); ++i) {
	//	n = pila.top();
	//	pila.pop();
	//	pila.push(n);
	//}
	// ahora imprimimos la cola y de paso la dejamos vacía
	while (!pila.empty()) {
		std::cout << pila.top() << " ";
		pila.pop();
	}
    std::cout << std::endl;
    
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
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