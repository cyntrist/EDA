// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
bool resolver(std::vector<int> datos) {
    int n = datos.size();
    int i = 0, j = 0, k = 0;

    while (i < n - 1) // porque accedemos al siguiente dentro del bucle 
    {
	    if (datos[i] < datos[i + 1])
			j++;
        else if (datos[i] > datos[i + 1])
            k++;
    	i++;
    }

    return k == i || j == i;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n = 0;
    std::cin >> n;
    if (n < 1)
        return false;

    std::vector<int> datos(n);
    for (int i = 0; i < n; i++)
        std::cin >> datos[i];

    if (resolver(datos))
        std::cout << "DALTON" << std::endl;
    else
        std::cout << "DESCONOCIDOS" << std::endl;

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