#include "stdafx.h"
#include "Die.h"

static std::uniform_int_distribution<int> distribution(1,6);
static std::default_random_engine generator;

int Die::Roll(int modifier)
{
	return distribution(generator) + modifier;
}