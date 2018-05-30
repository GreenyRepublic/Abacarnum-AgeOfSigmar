#include "stdafx.h"
#include "Die.h"

void Die::initDie()
{
	Die::distribution = std::uniform_int_distribution<int>(1, 6);
	Die::generator = std::default_random_engine();
}

int Die::Roll(int modifier)
{
	return Die::distribution(generator) + modifier;
}