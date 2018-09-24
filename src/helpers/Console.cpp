/*
 * Console.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: root
 */

#include "Console.h"

NullStream c;

Console::Console() {
	// TODO Auto-generated constructor stub

}

std::ostream& Console::Debug()
{
	//return c;
	return std::cout;
}

std::ostream& Console::Out()
{
	return std::cout;
}

Console::~Console() {
	// TODO Auto-generated destructor stub
}

