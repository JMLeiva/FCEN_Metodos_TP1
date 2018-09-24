
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

	virtual void Set(const unsigned int fil, const unsigned int col, float val);
	virtual float Get(const unsigned int fil, const unsigned int col) const;
	virtual Matriz* Escalonada() const;
	virtual Matriz* Extendida(const Vector& v) const;

	virtual MatrizStandard operator*(const Matriz& m2);
	MatrizStandard* CalcularGradoOptimizado();

	virtual ~MatrizLIL();
protected:
	MatrizLIL();
	virtual void SetTamano(const unsigned int filas, const unsigned int columnas);

private:
	std::vector<std::vector<std::tuple<int,float> > > datos;
};


#endif /* SRC_MATRIZLIL_H_ */
