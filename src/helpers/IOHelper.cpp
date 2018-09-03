/*
 * InputLoader.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: juan
 */

#include "IOHelper.h"
#include <iostream>
#include <fstream>
#include "../MatrizRala.h"
#include "../Matriz.h"

using namespace std;

namespace IO
{
	Matriz* Load(const char* path)
	{
		std::ifstream file;

		file.open(path);

		if(!file.fail())
		{
			cout << "OPENED" << endl;
		}
		else
		{
			cout << "NOT OPENED" << endl;
		}

		unsigned int numeroDePaginas;
		file >> numeroDePaginas;
		cout << "Numero de paginas: " << numeroDePaginas << endl;

		unsigned int numeroDeLinks;
		file >> numeroDeLinks;
		cout << "Numero de links: " << numeroDeLinks << endl;

		Matriz* matriz = new MatrizRala(numeroDePaginas, numeroDePaginas);

		for(unsigned int link = 0; link < numeroDeLinks; link++)
		{
			unsigned i, j;

			file >> i >> j;

			cout << i << " " << j << endl;

			matriz->Set(j-1, i-1, 1);
		}

		file.close();

		return matriz;
	}

	void Save(const char* path, const float& p, const Vector& solucion)
	{
		std::ofstream file;
		file.open(path);

		file << p << std::endl;

		for(unsigned int i = 0; i < solucion.GetTamano(); i++)
		{
			file << solucion.Get(i) << std::endl;
		}

		file.close();
	}
}


