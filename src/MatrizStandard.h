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
	friend class MatrizRala;
public:
	friend MatrizStandard operator+(const Matriz& m1, const Matriz& m2);
	friend MatrizStandard operator-(const Matriz& m1, const Matriz& m2);
	friend MatrizStandard operator*(const Matriz& m1, const Matriz& m2);
	friend MatrizStandard operator*(const float& f, const Matriz& m2);

	MatrizStandard(const unsigned int filas, const unsigned int columnas);
	MatrizStandard(const unsigned int filas, const unsigned int columnas, const float fill);

	static MatrizStandard Identidad(unsigned int tam);
	virtual MatrizStandard operator*(const Matriz& m2);

	virtual void Copy(const Matriz& m);
	virtual void Set(const unsigned int fil, const unsigned int col, const float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;
	virtual Matriz* Escalonada() const;
	virtual Matriz* Extendida(const Vector& v) const;

	virtual ~MatrizStandard();
protected:
	MatrizStandard();
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);

private:
	float** datos;
};


MatrizStandard operator+(const Matriz& m1, const Matriz& m2);
MatrizStandard operator-(const Matriz& m1, const Matriz& m2);
MatrizStandard operator*(const float& f, const Matriz& m2);

#endif /* SRC_MATRIZSTANDARD_H_ */
