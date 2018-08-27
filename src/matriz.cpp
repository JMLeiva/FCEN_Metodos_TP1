#include "matriz.h"
#include <assert.h>
#include <iomanip>

Matriz::Matriz(const Matriz& m)
{
	this->filas = m.GetCantidadFilas();
	this->columnas = m.GetCantidadColumnas();

	unsigned int size = m.GetCantidadFilas() * m.GetCantidadColumnas();

	this->datos = new float[size];

	for(unsigned int fil = 0; fil < m.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			this->Set(fil, col, m.Get(fil, col));
		}
	}
}

Matriz::Matriz(const unsigned int filas, const unsigned int columnas)
{
	this->filas = filas;
	this->columnas = columnas;
	this->datos = new float[filas * columnas];
}

Matriz::Matriz(const unsigned int filas, const unsigned int columnas, const float fill)
{
	// TODO llamar al otro constructor
	this->filas = filas;
	this->columnas = columnas;
	this->datos = new float[filas * columnas];

	for(unsigned int i = 0; i < filas * columnas; i++)
	{
		this->datos[i] = fill;
	}
}

Matriz::~Matriz()
{
	delete datos;
}

Matriz Matriz::operator+(const Matriz& m)
{
	assert(this->GetCantidadColumnas() == m.GetCantidadColumnas());
	assert(this->GetCantidadFilas() == m.GetCantidadFilas());

	Matriz result = Matriz(this->GetCantidadFilas(), this->GetCantidadColumnas());

	for(unsigned int i = 0; i < GetCantidadFilas() * GetCantidadColumnas(); i++)
	{
		result.datos[i] = this->datos[i] + m.datos[i];
	}

	return result;
}

Matriz Matriz::operator*(const Matriz& m)
{
	assert(this->GetCantidadColumnas() == m.GetCantidadFilas());

	Matriz result = Matriz(this->GetCantidadFilas(), m.GetCantidadColumnas());

	for(unsigned int fil = 0; fil < this->GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			int accum = 0;

			for(unsigned int i = 0; i < this->GetCantidadColumnas(); i++)
			{
				accum += this->Get(fil, i) * m.Get(i, col);
			}

			result.Set(fil, col, accum);
		}
	}

	return result;
}


Matriz Matriz::Escalonada()
{
	// Eliminacion Gaussiana
	Matriz result = Matriz(*this);

	unsigned int currentCol = 0;

	for(unsigned int currentFil = 0; currentFil < result.GetCantidadFilas() && currentCol < result.GetCantidadColumnas() - 1; currentFil++)
	{
		for(unsigned int fil = currentFil+1; fil < result.GetCantidadFilas(); fil++)
		{
			float srcVal = ((float)result.Get(currentFil, currentCol));
			float dstVal = -((float)result.Get(fil, currentCol));

			float escalar = dstVal / srcVal;
			result.GaussSumarMultiplo(currentFil, fil, escalar);

			std::cout << "F" << fil << "=" << "F" << currentFil << " x " << escalar << " + " << "F" << fil << std::endl;
			std::cout << result << std::endl;
		}

		currentCol++;
	}


	return result;
}

void Matriz::GaussMultiplicarFila(unsigned int fila, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		this->Set(fila, col, this->Get(fila, col) * escalar);
	}
}

void Matriz::GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		float srcVal = this->Get(filaSrc, col);
		float dstval = this->Get(filaDst, col);
		float result = dstval + srcVal * escalar;
		this->Set(filaDst, col, result);
	}
}

unsigned int Matriz::IndiceParaPosiciones(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	return fil * columnas + col;
}

unsigned int Matriz::GetCantidadFilas() const
{
	return filas;
}

unsigned int Matriz::GetCantidadColumnas() const
{
	return columnas;
}

void Matriz::Set(const unsigned int fil, const unsigned int col, const float val)
{
	CheckPosicionesValidas(fil, col);

	unsigned int indice = this->IndiceParaPosiciones(fil, col);
	this->datos[indice] = val;
}

float Matriz::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	unsigned int indice = this->IndiceParaPosiciones(fil, col);
	return this->datos[indice];
}

void Matriz::CheckPosicionesValidas(const unsigned int fil, const unsigned int col) const
{
	assert(fil < filas);
	assert(col < columnas);
}

std::ostream& operator<<(std::ostream& os, const Matriz& m)
{
	for(unsigned int fil = 0; fil < m.GetCantidadFilas(); fil++)
	{
		os << "| ";

		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			os << std::setw(12) << m.Get(fil, col);
		}

		os << "     |" << std::endl;
	}

    return os;
}
