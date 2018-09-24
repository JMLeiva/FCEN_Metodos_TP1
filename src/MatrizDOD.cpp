
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"
#include "MatrizDOD.h"
#include "helpers/Tools.h"

MatrizDOD::MatrizDOD(const MatrizDOD& m) : Matriz(m.GetCantidadFilas(), m.GetCantidadColumnas())
{
	datos.clear();
	tamano_columna.clear();

	auto itDatos = m.datos.begin();
	while(itDatos != m.datos.end())
	{
		unsigned int key = itDatos->first;
		auto mapCopia = std::map<unsigned int, float>(itDatos->second);
		datos[key] = mapCopia;
		itDatos++;
	}

	auto itTam = m.tamano_columna.begin();
	while(itTam != m.tamano_columna.end())
	{
		tamano_columna.push_back(*itTam);
		itTam++;
	}
}


MatrizDOD::MatrizDOD(const unsigned int filas, const unsigned int columnas) : Matriz(filas, columnas)
{
	for(unsigned int i = 0; i < columnas; i++)
	{
		tamano_columna.push_back(0);
	}
}

MatrizDOD::MatrizDOD(const unsigned int filas, const unsigned int columnas, const float fill) : Matriz(filas, columnas)
{
	for(unsigned int i = 0; i < columnas; i++)
	{
		tamano_columna.push_back(0);
	}

	if(Tools::EsNulo(fill))
	{
		// No hago nada
		return;
	}

	Console::Out() << "Atencion!!!!!!!!!" << std::endl << "Llenando Matriz rala con valores NO nulos" << std::endl;
	assert(false);
}

Matriz* MatrizDOD::Copiar() const
{
	Matriz* copy = new MatrizDOD(*this);
	return copy;
}

Matriz* MatrizDOD::CrearIdentidad(const unsigned int& tam)
{
	Matriz* identidad = new MatrizDOD(tam, tam, 0);

	for(unsigned int i = 0; i < tam; i++)
	{
		identidad->Set(i, i, 1);
	}

	return identidad;
}

void MatrizDOD::Set(const unsigned int fil, const unsigned int col, float val)
{
	Matriz::CheckPosicionesValidas(fil, col);

	auto itr = datos.find(fil);

	if(itr == datos.end() && !Tools::EsNulo(val))
	{
		std::pair<unsigned int, std::map<unsigned int, float>> pair = std::make_pair(fil, std::map<unsigned int, float>());
		auto a = datos.insert(pair);
		itr = a.first;
	}

	if(Tools::EsNulo(val))
	{
		if(itr != datos.end())
		{
			if(itr->second.erase(col) != 0)
			{
				//Elimine elemento
				tamano_columna[col] -= 1;
			}
		}
	}
	else
	{
		auto itFila = itr->second.find(col);

		if(itFila == itr->second.end())
		{
			// Habia un cero
			// Sumo tamano de columna
			tamano_columna[col] += 1;
		}

		itr->second[col] = val;

	}
}

float MatrizDOD::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	auto it = datos.find(fil);

	if(it == datos.end())
	{
		return 0;
	}

	auto filaIt = it->second.find(col);

	if(filaIt == it->second.end())
	{
		return 0;
	}

	return it->second.at(col);
}


void MatrizDOD::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);

	if(columnas < GetCantidadColumnas())
	{
		auto itDatos = datos.begin();
		while(itDatos != datos.end())
		{
			auto itFila = itDatos->second.begin();

			while(itFila != itDatos->second.end())
			{
				if(itFila->first >= columnas)
				{
					itFila = itDatos->second.erase(itFila);
				}
				else
				{
					itFila++;
				}
			}

			itDatos++;
		}
	}
	else
	{
		// Agrego las columnas nuevas, con tamaño 0
		for(unsigned int i = GetCantidadColumnas(); i < columnas; i++)
		{
			this->tamano_columna.push_back(0);
		}
	}

	if(filas < GetCantidadFilas())
	{
		// TODO
	}
}

void MatrizDOD::Sumar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	MatrizDOD copia(*this);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, copia.Get(fil, col) + m2.Get(fil, col));
		}
	}
}

void MatrizDOD::Restar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	MatrizDOD copia(*this);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < GetCantidadColumnas(); col++)
		{
			Set(fil, col, copia.Get(fil, col) - m2.Get(fil, col));
		}
	}
}

void MatrizDOD::Multiplicar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	MatrizDOD copia(*this);

	for(unsigned int fil = 0; fil < copia.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m2.GetCantidadColumnas(); col++)
		{
			float accum = 0;

			auto colIt = copia.datos.find(fil);
			if(colIt == copia.datos.end())
			{
				// FIla de ceros
				Set(fil, col, 0);
				continue;
			}

			auto filaIt = colIt->second.begin();

			while(filaIt != colIt->second.end())
			{
				unsigned int currentCol = filaIt->first;
				float v1 = filaIt->second;
				float v2 = m2.Get(currentCol, col);

				if(!Tools::EsNulo(v1) && !Tools::EsNulo(v2))
				{
					accum += v1 * v2;
				}

				filaIt++;
			}

			if(!Tools::EsNulo(accum))
			{
				Set(fil, col, accum);
			}
		}
	}
}

void MatrizDOD::Multiplicar(const float& f)
{
	auto it = datos.begin();

	while(it != datos.end())
	{
		auto filaIt = it->second.begin();

		while(filaIt != it->second.end())
		{
			filaIt->second *= f;

			filaIt++;
		}

		it++;
	}
}

void MatrizDOD::Extender(const Vector& v)
{
	assert(v.GetTamano() == GetCantidadFilas());
	SetTamano(GetCantidadFilas(), GetCantidadColumnas()+1);

	for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
	{
		Set(fil, GetCantidadColumnas()-1, v.Get(fil));
	}
}


void MatrizDOD::Escalonar()
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

void MatrizDOD::GaussMultiplicarFila(unsigned int fila, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		this->Set(fila, col, this->Get(fila, col) * escalar);
	}
}

void MatrizDOD::GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset)
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

MatrizDOD::~MatrizDOD()
{

}
