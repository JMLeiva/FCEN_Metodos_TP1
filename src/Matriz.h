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
	bool EstaEscalonada() const;
	Vector ResolverSistema(const Vector& v) const;
	virtual Matriz* Copiar() const =0;

	virtual void Sumar(const Matriz& m2) =0;
	virtual void Restar(const Matriz& m2)  =0;
	virtual void Multiplicar(const Matriz& m2) =0;
	virtual void Multiplicar(const float& f)  =0;
	virtual void Escalonar() =0;
	virtual void Extender(const Vector& v)=0;
	bool EsNulo(const float f) const;

protected:
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);
	void CheckPosicionesValidas(const unsigned int fil, const unsigned int j) const;


	unsigned int filas, columnas;
};

std::ostream& operator<<(std::ostream& os, const Matriz& m);

#endif
