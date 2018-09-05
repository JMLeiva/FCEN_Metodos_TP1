#ifndef MATRIZ_H_
#define MATRIZ_H_

#include "Vector.h"
#include <iostream>

class MatrizStandard;

class Matriz
{
public:
	Matriz(const unsigned int filas, const unsigned int columnas);
	virtual ~Matriz();

	unsigned int GetCantidadFilas() const;
	unsigned int GetCantidadColumnas() const;
	virtual void Set(const unsigned int fil, const unsigned int col, const float val) = 0;
	virtual float Get(const unsigned int fil, const unsigned int col) const= 0;
	virtual Matriz* Escalonada() const = 0;
	virtual Matriz* Extendida(const Vector& v) const = 0;
	bool EstaEscalonada() const;
	Vector ResolverSistema(const Vector& v) const;
	virtual MatrizStandard operator*(const Matriz& m2) =0;

	static void Sumar(const Matriz& m1, const Matriz& m2, Matriz* out);
	static void Restar(const Matriz& m1, const Matriz& m2, Matriz* out);
	static void Multiplicar(const Matriz& m1, const Matriz& m2, Matriz* out);
	static void Multiplicar(const float& f, const Matriz& m, Matriz* out);
	static void Escalonar(Matriz& m);
	static void Extender(const Matriz& m, const Vector& v, Matriz& out);

protected:
	Matriz();
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);

	void CheckPosicionesValidas(const unsigned int fil, const unsigned int j) const;
	unsigned int IndiceParaPosiciones(const unsigned int i, const unsigned int j) const;

private:
	void GaussMultiplicarFila(unsigned int fila, float escalar);
	void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar);

	unsigned int filas, columnas;
};

std::ostream& operator<<(std::ostream& os, const Matriz& m);

#endif
