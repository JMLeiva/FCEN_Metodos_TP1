
#include "MatrizRala.h"
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"

MatrizRala::MatrizRala()
{
	tamano_columna = NULL;
}


MatrizRala::MatrizRala(const unsigned int filas, const unsigned int columnas) : Matriz(filas, columnas)
{
	tamano_columna = new unsigned int[columnas];
}

void MatrizRala::Set(const unsigned int fil, const unsigned int col, float val)
{
	Matriz::CheckPosicionesValidas(fil, col);

	std::map <unsigned int, std::set<unsigned int> > :: iterator itr = datos.find(fil);

	if(itr == datos.end())
	{
		std::pair <unsigned int, std::set<unsigned int> > pair(fil, std::set<unsigned int>());
		itr = datos.insert(pair).first;
	}

	if(val == 0)
	{
		if(itr->second.erase(col) != 0)
		{
			//Elimine elemento
			tamano_columna[col] -= 1;
		}
	}
	else
	{
		std::pair<std::set<unsigned int>::iterator, bool> res = itr->second.insert(col);

		if(res.second)
		{
			// Agrego elemento
			tamano_columna[col] += 1;
		}
	}
}

float MatrizRala::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	if(datos.find(fil) == datos.end())
	{
		return 0;
	}

	std::set<unsigned int> mSet = datos.at(fil);

	return mSet.find(col) != mSet.end() ? 1 : 0;
}


void MatrizRala::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);
	datos.clear();
}


Matriz* MatrizRala::Escalonada() const
{
	//  Todo esto no se puede hacer bien aca!
	assert(false);
	return NULL;
}

Matriz* MatrizRala::Extendida(const Vector& v) const
{
	//  Todo esto no se puede hacer bien aca!
	assert(false);
	return NULL;
}

MatrizStandard MatrizRala::operator*(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	MatrizStandard result = MatrizStandard(GetCantidadFilas(), m2.GetCantidadColumnas(), 0);

	std::map <unsigned int, std::set<unsigned int> > :: iterator itFila;

	for ( itFila = datos.begin(); itFila != datos.end(); itFila++ )
	{
		unsigned int currentFil = itFila->first;

		std::set<unsigned int> fila = datos.at(currentFil);

		std::set<unsigned int>::iterator itColumna;

		for(unsigned int currentCol = 0; currentCol < m2.GetCantidadColumnas(); currentCol++)
		{
			float accum = 0;

			for(itColumna = fila.begin(); itColumna != fila.end(); itColumna++)
			{
				accum += m2.Get(*itColumna, currentCol);
			}

			//Console::Out() << currentFil * GetCantidadColumnas() + currentCol << " / " << GetCantidadFilas() * m2.GetCantidadColumnas() << std::endl;
			result.Set(currentFil, currentCol, accum);
		}
	}

	return result;
}

MatrizStandard* MatrizRala::CalcularGradoOptimizado()
{
	MatrizStandard* result = new MatrizStandard(GetCantidadFilas(), GetCantidadColumnas(), 0);

	for (unsigned int i = 0; i < GetCantidadColumnas(); i++)
	{
		unsigned int tamCol = tamano_columna[i];

		if(tamCol == 0)
		{
			result->Set(i, i, 0);
		}
		else
		{
			result->Set(i, i, (float)1 / tamCol);
		}
	}

	return result;
}

MatrizRala::~MatrizRala()
{
	if(tamano_columna != NULL)
	{
		delete [] tamano_columna;
	}
}

