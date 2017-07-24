#include "stdafx.h"
#include "Die.h"
#include <random>
#include <iostream>
#include <cstdlib>


std::default_random_engine generator(GetTickCount());
std::uniform_int_distribution<int> distribution(1, 6);

int Roll()
{
	int r = distribution(generator);
	//std::cout << "Rolled: " << r << std::endl;
	return r;  // generates number in the range 1..6
}
