/*
 * Console.h
 *
 *  Created on: Sep 23, 2018
 *      Author: root
 */

#ifndef SRC_HELPERS_CONSOLE_H_
#define SRC_HELPERS_CONSOLE_H_

#include <iostream>

class Console {
public:
	Console();
	virtual ~Console();

	static std::ostream& Debug();
	static std::ostream& Out();
};

#endif /* SRC_HELPERS_CONSOLE_H_ */
