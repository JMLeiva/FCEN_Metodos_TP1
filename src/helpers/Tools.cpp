/*
 * Tools.cpp
 *
 *  Created on: Sep 24, 2018
 *      Author: root
 */

#include "Tools.h"
#include <cmath>

const float EPSILON = 0.000001;

namespace Tools
{


	bool EsNulo(const float& f)
	{
		return fabs(f) < EPSILON;
	}

	bool Iguales(const float& f1, const float& f2)
	{
		return EsNulo(f1 - f2);
	}

}

