
#include "MatrizStandard.h"
#include <assert.h>
#include <iomanip>

MatrizStandard::MatrizStandard() : Matriz()
{
	this->datos = NULL;
}


void MatrizStandard::Copy(const Matriz& m)
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

Matriz* MatrizStandard::Escalonada() const
{
	MatrizStandard* result = new MatrizStandard();
	result->Copy(*this);
	Matriz::Escalonar(*result);
	return result;
}

Matriz* MatrizStandard::Extendida(const Vector& v) const
{
	MatrizStandard* result = new MatrizStandard(this->GetCantidadFilas(), this->GetCantidadColumnas()+1);
	Matriz::Extender(*this, v, *result);
	return result;
}

void MatrizStandard::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);

	if(this->datos != NULL)
	{
		for(unsigned int i = 0; i < GetCantidadFilas(); i++)
		{
			delete this->datos[i];
		}

		delete [] datos;
	}

	this->datos = new float*[GetCantidadFilas()];

	for(unsigned int i = 0; i < GetCantidadFilas(); i++)
	{
		this->datos[i] = new float[GetCantidadColumnas()];
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

MatrizStandard MatrizStandard::operator*(const Matriz& m2)
{
	MatrizStandard result = MatrizStandard();

	Matriz::Multiplicar(*this, m2, &result);

	return result;
}

MatrizStandard operator+(const Matriz& m1, const Matriz& m2)
{
	MatrizStandard result = MatrizStandard();

	Matriz::Sumar(m1, m2, &result);

	return result;
}

MatrizStandard operator-(const Matriz& m1, const Matriz& m2)
{
	MatrizStandard result = MatrizStandard();

	Matriz::Restar(m1, m2, &result);

	return result;
}

MatrizStandard operator*(const float& f, const Matriz& m2)
{
	MatrizStandard result = MatrizStandard();

	Matriz::Multiplicar(f, m2, &result);

	return result;
}
