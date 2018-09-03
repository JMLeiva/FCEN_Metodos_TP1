/*
 * InputLoader.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: juan
 */

#include "IOHelper.h"
#include "../MatrizRala.h"
#include "../Matriz.h"
#include "Console.h";

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>


namespace IO
{
	Matriz* Load(const char* path)
	{
		std::ifstream file;

		file.open(path);

		if(!file.fail())
		{
			Console::Debug() << "File " << path << " Opened" << std::endl; // @suppress("Invalid overload")
		}
		else
		{
			Console::Debug() << "File " << path << " Not opened" << std::endl; // @suppress("Invalid overload")
		}

		unsigned int numeroDePaginas;
		file >> numeroDePaginas;
		Console::Debug() << "Numero de paginas: " << numeroDePaginas << std::endl; // @suppress("Invalid overload")

		unsigned int numeroDeLinks;
		file >> numeroDeLinks;
		Console::Debug() << "Numero de links: " << numeroDeLinks << std::endl; // @suppress("Invalid overload")

		Matriz* matriz = new MatrizRala(numeroDePaginas, numeroDePaginas);

		for(unsigned int link = 0; link < numeroDeLinks; link++)
		{
			unsigned i, j;

			file >> i >> j;

			Console::Debug() << i << " " << j << std::endl; // @suppress("Invalid overload")

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


