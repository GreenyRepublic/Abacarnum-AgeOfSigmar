#pragma once
#include "Unit.h"

//HAPPY NOW GARY? >:(

struct BattleStats
{
	bool winner;
	std::string sideA;
	std::string sideB;
	int survivors;
	int turns;
};

BattleStats Battle(Unit*, Unit*, int);