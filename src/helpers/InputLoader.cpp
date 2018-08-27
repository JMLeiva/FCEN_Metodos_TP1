/*
 * InputLoader.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: juan
 */

#include "InputLoader.h"
#include <iostream>
#include <fstream>

using namespace std;

InputLoader::InputLoader() {
	// TODO Auto-generated constructor stub

}

Matriz* InputLoader::Load(const char* path)
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

	Matriz* matriz = new Matriz(numeroDePaginas, numeroDePaginas, 0);

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

InputLoader::~InputLoader() {
	// TODO Auto-generated destructor stub
}

