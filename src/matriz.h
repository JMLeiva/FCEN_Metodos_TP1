#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <iostream>

class Matriz
{
public:

	Matriz(const Matriz& m);
	Matriz(const unsigned int filas, const unsigned int columnas);
	Matriz(const unsigned int filas, const unsigned int columnas, const float fill);
	~Matriz();

	unsigned int GetCantidadFilas() const;
	unsigned int GetCantidadColumnas() const;
	void Set(const unsigned int fil, const unsigned int col, const float val);
	float Get(const unsigned int fil, const unsigned int col) const;
	Matriz operator+(const Matriz& m);
	Matriz operator*(const Matriz& m);
	Matriz Escalonada();

private:
	unsigned int IndiceParaPosiciones(const unsigned int i, const unsigned int j) const;
	void GaussMultiplicarFila(unsigned int fila, float escalar);
	void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar);

	unsigned int filas, columnas;
	float* datos;

	///
	void CheckPosicionesValidas(const unsigned int fil, const unsigned int j) const;
};

std::ostream& operator<<(std::ostream& os, const Matriz& m);
#endif
