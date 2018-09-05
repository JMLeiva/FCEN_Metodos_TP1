#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>

#include "helpers/Console.h"
#include "helpers/IOHelper.h"
#include "MatrizStandard.h"
#include "MatrizRala.h"

void testSum();
void testMul();
void testGauss();
void testSolucion();
Matriz* generarMatrizGrado(const Matriz& w);
Vector* generarVectorZ(const Matriz& D);

int main(int argc, char* argv[])
{
	char* inputPath = argv[1];
	float p = std::stof(argv[2]);

	Console::Out() << "Leyendo archivo..." << std::endl;

	MatrizRala* W = IO::Load(inputPath); // ../
	Console::Debug() << *W << std::endl; // @suppress("Invalid overload")

	Console::Out() << "Generando Grado..." << std::endl;

	Matriz* D = W->CalcularGradoOptimizado();//generarMatrizGrado(*W);
	Console::Debug() << *D << std::endl; // @suppress("Invalid overload")

	Console::Out() << "Generando e..." << std::endl;

	Vector* e = new Vector(D->GetCantidadFilas(), 1);


	Console::Out() << "Calculando WD..." << std::endl;

	MatrizStandard WD = (*W) * (*D);
	Console::Debug() << WD << std::endl; // @suppress("Invalid overload")

	Console::Out() << "Calculando pWD..." << std::endl;

	MatrizStandard pWD = p * WD;
	Console::Debug() << pWD << std::endl; // @suppress("Invalid overload")

	Console::Out() << "Calculando I - pWD..." << std::endl;
	MatrizStandard i_pWD = MatrizStandard::Identidad(W->GetCantidadFilas()) - pWD;
	Console::Debug() << i_pWD << std::endl; // @suppress("Invalid overload")

	Console::Out() << "Aplicando Eliminacion Gaussiana..." << std::endl;
	Vector solucion = i_pWD.ResolverSistema(*e);
	Console::Debug() << solucion << std::endl; // @suppress("Invalid overload")

	solucion.Normalizar();

	Console::Debug() << solucion << std::endl; // @suppress("Invalid overload")

	std::string outPath(inputPath);
	outPath += ".out";

	IO::Save(outPath.c_str(), p, solucion);

	//testSum();
	//testMul();
	//testGauss();
	//testSolucion();
	delete e;
	delete D;
	delete W;
	//delete i_pWD_escalonada;

	return 0;
}

Matriz* generarMatrizGrado(const Matriz& w)
{
	Matriz* result = new MatrizStandard(w.GetCantidadFilas(), w.GetCantidadColumnas(), 0);

	for(unsigned int col = 0; col < w.GetCantidadColumnas(); col++)
	{
		float accum = 0;

		for(unsigned int fil = 0; fil < w.GetCantidadFilas(); fil++)
		{
			accum += w.Get(fil, col);
		}

		if(accum == 0)
		{
			result->Set(col, col, 0);
		}
		else
		{
			result->Set(col, col, 1 / accum);
		}
	}

	return result;
}

Vector* generarVectorZ(const Matriz& D)
{
	Vector* z = new Vector(D.GetCantidadColumnas());

	for(unsigned int i = 0; i < D.GetCantidadColumnas(); i++)
	{
		float val = 0;
		float ci = D.Get(i, i);

		if(ci != 0)
		{
			val = 1 / ci;
		}

		z->Set(i, val);
	}

	return z;
}

void testSum()
{
	MatrizStandard m1(3, 3, 0);
	m1.Set(0, 0, 2);
	m1.Set(0, 1, 10);
	m1.Set(0, 2, 0);
	m1.Set(1, 0, 1);
	m1.Set(1, 1, 4);
	m1.Set(1, 2, 12);
	m1.Set(2, 0, 8);
	m1.Set(2, 1, -1);
	m1.Set(2, 2, -8);


	std::cout << m1 << std::endl;

	MatrizStandard m2(3, 3, 0);
	m2.Set(0, 0, -8);
	m2.Set(0, 1, 0);
	m2.Set(0, 2, 1);
	m2.Set(1, 0, 1);
	m2.Set(1, 1, 6);
	m2.Set(1, 2, 21);
	m2.Set(2, 0, -7);
	m2.Set(2, 1, -10);
	m2.Set(2, 2, 4);

	std::cout << m2 << std::endl;

	std::cout << m1 + m2 << std::endl;
}

void testMul()
{
	MatrizStandard m1(3, 2, 0);
	m1.Set(0, 0, 2);
	m1.Set(0, 1, 10);
	m1.Set(1, 0, 1);
	m1.Set(1, 1, 4);
	m1.Set(2, 0, 8);
	m1.Set(2, 1, -1);

	std::cout << m1 << std::endl;

	MatrizStandard m2(2, 2, 0);
	m2.Set(0, 0, -8);
	m2.Set(0, 1, 0);
	m2.Set(1, 0, 1);
	m2.Set(1, 1, 6);

	std::cout << m2 << std::endl;

	std::cout << m1 * m2 << std::endl;
}

void testGauss()
{
	MatrizStandard m1(4, 5, 0);
	m1.Set(0, 0, -8);
	m1.Set(0, 1, 0);
	m1.Set(0, 2, 1);
	m1.Set(0, 3, 2);
	m1.Set(0, 4, 18);
	m1.Set(1, 0, 1);
	m1.Set(1, 1, 6);
	m1.Set(1, 2, 21);
	m1.Set(1, 3, 1);
	m1.Set(1, 4, 1.5);
	m1.Set(2, 0, -7);
	m1.Set(2, 1, -10);
	m1.Set(2, 2, 4);
	m1.Set(2, 3, 10);
	m1.Set(2, 4, -1);
	m1.Set(3, 0, -5);
	m1.Set(3, 1, 11);
	m1.Set(3, 2, 0);
	m1.Set(3, 3, 0);
	m1.Set(3, 4, 5);

	std::cout << m1 << std::endl;

	std::cout << m1.Escalonada() << std::endl;
}


void testSolucion()
{
	MatrizStandard m1(3, 3, 0);
	m1.Set(0, 0, -1);
	m1.Set(0, 1, 3);
	m1.Set(0, 2, 0);
	m1.Set(1, 0, 8);
	m1.Set(1, 1, 0.5);
	m1.Set(1, 2, 17);
	m1.Set(2, 0, 4);
	m1.Set(2, 1, 0.666);
	m1.Set(2, 2, -9);

	Vector equals(3, 0);
	equals.Set(0, 1);
	equals.Set(1, 315);
	equals.Set(2, -175);

	std::cout << m1 << std::endl;
	std::cout << equals << std::endl;

	Vector solucion = m1.ResolverSistema(equals);


	std::cout << solucion << std::endl;
}
