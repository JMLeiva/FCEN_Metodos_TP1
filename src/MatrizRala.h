/*
 * MatrizStandard.h
 *
 *  Created on: Aug 27, 2018
 *      Author: juan
 */

#ifndef SRC_MATRIZRALA_H_
#define SRC_MATRIZRALA_H_

#include "MatrizStandard.h"
#include <set>
#include "Matriz.h"

class MatrizRala : public Matriz
{
public:
	MatrizRala(const unsigned int filas, const unsigned int columnas);

	virtual void Set(const unsigned int fil, const unsigned int col, float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;
	virtual Matriz* Escalonada() const;
	virtual Matriz* Extendida(const Vector& v) const;

	virtual ~MatrizRala();
protected:
	MatrizRala();
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);

private:
	std::set<unsigned int> datos;
};

#endif /* SRC_MATRIZRALA_H_ */
