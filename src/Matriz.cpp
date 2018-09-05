#include <assert.h>
#include <iomanip>
#include "Matriz.h"
#include "helpers/Console.h"

Matriz::Matriz()
{
	this->filas = 0;
	this->columnas = 0;
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

void Matriz::Extender(const Matriz& m, const Vector& v, Matriz& out)
{
	assert(v.GetTamano() == m.GetCantidadFilas());
	assert(out.GetCantidadFilas() == m.GetCantidadFilas());
	assert(out.GetCantidadColumnas() == m.GetCantidadColumnas()+1);

	for(unsigned int fil = 0; fil < m.GetCantidadFilas(); fil++)
	{
		for(unsigned int col = 0; col < m.GetCantidadColumnas(); col++)
		{
			out.Set(fil, col, m.Get(fil, col));
		}

		out.Set(fil, out.GetCantidadColumnas()-1, v.Get(fil));
	}
}


void Matriz::Escalonar(Matriz& m)
{
	if(m.EstaEscalonada())
	{
		return;
	}

	// Eliminacion Gaussiana
	unsigned int currentCol = 0;

	int temp = 0;

	for(unsigned int currentFil = 0; currentFil < m.GetCantidadFilas() && currentCol < m.GetCantidadColumnas() - 1; currentFil++)
	{
		Console::Out() << currentFil << " / " << m.GetCantidadFilas() << std::endl;

		for(unsigned int fil = currentFil+1; fil < m.GetCantidadFilas(); fil++)
		{
			float srcVal = (m.Get(currentFil, currentCol));
			float dstVal = -(m.Get(fil, currentCol));

			float escalar = dstVal / srcVal;
			m.GaussSumarMultiplo(currentFil, fil, escalar, currentFil);

			//Console::Debug() << "F" << fil << "=" << "F" << currentFil << " x " << escalar << " + " << "F" << fil << std::endl;  // @suppress("Invalid overload")
			//Console::Debug() << m << std::endl;  // @suppress("Invalid overload")
		}

		currentCol++;

		temp++;

		if(temp >= 250)
		{
			break;
		}
	}
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

void Matriz::GaussMultiplicarFila(unsigned int fila, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		this->Set(fila, col, this->Get(fila, col) * escalar);
	}
}

void Matriz::GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset)
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

	Matriz* extendida = this->Extendida(v);
	Matriz* escalonada = extendida->Escalonada();

	Vector solucion(v.GetTamano(), 0);

	unsigned int colIndex = escalonada->GetCantidadColumnas() - 1;
	unsigned int filIndex = v.GetTamano()-1;



	while(colIndex > 0)
	{
		float accum = escalonada->Get(filIndex, escalonada->GetCantidadColumnas()-1);

		unsigned int col = colIndex;
		unsigned int solIndex = filIndex+1;

		while(col < escalonada->GetCantidadColumnas() - 1)
		{
			float mVal = escalonada->Get(filIndex, col);
			float solVal = solucion.Get(solIndex);
			accum -= mVal * solVal;

			col++;
			solIndex++;
		}

		float posResult = accum / escalonada->Get(filIndex, colIndex-1);

		solucion.Set(filIndex, posResult);


		filIndex--;
		colIndex--;
	}

	delete extendida;
	delete escalonada;

	return solucion;
}

void Matriz::CheckPosicionesValidas(const unsigned int fil, const unsigned int col) const
{
	//assert(fil < filas);
	//assert(col < columnas);
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

