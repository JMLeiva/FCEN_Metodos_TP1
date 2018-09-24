#include <assert.h>
#include <iomanip>
#include "Matriz.h"
#include "helpers/Console.h"
#include <cmath>

const float EPSILON = 0.000001;

Matriz::Matriz(const unsigned int filas, const unsigned int columnas)
{
	this->filas = filas;
	this->columnas = columnas;
}

void Matriz::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	this->filas = filas;
	this->columnas = columnas;
}

Matriz::~Matriz()
{

}

bool Matriz::EstaEscalonada() const
{
	unsigned int currentCol = 0;

	for(unsigned int currentFil = 0; currentFil < this->GetCantidadFilas() && currentCol < this->GetCantidadColumnas() - 1; currentFil++)
	{
		// Busco primer valor no nulo de la fila
		for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
		{
			if(this->Get(currentFil, col) != 0)
			{
				if(col < currentCol)
				{
					return false;
				}

				currentCol = col+1;
				break;
			}
		}
	}

	return true;
}

unsigned int Matriz::GetCantidadFilas() const
{
	return filas;
}

unsigned int Matriz::GetCantidadColumnas() const
{
	return columnas;
}


Vector Matriz::ResolverSistema(const Vector& v) const
{
	assert(v.GetTamano() == GetCantidadFilas());

	Matriz* extendida = this->Copiar();

	Console::Debug() << *extendida << std::endl;

	extendida->Extender(v);

	Console::Debug() << *extendida << std::endl;

	extendida->Escalonar();

	Console::Debug() << *extendida << std::endl;

	Vector solucion(v.GetTamano(), 0);

	unsigned int colIndex = extendida->GetCantidadColumnas() - 1;
	unsigned int filIndex = v.GetTamano()-1;



	while(colIndex > 0)
	{
		float accum = extendida->Get(filIndex, extendida->GetCantidadColumnas()-1);

		unsigned int col = colIndex;
		unsigned int solIndex = filIndex+1;

		while(col < extendida->GetCantidadColumnas() - 1)
		{
			float mVal = extendida->Get(filIndex, col);
			float solVal = solucion.Get(solIndex);
			accum -= mVal * solVal;

			col++;
			solIndex++;
		}

		float posResult = accum / extendida->Get(filIndex, colIndex-1);

		solucion.Set(filIndex, posResult);


		filIndex--;
		colIndex--;
	}

	delete extendida;

	return solucion;
}

void Matriz::CheckPosicionesValidas(const unsigned int fil, const unsigned int col) const
{
	assert(fil < filas);
	assert(col < columnas);
}

bool Matriz::EsNulo(const float f) const
{
	return fabs(f) < EPSILON;
}

std::ostream& operator<<(std::ostream& os, const Matriz& m)
{
	/*for(unsigned int fil = 0; fil < m.GetCantidadFilas(); fil++)
	{
		os << "| ";

		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			os << std::setw(12) << m.Get(fil, col);
		}

		os << "     |" << std::endl;
	}*/

    return os;
}
