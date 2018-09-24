/*
 * MatrizDOK.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: root
 */

#include "MatrizDOK.h"
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"

MatrizDOK::MatrizDOK(const MatrizDOK& m) : Matriz(m.GetCantidadFilas(), m.GetCantidadColumnas())
{
	datos.clear();

	auto it = datos.begin();

	while(it != datos.end())
	{
		auto key = it->first;
		datos[key] = it->second;
		it++;
		//datos.insert(std::pair<std::tuple<unsigned int, unsigned int>, float>(it->first, it->second));
	}
}


MatrizDOK::MatrizDOK(const unsigned int filas, const unsigned int columnas) : Matriz(filas, columnas)
{

}

MatrizDOK::MatrizDOK(const unsigned int filas, const unsigned int columnas, const float fill) : Matriz(filas, columnas)
{
	if(EsNulo(fill))
	{
		// No hago nada
		return;
	}

	Console::Out() << "Atencion!!!!!!!!!" << std::endl << "Llenando Matriz rala con valores NO nulos" << std::endl;

	for(unsigned int f = 0; f < filas; f++)
	{
		for(unsigned int c = 0; c < columnas; c++)
		{
			auto key = std::make_tuple(f, c);
			datos[key] = fill;
		}
	}
}

Matriz* MatrizDOK::Copiar() const
{
	Matriz* copy = new MatrizDOK(*this);
	return copy;
}


MatrizDOK MatrizDOK::Identidad(unsigned int tam)
{
	MatrizDOK result(tam, tam, 0);

	for(unsigned int i = 0; i < tam; i++)
	{
		result.Set(i, i, 1);
	}

	return result;
}

void MatrizDOK::Set(const unsigned int fil, const unsigned int col, const float val)
{
	CheckPosicionesValidas(fil, col);

	auto key = std::make_tuple(fil, col);

	if(!EsNulo(val))
	{
		datos[key] = val;
	}
	else
	{
		datos.erase(key);
	}
}

float MatrizDOK::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	auto key = std::make_tuple(fil, col);

	if(datos.find(key) != datos.end())
	{
		return datos.at(key);
	}

	return 0;
}


void MatrizDOK::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	unsigned int oldFilas = GetCantidadFilas();
	unsigned int oldColumnas = GetCantidadColumnas();
	Matriz::SetTamano(filas, columnas);

	if(filas >= oldFilas && columnas >= oldColumnas)
	{
		return;
	}

	auto it = datos.begin();

	while(it != datos.end())
	{
		auto key = it->first;

		if(std::get<0>(key) > filas || std::get<1>(key) > columnas)
		{
			datos.erase(key);
		}

		it++;
	}
}

void MatrizDOK::Sumar(const Matriz& m2)
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

void MatrizDOK::Restar(const Matriz& m2)
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

void MatrizDOK::Multiplicar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m2.GetCantidadColumnas(); col++)
		{
			float accum = 0;

			for(unsigned int i = 0; i < GetCantidadColumnas(); i++)
			{
				float v1 = Get(fil, i);
				float v2 = m2.Get(i, col);

				if(EsNulo(v1) || EsNulo(v2))
				{
					continue;
				}

				accum += Get(fil, i) * m2.Get(i, col);
			}

			Set(fil, col, accum);
		}
	}
}

void MatrizDOK::Multiplicar(const float& f)
{
	auto it = datos.begin();

	while(it != datos.end())
	{
		auto key = it->first;

		datos[key] *= f;

		it++;
	}
}

void MatrizDOK::Extender(const Vector& v)
{
	assert(v.GetTamano() == GetCantidadFilas());
	SetTamano(GetCantidadFilas(), GetCantidadColumnas()+1);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		Set(fil, GetCantidadColumnas()-1, v.Get(fil));
	}
}


void MatrizDOK::Escalonar()
{
	if(EstaEscalonada())
	{
		return;
	}

	// Eliminacion Gaussiana
	unsigned int currentCol = 0;

	for(unsigned int currentFil = 0; currentFil < GetCantidadFilas() && currentCol < GetCantidadColumnas() - 1; currentFil++)
	{
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

void MatrizDOK::GaussMultiplicarFila(unsigned int fila, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		this->Set(fila, col, this->Get(fila, col) * escalar);
	}
}

void MatrizDOK::GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset)
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

MatrizDOK::~MatrizDOK()
{

}
