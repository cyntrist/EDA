/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <map>
#include <vector>
#include <utility>

using namespace std;
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

//using Heroe = string;
//using Villano = string;

/*
Debemos simular un sistema de batallas por turnos entre héroes y villanos para un video-
juego. Cuando un héroe o un villano aparecen en la batalla, tienen que esperar a que todos los
personajes que estuvieran presentes anteriormente en la batalla ataquen. El personaje al que le
toca el turno, ya sea héroe o villano, realiza un ataque y vuelve a esperar su turno para volver a
atacar. Si el ataque derrota al adversario, éste desaparece de￿nitivamente de la batalla. Los villa-
nos tienen un nombre, una determinada cantidad de puntos de vida y un valor de daño al atacar.
Los héroes, por otro lado, además de su nombre y sus puntos de vida, tienen una lista de ataques
que van aprendiendo a lo largo de la batalla, cada uno con su valor de daño correspondiente. El
nombre de cada personaje es único, es decir, no puede existir un villano y un héroe con el mismo
nombre.
*/

using HeroeNombre = string;
using VillanoNombre = string;
using Vida = int;
using Daño = int;
using Ataque = string;
using Ataques = map<Ataque, Daño>;
using Turno = int;
using Contador = int;

struct Heroe
{
    HeroeNombre nombre;
    Vida vida;
    Turno turno;
    Ataques ataques;
};

struct Villano
{
    VillanoNombre nombre;
    Vida vida;
    Daño daño;
    Turno turno;
};

using Heroes = std::map<string, Heroe>;
using Villanos = std::map<string, Villano>;

class SistemaBatallas {
    Heroes heroes;
    Villanos villanos;
    Contador entidades = 0;

public:
    // Registra el nuevo villano v en la batalla con s puntos de vida y valor
    // de ataque a. Si el villano no había aparecido en la batalla, se registra.
    // Si el personaje ya había aparecido anteriormente en la batalla, se lanza
    // una excepción del tipo invalid_argument con el mensaje Personaje ya existente.
    // Coste: O(log n) 
    void aparece_villano(VillanoNombre const& v, int puntos, int valor) {
   //     // comprobar si esta ya
   //     size_t i = 0;
   //     while (villanos[i].nombre != v) i++;    
   //     if (i != villanos.size())
			//throw invalid_argument("Personaje ya existente");
   //     // registrarlo
   //     villanos.push_back({ v, puntos, valor }); // complejidad constante amortizada
        const auto search = villanos.find(v);
        if (search != villanos.end())
            throw invalid_argument("Personaje ya existente");

        entidades++;
        auto villano = { v, puntos, valor, entidades };
        villanos.insert(villano);
    }

    // Registra el nuevo héroe h en la batalla con s puntos de vida. Si el héroe
    // no había aparecido en la batalla, se registra. Si el personaje ya había aparecido
    // anteriormente en la batalla, se lanza una excepción del tipo invalid_argument
    // con el mensaje Personaje ya existente.
    // Coste: O(log n)
    void aparece_heroe(HeroeNombre const& h, int puntos){
        //size_t i = 0;
        //while (heroes[i].nombre != h) i++;
        //if (i != heroes.size())
        //    throw invalid_argument("Personaje ya existente");
        //throw invalid_argument("Personaje ya existente");

        const auto search = heroes.find(h);
        if (search != heroes.end())
            throw invalid_argument("Personaje ya existente");

        entidades++;
        heroes.insert({ h, { h, puntos, entidades }});
    }

    //  Añade el ataque a con daño v a la lista de ataques del héroe h.
    //  Si el héroe no está en la batalla, se lanza una excepción del tipo invalid_argument con el mensaje Heroe inexistente.
    //  Si el héroe conoce ya ese ataque, se lanza una excepción del tipo invalid_argument con el mensaje Ataque repetido.
    // Coste: (log n)
    void aprende_ataque(HeroeNombre const& h, string const& ataque, int valor){
        const auto heroSearch = heroes.find(h);
        if (heroSearch == heroes.end())
			throw invalid_argument("Heroe inexistente");

        const auto attackSearch = heroSearch->second.ataques.find(ataque);
        if (attackSearch != heroSearch->second.ataques.end())
			throw invalid_argument("Ataque repetido");

        heroSearch->second.ataques.insert({ ataque, valor });
    }

    // Devuelve un vector de pares (nombre, daño) ordenadados lexicográ￿cament con aquellos ataques aprendidos por el héroe h.
    // Si el héroe no está registrado, se lanza una excepción del tipo invalid_argument con el mensaje Heroe inexistente.
    // Coste: O(n)
    vector<pair<string,int>> mostrar_ataques(HeroeNombre const& h){
        const auto heroSearch = heroes.find(h);
        if (heroSearch == heroes.end())
			throw invalid_argument("Heroe inexistente");

        auto it = heroSearch->second.ataques.begin();
    	vector<pair<string,int>> res;

        while (it != heroSearch->second.ataques.end())
        {
            res.emplace_back(it->first, it->second);
            ++it;
        }
        
        return res;
    }

    //  Devuelve un vector de pares con el nombre de todos los héroes y villanos
    //  acompañados de su cantidad correspondiente de puntos de vida, ordenados según su turno.
    //  Coste:
    vector<pair<string,int>> mostrar_turnos(){
        vector<pair<string,int>> res;



        return res;
    }

    //  El villano v ataca al héroe h, restándole a los puntos de vida del héroe el valor de daño de v.
    //  Tras el ataque, v vuelve a pedir turno cuando corresponda.Si el villano o el héroe no están registrados,
    //  se lanza una excepción con el mensaje Villano inexistente y Heroe inexistente, respectivamente.
    //  Si no es el turno del villano pasado como parámetro, se lanza una excepción con el mensaje No es su turno.
    //  Si el héroe atacado es derrotado, es decir, pierde todos sus puntos de vida, desaparece completamente
    //  de la batalla y la función devuelve el valor cierto.
    // Coste:
    bool villano_ataca(VillanoNombre const& v, HeroeNombre const& h){
        ...
        throw invalid_argument("Villano inexistente");
        ...
        throw invalid_argument("Heroe inexistente");
        ...
        throw invalid_argument("No es su turno");
        ...
    }

    //  El héroe h ataca al villano v, restándole a los puntos de vida del villano el valor de daño del ataque a.
    //  Tras el ataque, h vuelve a pedir turno cuando corresponda.Si el villano o el héroe no están registrados,
    //  se lanza una excepción con el mensaje Villano inexistente y Heroe inexistente, respectivamente.
    //  Si no es el turno del héroe pasado como parámetro, se lanza una excepción con el mensaje No es su turno.
    //  Si el héroe h no conoce el ataque a, se lanza una excepción con el mensaje Ataque no aprendido.
    //  Si el villano atacado es derrotado, desaparece completamente de la batalla y la función devuelve el valor cierto.
    // Coste:
    bool heroe_ataca(HeroeNombre const& h, string const& ataque, VillanoNombre const& v){
        ...
        throw invalid_argument("Villano inexistente");
        ...
        throw invalid_argument("Heroe inexistente");
        ...
        throw invalid_argument("No es su turno");
        ...
        throw invalid_argument("Ataque no aprendido");
        ...
    }

};


bool resuelveCaso() { // No tacar nada de esta función!
    string comando;
    cin >> comando;
    if (!cin) return false;

    SistemaBatallas sistema;
    VillanoNombre v; HeroeNombre h; 
    string ataque; int ptos; int valor;
    while (comando != "FIN") {
        try {
            if (comando == "aparece_villano") {
                cin >> v >> ptos >> valor;
                sistema.aparece_villano(v, ptos, valor);
            } else if (comando == "aparece_heroe") {
                cin >> h >> ptos;
                sistema.aparece_heroe(h, ptos);
            } else if (comando == "aprende_ataque") {
                cin >> h >> ataque >> valor;
                sistema.aprende_ataque(h, ataque, valor);
            } else if (comando == "mostrar_ataques") {
                cin >> h;
                auto ataques = sistema.mostrar_ataques(h);
                cout << "Ataques de " << h << endl;
                for (auto& [ataque,valor] : ataques) {
                    cout << ataque << " " << valor << "\n";
                }
            } else if (comando == "mostrar_turnos") {
                cout << "Turno: " << endl;
                auto turnos = sistema.mostrar_turnos();
                for (auto &[pers, puntos] : turnos) {
                    cout << pers << " " << puntos << "\n";
                }
            } else if (comando == "villano_ataca") {
                cin >> v >> h;
                bool derrotado = sistema.villano_ataca(v, h);
                cout << v << " ataca a " << h << endl;
                if (derrotado) cout << h << " derrotado" << endl;
            } else if (comando == "heroe_ataca") {
                cin >> h >> ataque >> v;
                bool derrotado = sistema.heroe_ataca(h, ataque, v);
                cout << h << " ataca a " << v << endl;
                if (derrotado) cout << v << " derrotado" << endl;
            }
        } catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(resuelveCaso()) { }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
