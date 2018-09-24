/*
 * MatrizDOK.h
 *
 *  Created on: Sep 23, 2018
 *      Author: root
 */

#ifndef SRC_MATRIZDOK_H_
#define SRC_MATRIZDOK_H_

#include <map>
#include "Matriz.h"

class MatrizDOK : public Matriz
{
public:
	MatrizDOK(const MatrizDOK& m);
	MatrizDOK(const unsigned int filas, const unsigned int columnas);
	MatrizDOK(const unsigned int filas, const unsigned int columnas, const float fill);

	virtual Matriz* CrearIdentidad(const unsigned int& tam);

	virtual void Set(const unsigned int fil, const unsigned int col, const float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;

	virtual Matriz* Copiar() const;

	virtual void Sumar(const Matriz& m2);
	virtual void Restar(const Matriz& m2);
	virtual void Multiplicar(const Matriz& m2);
	virtual void Multiplicar(const float& f);
	virtual void Escalonar();
	virtual void Extender(const Vector& v);

	virtual ~MatrizDOK();
protected:
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);
	void GaussMultiplicarFila(unsigned int fila, float escalar);
	void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset);
private:

	std::map<std::tuple<unsigned int, unsigned int>, float> datos;
};
#endif /* SRC_MATRIZDOK_H_ */
