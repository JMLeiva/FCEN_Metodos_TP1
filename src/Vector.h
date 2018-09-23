/*
 * Vector.h
 *
 *  Created on: Sep 23, 2018
 *      Author: root
 */

#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#include <iostream>

class Vector {
public:
	Vector(unsigned int size);
	Vector(unsigned int size, float val);

	void Normalizar();

	unsigned int GetTamano() const;
	float Get(const unsigned int i) const;
	void Set(const unsigned int i, const float v);
	virtual ~Vector();

private:
	unsigned int size;
	float* datos;
};

std::ostream& operator<<(std::ostream& os, const Vector& m);

#endif /* SRC_VECTOR_H_ */
