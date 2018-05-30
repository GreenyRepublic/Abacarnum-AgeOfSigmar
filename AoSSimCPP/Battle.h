#pragma once
#include "Unit.h"

//HAPPY NOW GARY? >:(


enum Side {
	SideA = 0,
	SideB
};
struct BattleStats
{
	Side Winner;
	int survivors;
	int turns;
};

BattleStats Battle(Unit&, Unit&, int);