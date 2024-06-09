// Tema 1: Complejidad algoritmos

template <class T>
bool search(vector<T> const& v, T const& x) {
  int i = 0;
  while (i < v.size() && v[i] != x) {
    ++i;
  }
  return i < v.size();
}


// Ejemplos (algoritmos vistos en FP2: búsquedas y algoritmos de ordenación)

// Búsqueda lineal en C# (algoritmo visto en FP2 el curso pasado)
static bool busquedaLineal(int[] v, int e){
    int n = v.Length;
    int i = 0;
    while (i < n && v[i] != e){
        i++;
    }
    return i < n;
}

/*
Caso peor (e no está en v o es el último)
    
    Nº de iteraciones: n=v.Length
    Podríamos contar número exacto de instrucciones pero no es muy útil
	O(n), con n = v.Length

Caso mejor (v[0]=e)
    Nº de iteraciones: 1
	O(1)  
*/


// Búsqueda binaria en C# (algoritmo visto en FP2 el curso pasado)
static bool busquedaBinaria(int[] v, int e){
    int ini = 0, n = v.Length−1;
    bool enc = false;
    while (ini<=n && !enc){
        int med = (ini + n) / 2;
        if (e < v[med])
            n = med−1;
        else if (e > v[med])
            ini = med+1;
        else
            enc = true;
    }
    return enc;
}

// Caso mejor: v[v.Length−1] == e  -> O(1)

// Caso peor: e no pertenece a v
// O(log n), siendo n = v.Length


//Ordenación por inserción en C# (algoritmo visto en FP2 el curso pasado)
static void insercion(int[] v){
    int n = v.Length; // número de eltos del vector
    // v[0] ya está ordenado, para cada uno desde 1 hasta n:
    for (int i=1; i<n; i++){ // inv: v [0..i−1] está ordenado
        // insertamos v[i] ordenadamente en el subvector v[0..i−1]
        int tmp = v[i]; // guardamos v[i]
        int j = i−1; // desplazamos eltos a la dcha abriendo hueco para v[i]
        while ((j>=0) && (v[j]>tmp)) {
            v[j+1] = v[j];
            j−−;
        }
    }
}

/*
Caso peor (v ordenado al revés):

Nº iteraciones bucle interno:
1 + 2 + 3 + 4 + ... + (N - 1) -> Suma de serie aritmética = n(a1 + an)/2 
(N - 1)*(1 + (N - 1)) / 2 =
N * (N - 1) / 2 = (N^2 - N) / 2 

Crece en el orden de N^2 (N cuadrado). O(N*N), siendo N = v.Length

Caso mejor (v ordenado): Nº iteraciones = n-1
O(N), siendo N = v.Length
*/


//Ordenación por selección en C# (algoritmo visto en FP2 el curso pasado)

static void seleccion(int[] v){
    int n = v.Length; // num de eltos del vector
    // en cada posición i=0..n−1 ponemos el menor de v[i..n−1]
    // vamos hasta i=n−2 porque al final v[n−1] ya está en su sitio
    for (int i=0; i<n−1; i++){
        // inv: el subarray 0..i−1 está ordenado
        // buscamos el menor en v[i..n)
        int min = i;
        for (int j = i+1; j < n; j++)
            if (v[j] < v[min]) // con menor estricto es estable
                min = j;
        // ponemos el menor en v[i] y v[i] en la pos del menor
        swap(ref v[i], ref v[min]);
    }
}

/*

Trabaja lo mismo en todos los casos
nº iteraciones: (N - 1) + (N - 2) + (N - 3) + ... + 3 + 2 + 1 =

Crece en el orden de N^2.  
O(N*N), siendo N = v.Length
*/


//Ordenación burbuja en C# (algoritmo visto en FP2 el curso pasado)

static void burbujaMejorado(int[] v){
    int n = v.Length;
    bool cont = true; // control de parada
    int i = 0; // ahora el for es un while con "cont" en la condición de parada
    while (i<n−1 && cont) {
        cont = false; // control de intercambio, inicialmente false
        for (int j=n−1; j>i; j−−)
            if (v[j−1]>v[j]) {
                swap(ref v[j−1],ref v[j]);
                // si hay intercambio cont a true
                cont = true;
            }
        i++;
    }
}

// Complejidad análoga a la ordenación por inserción




// Ejempos de uso de vector
int main(){
	int n, e;
	cin >> n;
	vector<int> v(n,0);
	for (int i = 0; i < n; i++){
		//cin >> e;
		//v[i] = e;
		cin >> v[i]; // Mejor así
	}
	
	// Forma equivalente y más cómoda
	for (int& e : v) cin >> e;
	
	// Impresión de vector
	for (int e : v) cout << e << " ";
}

