/*
* InputLoader.h
 *
 *  Created on: Aug 25, 2018
 *      Author: juan
 */

#ifndef INPUTLOADER_H_
#define INPUTLOADER_H_

#include "../matriz.h"


class InputLoader {
public:
	InputLoader();
	Matriz* Load(const char* path);
	virtual ~InputLoader();
};

#endif /* INPUTLOADER_H_ */
