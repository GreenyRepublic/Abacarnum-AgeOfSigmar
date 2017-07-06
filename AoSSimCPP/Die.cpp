#include "stdafx.h"
#include "Die.h"
#include <time.h>
#include <random>
#include <iostream>
#include <cstdlib>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 6);

uint8_t Roll()
{
	return distribution(generator);  // generates number in the range 1..6 
}
