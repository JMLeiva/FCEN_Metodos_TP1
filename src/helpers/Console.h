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

class NullStream : public std::ostream {
    class NullBuffer : public std::streambuf {
    public:
        int overflow( int c ) { return c; }
    } m_nb;
public:
    NullStream() : std::ostream( &m_nb ) {}
};

#endif /* SRC_HELPERS_CONSOLE_H_ */
