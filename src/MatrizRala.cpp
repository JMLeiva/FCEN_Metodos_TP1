
#include "MatrizRala.h"
#include <assert.h>
#include <iomanip>

MatrizRala::MatrizRala()
{

}


MatrizRala::MatrizRala(const unsigned int filas, const unsigned int columnas) : Matriz(filas, columnas)
{

}


void MatrizRala::Set(const unsigned int fil, const unsigned int col, float val)
{
	Matriz::CheckPosicionesValidas(fil, col);

	datos.insert(IndiceParaPosiciones(fil, col));
}

float MatrizRala::Get(const unsigned int fil, const unsigned int col) const
{
	CheckPosicionesValidas(fil, col);

	return datos.find(IndiceParaPosiciones(fil, col)) != datos.end() ? 1 : 0;
}


void MatrizRala::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);
	datos.clear();
}


MatrizRala::~MatrizRala()
{

}
