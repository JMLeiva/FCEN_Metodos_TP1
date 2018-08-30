#include "matriz.h"
#include <assert.h>
#include <iomanip>


Matriz::Matriz()
{
	this->filas = 0;
	this->columnas = 0;
}

Matriz::Matriz(const Matriz& m)
{
	this->filas = m.GetCantidadFilas();
	this->columnas = m.GetCantidadColumnas();
}

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

void Matriz::Sumar(const Matriz& m1, const Matriz& m2, Matriz* out)
{
	assert(m1.GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(m2.GetCantidadFilas() == m2.GetCantidadFilas());

	out->SetTamano(m1.GetCantidadFilas(), m1.GetCantidadColumnas());

	for(unsigned int fil = 0; fil < m1.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m1.GetCantidadColumnas(); col++)
		{
			out->Set(fil, col, m1.Get(fil, col) + m2.Get(fil, col));
		}
	}
}

void Matriz::Restar(const Matriz& m1, const Matriz& m2, Matriz* out)
{
	assert(m1.GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(m2.GetCantidadFilas() == m2.GetCantidadFilas());

	out->SetTamano(m1.GetCantidadFilas(), m1.GetCantidadColumnas());

	for(unsigned int fil = 0; fil < m1.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m1.GetCantidadColumnas(); col++)
		{
			out->Set(fil, col, m1.Get(fil, col) - m2.Get(fil, col));
		}
	}
}

void Matriz::Multiplicar(const Matriz& m1, const Matriz& m2, Matriz* out)
{
	assert(m1.GetCantidadColumnas() == m2.GetCantidadFilas());
	out->SetTamano(m1.GetCantidadFilas(), m2.GetCantidadColumnas());

	for(unsigned int fil = 0; fil < m1.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m2.GetCantidadColumnas(); col++)
		{
			float accum = 0;

			for(unsigned int i = 0; i < m1.GetCantidadColumnas(); i++)
			{
				accum += m1.Get(fil, i) * m2.Get(i, col);
			}

			out->Set(fil, col, accum);
		}
	}
}

void Matriz::Multiplicar(const float& f, const Matriz& m, Matriz* out)
{
	out->SetTamano(m.GetCantidadFilas(), m.GetCantidadColumnas());

	for(unsigned int fil = 0; fil < m.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			out->Set(fil, col, m.Get(fil, col) *  f);
		}
	}
}


Matriz& Matriz::Escalonada()
{
	// Eliminacion Gaussiana
	unsigned int currentCol = 0;

	for(unsigned int currentFil = 0; currentFil < this->GetCantidadFilas() && currentCol < this->GetCantidadColumnas() - 1; currentFil++)
	{
		for(unsigned int fil = currentFil+1; fil < this->GetCantidadFilas(); fil++)
		{
			float srcVal = (this->Get(currentFil, currentCol));
			float dstVal = -(this->Get(fil, currentCol));

			float escalar = dstVal / srcVal;
			this->GaussSumarMultiplo(currentFil, fil, escalar);

			std::cout << "F" << fil << "=" << "F" << currentFil << " x " << escalar << " + " << "F" << fil << std::endl;
			std::cout << *this << std::endl;
		}

		currentCol++;
	}


	return *this;
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
	assert(filaSrc < this->GetCantidadFilas());
	assert(filaDst < this->GetCantidadFilas());

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

