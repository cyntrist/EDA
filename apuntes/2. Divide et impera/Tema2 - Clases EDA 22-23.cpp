#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Factorial. Versión no-final devolviendo por return
int fact(int n) {
    if (n == 0) return 1;
    return fact(n-1)*n;
}

// Factorial. Versión no-final pero devolviendo resultado por parámetro de salida
void factParam(int n, int& res){
    if (n == 0) res = 1;
    else {
        int resAux;
        factParam(n-1,resAux);
        res = resAux*n;
    }
}

// Factorial. Versión final devolviendo resultado por return
int factFin(int n, int ac){
    if (n == 0) return ac;
    return factFin(n-1,ac*n);
}

// Función principal para llamar a la anterior
int fact2(int n){
    int ac = 1;
    return factFin(n,ac);
}

// Factorial. Versión final dejando el resultado final en el propio acumulador
void factAc(int n, int& ac){
    if (n == 0) return ;
    else {
        ac = n*ac;
        factAc(n-1,ac);
    }
}

// Función principal para llamar a la anterior
int fact3(int n){
    int ac = 1;
    factAc(n,ac);
    return ac;
}


// Suma de elementos de un vector. Versión iterativa
int sumaIt(const vector<int>& v){
    int r = 0;
    for (int e : v) r += e;
    return r;
}

// Suma de elementos de un vector. Versión recursiva por sustracción
int sumaRec(const vector<int>& v, int ini, int fin){
    int n = fin-ini;
    if (n == 0) return 0;
    return v[ini] + sumaRec(v,ini+1,fin);
}

// Suma de elementos de un vector. Versión recursiva restando por ambos lados
int sumaRec2(const vector<int>& v, int ini, int fin){
    int n = fin-ini;
    if (n == 0) return 0;
    else if (n == 1) return v[ini]; // En este caso sí que es necesario (cuando longitud impar)
    return v[ini] + v[fin-1] + sumaRec2(v,ini+1,fin-1);
}

// Suma de elementos de un vector. Versión recursiva por división (Divide y Vencerás)
int sumaDyV(const vector<int>& v, int ini, int fin){
    int n = fin-ini;
    if (n == 0) return 0;
    else if (n == 1) return v[ini];
    else {
        int mitad = (ini + fin) / 2;
        int mitadIz, mitadDr;
        mitadIz = sumaDyV(v, ini, mitad);
        mitadDr = sumaDyV(v, mitad, fin);
        return mitadIz + mitadDr;
    }
}

// Función principal para llamar a las anteriores
int suma(const vector<int>& v){
    return sumaDyV(v,0,v.size());
}

void resuelveCasoFact() {
    // resuelve caso para el factorial
    int n, res;
    cin >> n;
    cout << fact(n) << endl;
    factParam(n,res);
    cout << res << endl;
    cout << fact2(n) << endl;
    cout << fact3(n) << endl;
}

void sumaDivAc(vector<int> const& v, int ini, int fin, int& ac){
    int n = fin-ini;
    if (n == 0) true;
    else if (n == 1) ac += v[ini];
    else {
        int mitad = (ini+fin)/2;
        sumaDivAc(v,ini,mitad,ac);
        sumaDivAc(v,mitad,fin,ac);
    }
}

int suma(vector<int> const& v){
    int res = 0;
    sumaDivAc(v,0,v.size(),res);
    return res;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& e : v) cin >> e;
    //for (int i = 0 ; i < n; i++)
    //    cin >> v[i];
    cout << suma(v) << endl;
}

void resuelveCasoAlt() {
    // Versión alternativa que usaríamos si los vectores viniesen acabados con -1 y sin saber apriori su número de elementos
    // leer los datos de la entrada
    vector<int> v;
    int e;
    cin >> e;
    while (e != -1){
        v.push_back(e);
        cin >> e;
    }
    cout << suma(v) << endl;
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
        //resuelveCasoFact();
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}



int fib(int n){
    if (n == 0) return 1;
    if (n == 1) return 1;
    return fib(n-1) + fib(n-2);
}

bool member(vector<int> const& v, int ini, int fin, int e){
    int n = fin-ini; 
    if (n == 0) return false;
    else {
        return ((v[ini] == e) || member(v,ini+1,fin,e));
    }
}


bool memberDiv(vector<int> const& v, int ini, int fin, int e){
    int n = fin-ini; 
    if (n == 0) return false;
    if (n == 1) return v[ini] == e;
    else {
        int mitad = ...
        bool estaIzq = memberDiv(v,ini,mitad,e);
        bool estaDer = memberDiv(v,mitad,fin,e);
        return (estaIzq || estaDer);
    }
}


bool memberOrd(vector<int> const& v, int ini, int fin, int e){
    int n = fin-ini; 
    if (n == 0) return false;
    if (n == 1) return v[ini] == e;
    else {
        int mitad = ...
        if (e < v[mitad]) return memberOrd(v,ini,mitad,e);
        else return memberOrd(v,mitad,fin,e);
    }
}




void sort(vector<int>& v){
    sort(v,0,v.size());
}

void sort(vector<int>& v, int ini, int fin){
    int n = fin-ini;
    if (n > 1){
        int mitad = ...
        sort(v,ini,mitad);
        sort(v,mitad,fin);
        merge(...);
    }
}


bool parcialmenteOrdenado(vector<int>& const v, int ini, int fin, int& min, int& max) {
    int n = ...
        if (n == 1) {
            min = v[ini]; ...
            return true;
        }
    bool ordIz, ordDr;
    int mitad = ...
    int minIz, minDr, maxIz, maxDr;
    ordIz = parcialmenteOrdenado(v, ini, mitad, minIz, maxIz);
    ordDr = parcialmenteOrdenado(v, mitad, fin, minDr, MaxDr);
    min = min(minIz, minDr);
    max = max(maxIz, maxDr);
    return ordIz && ordDr && minIz <= minDr && maxDr >= maxIz;
}
