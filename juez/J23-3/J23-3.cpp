#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <list>
#include <unordered_map>

using namespace std;


class Fecha
{
	int _dia, _mes, _anio;

public:
	Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a)
	{
	}

	int dia() const { return _dia; }
	int mes() const { return _mes; }
	int anio() const { return _anio; }

	bool operator<(Fecha const& other) const
	{
		return _anio < other._anio ||
			(_anio == other._anio && _mes < other._mes) ||
			(_anio == other._anio && _mes == other._mes && _dia < other._dia);
	}
};

inline std::istream& operator>>(std::istream& entrada, Fecha& h)
{
	int d, m, a;
	char c;
	std::cin >> d >> c >> m >> c >> a;
	h = Fecha(d, m, a);
	return entrada;
}

inline std::ostream& operator<<(std::ostream& salida, Fecha const& f)
{
	salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
	salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
	salida << std::setfill('0') << std::setw(2) << f.anio();
	return salida;
}

using Codigo = string;
using Cliente = string;
using Existencias = int;

using FechasExistencias = list<pair<Fecha, Existencias>>;
using ListaEspera = list<Cliente>;

struct InfoProducto
{
	ListaEspera listaEspera;
	FechasExistencias fechasExistencias;
	Existencias existencias;
};

using Productos = unordered_map<Codigo, InfoProducto>;

// Nos piden implementar un sistema para gestionar la adquisición y venta de productos por parte de una tienda.
// De vez en cuando la tienda recibe nuevos productos identi￿cados por un código (cadena sin espacios)
// y señalados con una fecha.

// Las unidades del producto adquirido se guardan en el almacén, salvo que haya clientes que hubieran intentado
// comprar ese determinado producto cuando no había existencias y se hubieran colocado en la lista de espera.
// En ese caso, los clientes son servidos en riguroso orden de llegada.

// También puede haber venta de productos en existencia.
// En ese caso, se venden siempre las unidades con una fecha menor.
class Tienda
{
private:
	Productos productos;

public:
	//Tienda() { productos.clear(); }

	// Gestiona la adquisición de CANT unidades (un entero no negativo) del producto COD con fecha F.
	// Si hubiera clientes esperando la llegada de este producto, devuelve un vector con los identi￿cadores
	// de los clientes que han podido ser servidos, en el orden en que hicieron la petición.
	// El resto de unidades (si las hay) se guardan en el almacén.
	vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant)
	{
		auto prod = productos.find(cod);
		vector<Cliente> c;

		if (prod == productos.end())
		{ // si no existe lo registras
			FechasExistencias fechas;
			fechas.emplace_back(f, cant);
			ListaEspera esperas;
			InfoProducto i;
			i.fechasExistencias = fechas;
			i.listaEspera = esperas;
			i.existencias = cant;
			productos.insert({ cod, i });
		}
		else
		{ // si existe le añades
			if (!prod->second.listaEspera.empty())
			{ // si tiene lista de espera se vende
				auto& aux = prod->second.listaEspera;
				int size = prod->second.listaEspera.size();
				for (int i = 0; i < size && cant > 0; i++)
				{
					c.push_back(aux.front());
					aux.pop_front();
					cant--;
				}

				int aAnyadir = cant - prod->second.listaEspera.size();
				if (aAnyadir > 0)
				{
					prod->second.existencias += aAnyadir;
					prod->second.fechasExistencias.emplace_back(f, aAnyadir);
				}
			}
			else
			{	// si no se deja en el almacen
				prod->second.existencias += cant;
				prod->second.fechasExistencias.emplace_back(f, cant);
			}
		}
		return c;
	}

	// Gestiona la venta de una unidad del producto COD al cliente CLI (un string sin espacios).
	// Si hay existencias, la operación devuelve true y la fecha del producto vendido (la menor entre las disponibles).
	// Si no hay existencias, devuelve false y añade al cliente a la lista de espera de este producto
	// (un cliente puede aparecer varias veces en la lista de espera).
	pair<bool, Fecha> vender(Codigo const& cod, Cliente const& cli)
	{
		auto prod = productos.find(cod);
		bool meterLista = false;
		pair<bool, Fecha> par = { false, 0 };

		if (prod == productos.end()) // si no existe
		{
			meterLista = true;

			ListaEspera l;
			InfoProducto p;
			p.existencias = 0;
			p.listaEspera = l;

			productos.insert({ cod, p });
			prod = productos.find(cod);
		}
		if (prod != productos.end() && prod->second.existencias <= 0) // si no tiene existencias
			meterLista = true;

		if (meterLista)
		{
			prod->second.listaEspera.push_back(cli);
		}
		else if (prod != productos.end() && prod->second.existencias > 0)// vender
		{
			auto fecha = prod->second.fechasExistencias.back().first;
			auto& existencias = prod->second.fechasExistencias.back().second;

			existencias--;
			prod->second.existencias--;
			if (existencias <= 0)
				prod->second.fechasExistencias.pop_back();

			par.first = true;
			par.second = fecha;
		}
		return par;
	}

	// Devuelve cuántas unidades tiene la tienda del producto COD (independientemente de la fecha).
	// Si se trata de un producto que nunca se ha adquirido simplemente se devuelve 0.
	int cuantos(Codigo const& cod) const
	{
		auto prod = productos.find(cod);
		if (prod == productos.end())
			return 0;
		return prod->second.existencias;
	}

	//  Indica si hay clientes en la lista de espera del producto COD.
	//  Si se trata de un producto que nunca se ha adquirido simplemente se devuelve false.
	bool hay_esperando(Codigo const& cod) const
	{
		auto prod = productos.find(cod);
		if (prod == productos.end())
			return false;
		return !prod->second.listaEspera.empty();
	}
};

bool resuelveCaso()
{
	std::string operacion, cod, cli;
	Fecha f;
	int cant;
	std::cin >> operacion;
	if (!std::cin)
		return false;

	Tienda tienda;

	while (operacion != "FIN")
	{
		if (operacion == "adquirir")
		{
			cin >> cod >> f >> cant;
			vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
			cout << "PRODUCTO ADQUIRIDO";
			for (auto c : clientes)
				cout << ' ' << c;
			cout << '\n';
		}
		else if (operacion == "vender")
		{
			cin >> cod >> cli;
			pair<bool, Fecha> venta = tienda.vender(cod, cli);
			if (venta.first)
			{
				cout << "VENDIDO " << venta.second << '\n';
			}
			else
				cout << "EN ESPERA\n";
		}
		else if (operacion == "cuantos")
		{
			cin >> cod;
			cout << tienda.cuantos(cod) << '\n';
		}
		else if (operacion == "hay_esperando")
		{
			cin >> cod;
			if (tienda.hay_esperando(cod))
				cout << "SI\n";
			else
				cout << "NO\n";
		}

		std::cin >> operacion;
	}
	std::cout << "---\n";
	return true;
}


//#define DOMJUDGE
int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("input.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
#endif

	return 0;
}
