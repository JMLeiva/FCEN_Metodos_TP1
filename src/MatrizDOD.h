/*
 * MatrizStandard.h
 *
 *  Created on: Aug 27, 2018
 *      Author: juan
 */

#ifndef SRC_MATRIZDOD_H_
#define SRC_MATRIZDOD_H_

#include "MatrizStandard.h"
#include <map>
#include <vector>
#include "Matriz.h"

class MatrizDOD : public Matriz
{
public:
	MatrizDOD(const MatrizDOD& m);
	MatrizDOD(const unsigned int filas, const unsigned int columnas);
	MatrizDOD(const unsigned int filas, const unsigned int columnas, const float fill);

	virtual Matriz* CrearIdentidad(const unsigned int& tam);

	virtual void Set(const unsigned int fil, const unsigned int col, const float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;

	virtual Matriz* Copiar() const;
	virtual unsigned int CantidadNoNulosColumna(unsigned int& col) const;
	virtual void Sumar(const Matriz& m2);
	virtual void Restar(const Matriz& m2);
	virtual void Multiplicar(const Matriz& m2);
	virtual void Multiplicar(const float& f);
	virtual void Escalonar();
	virtual void Extender(const Vector& v);

	virtual ~MatrizDOD();
protected:
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);
	void GaussMultiplicarFila(unsigned int fila, float escalar);
	void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset);
private:
	std::map<unsigned int, std::map<unsigned int, float> > datos;
	std::vector<unsigned int> tamano_columna;
};


#endif /* SRC_MATRIZDOD_H_ */
