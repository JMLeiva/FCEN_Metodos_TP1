/*
 * Vector.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: root
 */

#include <assert.h>
#include "Vector.h"
#include <cmath>
#include <iomanip>

Vector::Vector(unsigned int size)
{
	this->size = size;
	datos = new float[size];
}

Vector::Vector(unsigned int size, float val)
{
	this->size = size;
	datos = new float[size];

	for(unsigned int i = 0; i < size; i++)
	{
		datos[i] = val;
	}
}

unsigned int Vector::GetTamano() const
{
	return size;
}

float Vector::Get(const unsigned int i) const
{
	assert(i < size);
	return datos[i];
}

void Vector::Set(const unsigned int i, const float v)
{
	assert(i < size);
	datos[i] = v;
}

void Vector::Normalizar()
{
	float sum = 0;

	for(unsigned int i = 0; i < size; i++)
	{
		sum += fabs(datos[i]);
	}

	for(unsigned int i = 0; i < size; i++)
	{
		datos[i] /= sum;
	}
}

Vector::~Vector() {
	delete datos;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
	for(unsigned int i = 0; i < v.GetTamano(); i++)
	{
		os << "| ";

		os << std::setw(12) << v.Get(i);

		os << "     |" << std::endl;
	}

    return os;
}
