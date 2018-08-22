#pragma once
#include "stdafx.h"
#include "Unit.h"

//HAPPY NOW GARY? >:(

struct BattleStats
{
	std::string Winner;
	int survivors;
	int turns;
};

BattleStats Battle(Unit&, Unit&, int);