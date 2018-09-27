
#include "MatrizStandard.h"
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"
#include <algorithm>
#include "helpers/Tools.h"

MatrizStandard::MatrizStandard(const MatrizStandard& m) : Matriz(m.GetCantidadFilas(), m.GetCantidadColumnas())
{
	this->datos = NULL;

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

	float** newDatos = new float*[filas];

	for(unsigned int i = 0; i < filas; i++)
	{
		newDatos[i] = new float[columnas];
	}

	if(this->datos != NULL)
	{
		for(unsigned int f = 0; f < std::min(filas, GetCantidadFilas()); f++)
		{
			for(unsigned int c = 0; c < std::min(columnas, GetCantidadColumnas()); c++)
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

	MatrizStandard copia(*this);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, copia.Get(fil, col) + m2.Get(fil, col));
		}
	}
}

void MatrizStandard::Restar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	MatrizStandard copia(*this);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, copia.Get(fil, col) - m2.Get(fil, col));
		}
	}
}

void MatrizStandard::Multiplicar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	MatrizStandard copia(*this);

	for(unsigned int fil = 0; fil < copia.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m2.GetCantidadColumnas(); col++)
		{
			float accum = 0;

			for(unsigned int i = 0; i < copia.GetCantidadColumnas(); i++)
			{
				float v1 = copia.Get(fil, i);
				float v2 = m2.Get(i, col);

				if(Tools::EsNulo(v1) || Tools::EsNulo(v2))
				{
					continue;
				}

				accum += copia.Get(fil, i) * m2.Get(i, col);
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

	for(unsigned int currentCol = 0; currentCol < GetCantidadFilas() && currentCol < GetCantidadColumnas() - 1; currentCol++)
	{
		Console::Out() << currentCol << " / " << GetCantidadFilas() << std::endl;

		for(unsigned int fil = currentCol+1; fil < GetCantidadFilas(); fil++)
		{
			float srcVal = (Get(currentCol, currentCol));
			float dstVal = -(Get(fil, currentCol));

			float escalar = dstVal / srcVal;
			GaussSumarMultiplo(currentCol, fil, escalar, currentCol);

			//Console::Debug() << "F" << fil << "=" << "F" << currentFil << " x " << escalar << " + " << "F" << fil << std::endl;  // @suppress("Invalid overload")
			//Console::Debug() << m << std::endl;  // @suppress("Invalid overload")
		}

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

Matriz* MatrizStandard::CrearIdentidad(const unsigned int& tam)
{
	Matriz* identidad = new MatrizStandard(tam, tam, 0);

	for(unsigned int i = 0; i < tam; i++)
	{
		identidad->Set(i, i, 1);
	}

	return identidad;
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
