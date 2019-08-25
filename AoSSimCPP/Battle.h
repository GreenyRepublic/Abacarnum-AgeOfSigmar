#pragma once
#include "stdafx.h"
#include "Unit.h"

//HAPPY NOW GARY? >:(

struct BattleStats
{
	std::string Winner;
	size_t Survivors;
	size_t Turns;
};

class Battle
{
public:
	Battle();
	~Battle();
	BattleStats FightBattle(Unit unitA, Unit unitB, int frontage = 10);

private:
};
