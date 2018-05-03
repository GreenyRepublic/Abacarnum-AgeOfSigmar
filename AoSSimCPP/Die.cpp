#include "stdafx.h"
#include "Die.h"


Die::Die(int s)
{
	generator = std::default_random_engine(GetTickCount());
	dist = std::uniform_int_distribution<int>(1, s);
}

int Die::Roll(int mods)
{
	return max(dist(generator) + mods, 0);	
}