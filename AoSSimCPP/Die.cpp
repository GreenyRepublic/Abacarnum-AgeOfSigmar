#include "stdafx.h"
#include "Die.h"

std::uniform_int_distribution<unsigned int> Die::dieDistribution = std::uniform_int_distribution<unsigned int>(1,6);
std::default_random_engine Die::dieGenerator;

int Die::RollD6()
{
	return dieDistribution(dieGenerator);
}

int Die::RollD3()
{
	return static_cast<int>(ceil(RollD6() * 0.5));
}