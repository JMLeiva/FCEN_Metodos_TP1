
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
	this->datos = new float[GetCantidadFilas() * GetCantidadColumnas()];
}

MatrizStandard::MatrizStandard(const unsigned int filas, const unsigned int columnas, const float fill) : Matriz(filas, columnas)
{
	this->datos = new float[GetCantidadFilas() * GetCantidadColumnas()];

	for(unsigned int i = 0; i < GetCantidadFilas() * GetCantidadColumnas(); i++)
	{
		this->datos[i] = fill;
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
	Matriz::CheckPosicionesValidas(fil, col);

	unsigned int indice = this->IndiceParaPosiciones(fil, col);

	this->datos[indice] = val;
}

float MatrizStandard::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	unsigned int indice = this->IndiceParaPosiciones(fil, col);
	return this->datos[indice];
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
		delete [] datos;
	}

	unsigned int size = this->GetCantidadFilas() * this->GetCantidadColumnas();
	this->datos = new float[size];
}

MatrizStandard::~MatrizStandard()
{
	if(this->datos != NULL)
	{
		delete [] datos;
	}
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

MatrizStandard operator*(const Matriz& m1, const Matriz& m2)
{
	MatrizStandard result = MatrizStandard();

	Matriz::Multiplicar(m1, m2, &result);

	return result;
}

MatrizStandard operator*(const float& f, const Matriz& m2)
{
	MatrizStandard result = MatrizStandard();

	Matriz::Multiplicar(f, m2, &result);

	return result;
}
