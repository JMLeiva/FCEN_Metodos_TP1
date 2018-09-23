/*
 * MatrizStandard.h
 *
 *  Created on: Aug 27, 2018
 *      Author: juan
 */

#ifndef SRC_MATRIZSTANDARD_H_
#define SRC_MATRIZSTANDARD_H_

#include "Matriz.h"

class MatrizStandard : public Matriz
{
public:
	MatrizStandard(const MatrizStandard& m);
	MatrizStandard(const unsigned int filas, const unsigned int columnas);
	MatrizStandard(const unsigned int filas, const unsigned int columnas, const float fill);

	static MatrizStandard Identidad(unsigned int tam);

	virtual void Set(const unsigned int fil, const unsigned int col, const float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;

	virtual Matriz* Copiar() const;

	virtual void Sumar(const Matriz& m2);
	virtual void Restar(const Matriz& m2);
	virtual void Multiplicar(const Matriz& m2);
	virtual void Multiplicar(const float& f);
	virtual void Escalonar();
	virtual void Extender(const Vector& v);

	virtual ~MatrizStandard();
protected:
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);
	void GaussMultiplicarFila(unsigned int fila, float escalar);
	void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset);
private:
	float** datos;
};

#endif /* SRC_MATRIZSTANDARD_H_ */
