/*
 * MatrizStandard.h
 *
 *  Created on: Aug 27, 2018
 *      Author: juan
 */

#ifndef SRC_MATRIZSTANDARD_H_
#define SRC_MATRIZSTANDARD_H_

#include "matriz.h"

class MatrizStandard : public Matriz
{
public:
	friend MatrizStandard operator+(const Matriz& m1, const Matriz& m2);
	friend MatrizStandard operator*(const Matriz& m1, const Matriz& m2);
	MatrizStandard(const Matriz& m);
	MatrizStandard(const unsigned int filas, const unsigned int columnas);
	MatrizStandard(const unsigned int filas, const unsigned int columnas, const float fill);

	static MatrizStandard Identidad(unsigned int tam);

	virtual void Set(const unsigned int fil, const unsigned int col, const float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;

	virtual ~MatrizStandard();
protected:
	MatrizStandard();
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);

private:
	float* datos;
};


MatrizStandard operator+(const Matriz& m1, const Matriz& m2);
MatrizStandard operator*(const Matriz& m1, const Matriz& m2);

#endif /* SRC_MATRIZSTANDARD_H_ */
