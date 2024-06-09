
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v){
    for (auto e : v) out << e << " ";
    return out;
}

struct Vector2D {
    int x = 0; int y = 0;
    Vector2D operator+(const Vector2D& v) const { return {x + v.x, y + v.y}; }
};
using Point2D = Vector2D;

std::ostream& operator<<(std::ostream& os, const Vector2D &v) {
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

using Mapa = vector<vector<bool>>; // Se representa por filas


void printSolucion(vector<Point2D> const& sol, int k){
    for (int i = 0; i <= k; ++i)
        cout << sol[i] << " ";
    cout << endl;
}

const int NUM_DIRS = 4;
//enum Direccion {Dcha, Abajo, Izqda, Arriba}; // No parece servir para nada
const array<Point2D, NUM_DIRS> DIRS = {{{1,0}, {0,1}, {-1,0}, {0,-1}}}; // Dcha, Abajo, Izqda, Arriba

bool esValida(Point2D const& pos, Mapa const& muros, Mapa& visitadas) {
    return (pos.x >= 0 && pos.x < muros.size() && pos.y >= 0 && pos.y < muros.size() &&
            !muros[pos.y][pos.x] && !visitadas[pos.y][pos.x]);
}

// Algoritmo backtracking que encuentra e imprime todas las soluciones
void laberinto(vector<Point2D>& soluc, int n, int k, Mapa const& muros, Mapa& visitadas){
    for (int d = 0; d < NUM_DIRS; ++d){
        Point2D pos = soluc[k-1] + DIRS[d];
        soluc[k] = pos;
        if (esValida(pos, muros, visitadas)){
            if (pos.x == n-1 && pos.y == n-1) {
                printSolucion(soluc,k);
            } else {
                visitadas[pos.y][pos.x] = true;
                laberinto(soluc, n, k+1, muros, visitadas);
                visitadas[pos.y][pos.x] = false;
            }
        }
    }
}

// Algoritmo backtracking que encuentra e imprime la primera solución
void laberintoPrim(vector<Point2D>& soluc, int n, int k, Mapa const& muros, Mapa& visitadas, bool& fin){
    for (int d = 0; d < NUM_DIRS && !fin; ++d){
        Point2D pos = soluc[k-1] + DIRS[d];
        soluc[k] = pos;
        if (esValida(pos, muros, visitadas)){
            if (pos.x == n-1 && pos.y == n-1) {
                printSolucion(soluc,k);
                fin = true;
            } else {
                visitadas[pos.y][pos.x] = true;
                laberintoPrim(soluc, n, k+1, muros, visitadas, fin);
                //visitadas[pos.y][pos.x] = false; // En este caso no es necesario desmarcar
            }
        }
    }
}


// Algoritmo backtracking que encuentra y devuelve la mejor solución
void laberintoOpt(vector<Point2D>& soluc, int n, int k, Mapa const& muros, Mapa& visitadas,
                  int& mejorLong, vector<Point2D>& mejorSol){
    for (int d = 0; d < NUM_DIRS; ++d){
        Point2D pos = soluc[k-1] + DIRS[d];
        soluc[k] = pos;
        if (esValida(pos, muros, visitadas)){
            if (pos.x == n-1 && pos.y == n-1) {
                //printSolucion(soluc,k);
                if (k < mejorLong) {
                    mejorLong = k;
                    mejorSol.resize(k + 1);
                    copy(soluc.begin(), soluc.begin() + k + 1, mejorSol.begin());
                }
            } else {
                int estimacionOptimista = (n-1-pos.x) + (n-1-pos.y); // Longitud de camino minimo sin muros
                if (k + estimacionOptimista < mejorLong) { // Poda por estimación: Si el mejor camino (sin muros) desde donde estoy no es mas corto que el de mejorSol dejo de explorar
                    visitadas[pos.y][pos.x] = true;
                    laberintoOpt(soluc, n, k + 1, muros, visitadas, mejorLong, mejorSol);
                    visitadas[pos.y][pos.x] = false;
                }
            }
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    Mapa muros(n,vector<bool>(n)); // Se lee fila a fila
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int muro; cin >> muro; muros[i][j] = muro;
        }
    Mapa visitadas(n,vector<bool>(n,false));
    vector<Point2D> soluc(n*n); // Formato (x,y) = (columna,fila)
    soluc[0] = {0,0};
    visitadas[0][0] = true;
    //laberinto(soluc,n,1,muros,visitadas);
    //bool fin = false;
    //laberintoPrim(soluc,n,1,muros,visitadas, fin);
    vector<Point2D> mejorSol;
    int mejorLong = n*n;
    laberintoOpt(soluc,n,1,muros,visitadas,mejorLong,mejorSol);
    cout << mejorSol;
    return true;
}

/* Fichero con laberinto de ejemplo (0=libre, 1=muro)
5
0 0 0 0 0
0 1 1 1 0
0 1 0 0 0
0 0 0 1 0
0 0 0 1 0
0
 */

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("../Tema3/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}