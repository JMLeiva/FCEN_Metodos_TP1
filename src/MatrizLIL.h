/*
 * MatrizLIL.h
 *
 *  Created on: Sep 25, 2018
 *      Author: jorgedavid
 */

#ifndef SRC_MATRIZLIL_H_
#define SRC_MATRIZLIL_H_

#include "Matriz.h"
#include <vector>
#include <tuple>

class MatrizLIL : public Matriz
{
public:
    MatrizLIL(const MatrizLIL&);
    MatrizLIL(const unsigned int&, const unsigned int&);
    MatrizLIL(const unsigned int&, const unsigned int&, const float&);

    virtual Matriz* CrearIdentidad(const unsigned int&);
    virtual void Set(const unsigned int, const unsigned int, const float);
    virtual float Get(const unsigned int, const unsigned int) const;

    virtual Matriz* Copiar() const;

    virtual void Sumar(const Matriz&);
    virtual void Restar(const Matriz& m2);
    virtual void Multiplicar(const Matriz& m2);
    virtual void Multiplicar(const float& f);
    virtual void Escalonar();
    virtual void Extender(const Vector& v);

    ~MatrizLIL();

protected:
    void GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset);

private:
    std::vector<std::vector<std::tuple<int, float> > > datos;
};


#endif /* SRC_MATRIZLIL_H_ */
