
#ifndef SRC_MATRIZLIL_H_
#define SRC_MATRIZLIL_H_

#include "MatrizStandard.h"
#include <set>
#include <vector>
#include "Matriz.h"

class MatrizLIL : public Matriz
{
public:
	MatrizLIL(const unsigned int filas, const unsigned int columnas);

	static MatrizLIL Identidad(unsigned int tam);

	virtual void Set(const unsigned int fil, const unsigned int col, float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;

	virtual Matriz* Copiar() const;

	virtual void Sumar(const Matriz& m2);
	virtual void Restar(const Matriz& m2);
	virtual void Multiplicar(const Matriz& m2);
	virtual void Multiplicar(const float& f);
	virtual void Escalonar();
	virtual void Extender(const Vector& v);


	virtual ~MatrizLIL();
protected:
	MatrizLIL();
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);
	void GaussMultiplicarFila(unsigned int fila, float escalar);
	void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset);

private:
	std::vector<std::vector<std::tuple<int,float> > > datos;
};


#endif /* SRC_MATRIZLIL_H_ */
