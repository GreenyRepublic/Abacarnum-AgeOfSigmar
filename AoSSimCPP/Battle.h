#pragma once
#include "Unit.h"

typedef struct BattleStats
{
	bool winner;
	std::string sideA;
	std::string sideB;
	int survivors;
	int turns;
} BattleStats;

BattleStats Battle(Unit*, Unit*, int);