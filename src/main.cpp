#include <iostream>
#include "helpers/InputLoader.h"
#include "MatrizStandard.h"

void testSum();
void testMul();
void testGauss();

int main(int argc, char* argv[])
{
	InputLoader inputLoader;

	Matriz* W = inputLoader.Load("../Tests/test_001.txt");

	std::cout << *W;
	//testSum();
	//testMul();
	//testGauss();


	delete W;

	return 0;
}


void testSum()
{
	MatrizStandard m1(3, 3, 0);
	m1.Set(0, 0, 2);
	m1.Set(0, 1, 10);
	m1.Set(0, 2, 0);
	m1.Set(1, 0, 1);
	m1.Set(1, 1, 4);
	m1.Set(1, 2, 12);
	m1.Set(2, 0, 8);
	m1.Set(2, 1, -1);
	m1.Set(2, 2, -8);


	std::cout << m1 << std::endl;

	MatrizStandard m2(3, 3, 0);
	m2.Set(0, 0, -8);
	m2.Set(0, 1, 0);
	m2.Set(0, 2, 1);
	m2.Set(1, 0, 1);
	m2.Set(1, 1, 6);
	m2.Set(1, 2, 21);
	m2.Set(2, 0, -7);
	m2.Set(2, 1, -10);
	m2.Set(2, 2, 4);

	std::cout << m2 << std::endl;

	std::cout << m1 + m2 << std::endl;
}

void testMul()
{
	MatrizStandard m1(3, 2, 0);
	m1.Set(0, 0, 2);
	m1.Set(0, 1, 10);
	m1.Set(1, 0, 1);
	m1.Set(1, 1, 4);
	m1.Set(2, 0, 8);
	m1.Set(2, 1, -1);

	std::cout << m1 << std::endl;

	MatrizStandard m2(2, 2, 0);
	m2.Set(0, 0, -8);
	m2.Set(0, 1, 0);
	m2.Set(1, 0, 1);
	m2.Set(1, 1, 6);

	std::cout << m2 << std::endl;

	std::cout << m1 * m2 << std::endl;
}

void testGauss()
{
	MatrizStandard m1(4, 5, 0);
	m1.Set(0, 0, -8);
	m1.Set(0, 1, 0);
	m1.Set(0, 2, 1);
	m1.Set(0, 3, 2);
	m1.Set(0, 4, 18);
	m1.Set(1, 0, 1);
	m1.Set(1, 1, 6);
	m1.Set(1, 2, 21);
	m1.Set(1, 3, 1);
	m1.Set(1, 4, 1.5);
	m1.Set(2, 0, -7);
	m1.Set(2, 1, -10);
	m1.Set(2, 2, 4);
	m1.Set(2, 3, 10);
	m1.Set(2, 4, -1);
	m1.Set(3, 0, -5);
	m1.Set(3, 1, 11);
	m1.Set(3, 2, 0);
	m1.Set(3, 3, 0);
	m1.Set(3, 4, 5);

	std::cout << m1 << std::endl;

	std::cout << m1.Escalonada() << std::endl;
}
