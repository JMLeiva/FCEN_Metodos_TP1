
#include "MatrizStandard.h"
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"

MatrizStandard::MatrizStandard(const MatrizStandard& m) : Matriz(m.GetCantidadFilas(), m.GetCantidadColumnas())
{
	if(this->datos != NULL)
	{
		delete this->datos;
	}

	SetTamano(m.GetCantidadFilas(), m.GetCantidadColumnas());

	for(unsigned int fil = 0; fil < m.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			this->Set(fil, col, m.Get(fil, col));
		}
	}
}


MatrizStandard::MatrizStandard(const unsigned int filas, const unsigned int columnas) : Matriz(filas, columnas)
{
	this->datos = new float*[GetCantidadFilas()];

	for(unsigned int i = 0; i < GetCantidadFilas(); i++)
	{
		this->datos[i] = new float[GetCantidadColumnas()];
	}
}

MatrizStandard::MatrizStandard(const unsigned int filas, const unsigned int columnas, const float fill) : Matriz(filas, columnas)
{
	this->datos = new float*[GetCantidadFilas()];

	for(unsigned int i = 0; i < GetCantidadFilas(); i++)
	{
		this->datos[i] = new float[GetCantidadColumnas()];
	}

	for(unsigned int f = 0; f < GetCantidadFilas(); f++)
	{
		for(unsigned int c = 0; c <  GetCantidadColumnas(); c++)
		{
			this->datos[f][c] = fill;
		}
	}
}

Matriz* MatrizStandard::Copiar() const
{
	Matriz* copy = new MatrizStandard(*this);
	return copy;
}


MatrizStandard MatrizStandard::Identidad(unsigned int tam)
{
	MatrizStandard result(tam, tam, 0);

	for(unsigned int i = 0; i < tam; i++)
	{
		result.Set(i, i, 1);
	}

	return result;
}

void MatrizStandard::Set(const unsigned int fil, const unsigned int col, const float val)
{
	CheckPosicionesValidas(fil, col);
	this->datos[fil][col] = val;
}

float MatrizStandard::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);
	return this->datos[fil][col];
}


void MatrizStandard::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);

	float** newDatos = new float*[GetCantidadFilas()];

	for(unsigned int i = 0; i < GetCantidadFilas(); i++)
	{
		newDatos[i] = new float[GetCantidadColumnas()];
	}

	if(this->datos != NULL)
	{
		for(unsigned int f = 0; f < GetCantidadFilas(); f++)
		{
			for(unsigned int c = 0; c < GetCantidadColumnas(); c++)
			{
				newDatos[f][c] = this->datos[f][c];
			}

			delete this->datos[f];
		}

		delete [] datos;
	}

	this->datos = newDatos;
}

void MatrizStandard::Sumar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, Get(fil, col) + m2.Get(fil, col));
		}
	}
}

void MatrizStandard::Restar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, Get(fil, col) - m2.Get(fil, col));
		}
	}
}

void MatrizStandard::Multiplicar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m2.GetCantidadColumnas(); col++)
		{
			float accum = 0;

			for(unsigned int i = 0; i < GetCantidadColumnas(); i++)
			{
				accum += Get(fil, i) * m2.Get(i, col);
			}

			Set(fil, col, accum);
		}
	}
}

void MatrizStandard::Multiplicar(const float& f)
{
	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, Get(fil, col) *  f);
		}
	}
}

void MatrizStandard::Extender(const Vector& v)
{
	assert(v.GetTamano() == GetCantidadFilas());
	SetTamano(GetCantidadFilas(), GetCantidadColumnas()+1);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, Get(fil, col));
		}

		Set(fil, GetCantidadColumnas()-1, v.Get(fil));
	}
}


void MatrizStandard::Escalonar()
{
	if(EstaEscalonada())
	{
		return;
	}

	// Eliminacion Gaussiana
	unsigned int currentCol = 0;

	for(unsigned int currentFil = 0; currentFil < GetCantidadFilas() && currentCol < GetCantidadColumnas() - 1; currentFil++)
	{
		Console::Out() << currentFil << " / " << GetCantidadFilas() << std::endl;

		for(unsigned int fil = currentFil+1; fil < GetCantidadFilas(); fil++)
		{
			float srcVal = (Get(currentFil, currentCol));
			float dstVal = -(Get(fil, currentCol));

			float escalar = dstVal / srcVal;
			GaussSumarMultiplo(currentFil, fil, escalar, currentFil);

			//Console::Debug() << "F" << fil << "=" << "F" << currentFil << " x " << escalar << " + " << "F" << fil << std::endl;  // @suppress("Invalid overload")
			//Console::Debug() << m << std::endl;  // @suppress("Invalid overload")
		}

		currentCol++;

	}
}

void MatrizStandard::GaussMultiplicarFila(unsigned int fila, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		this->Set(fila, col, this->Get(fila, col) * escalar);
	}
}

void MatrizStandard::GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset)
{
	//assert(filaSrc < this->GetCantidadFilas());
	//assert(filaDst < this->GetCantidadFilas());

	for(unsigned int col = offset; col < this->GetCantidadColumnas(); col++)
	{
		float srcVal = this->Get(filaSrc, col);
		float dstval = this->Get(filaDst, col);
		float result = dstval + srcVal * escalar;
		this->Set(filaDst, col, result);
	}
}

MatrizStandard::~MatrizStandard()
{
	if(this->datos != NULL)
	{
		for(unsigned int i = 0; i < GetCantidadFilas(); i++)
		{
			delete this->datos[i];
		}

		delete [] datos;
	}
}
