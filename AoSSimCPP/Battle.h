#pragma once
#include "stdafx.h"
#include "Unit.h"

//HAPPY NOW GARY? >:(

struct BattleStats
{
	std::string Winner;
	size_t survivors,
		turns;
};

BattleStats Battle(Unit, Unit, int);