/*
* InputLoader.h
 *
 *  Created on: Aug 25, 2018
 *      Author: juan
 */

#ifndef INPUTLOADER_H_
#define INPUTLOADER_H_

#include "../MatrizStandard.h"
#include "../Vector.h"

namespace IO
{
	Matriz* Load(const char* path);
	void Save(const char* path, const float& p, const Vector& solucion);
}

#endif /* INPUTLOADER_H_ */
