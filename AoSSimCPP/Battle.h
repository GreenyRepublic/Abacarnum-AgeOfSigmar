#pragma once
#include "Unit.h"

//HAPPY NOW GARY? >:(

struct BattleStats
{
	std::string Winner;
	std::string Loser;
	int survivors;
	int turns;
};

BattleStats Battle(Unit*, Unit*, int);