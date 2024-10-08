// Nombre del alumno ..... Cynthia Tristán
// Usuario del Juez ...... EDA-GDV73 


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

class Horas
{
	int h, m, s;

	bool validate() const
	{
		// returns true if valid time
		return
			0 <= h &&
			h <= 23 &&
			0 <= m &&
			m <= 59 &&
			0 <= s &&
			s <= 59;
	}

public: // constructoras
	Horas(int h = 0, int m = 0, int s = 0) : h(h), m(m), s(s)
	{
		if (!validate())
			throw std::invalid_argument("ERROR");
	}

	Horas(const Horas& hora) : h(hora.h), m(hora.m), s(hora.s)
	{
		if (!validate())
			throw std::invalid_argument("ERROR");
	}

	~Horas() = default;

	// operators
	bool operator<(const Horas& hora) const
	{
		return
			(h < hora.h) ||
			(h == hora.h && m < hora.m) ||
			(h == hora.h && m == hora.m && s < hora.s);
	}

	Horas& operator=(const Horas& other)
	{
		if (this != &other) {  
            h = other.h;
            m = other.m;
            s = other.s;

            if (!validate()) 
                throw std::invalid_argument("ERROR");
        }
        return *this;  
	}

	friend std::ostream& operator<<(std::ostream& out, const Horas& h);
	// friend porque accede a campos privados pero es funcion externa
	friend std::istream& operator>>(std::istream& in, Horas& h);
	// friend porque accede a campos privados pero es funcion externa
};

std::ostream& operator<<(std::ostream& out, const Horas& hora)
{
	out << (hora.h < 10 ? "0" : "") << hora.h << ":"
		<< (hora.m < 10 ? "0" : "") << hora.m << ":"
		<< (hora.s < 10 ? "0" : "") << hora.s;

	return out;
}

std::istream& operator>>(std::istream& in, Horas& hora)
{
	int h, m, s;
	in >> h;
	in.ignore(1, ':');
	in >> m;
	in.ignore(1, ':');
	in >> s;
	hora = Horas(h, m, s);
	return in;
}

// devuelve la hora del siguiente tren segun la consultada
bool siguiente(const std::vector<Horas>& trenes, const Horas& consulta, Horas& siguiente)
{
	unsigned int i = 0;
	while (i < trenes.size())
	{
		if (consulta < trenes[i])
		{
			siguiente = trenes[i];
			return true;
		}
		i++;
	}
	return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	int n = 0, m = 0;
	std::cin >> n >> m;

	if (n == 0 && m == 0)
		return false;

	std::vector<Horas> trenes(n);
	for (auto& tren : trenes)
		std::cin >> tren;

	Horas sig, consulta;
	for (int i = 0; i < m; i++)
	{
		try
		{
			std::cin >> consulta;
			if (siguiente(trenes, consulta, sig))
				std::cout << sig << std::endl;
			else
				std::cout << "NO\n";
		}
		catch (const std::invalid_argument& e) 
		{
			std::cout << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "ERROR" << std::endl;
		}
	}
	std::cout << "---\n";
	return true;
}

int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


	while (resuelveCaso());


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
