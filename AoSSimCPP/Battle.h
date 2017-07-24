#pragma once
#include "stdafx.h"
#include "Unit.h"

class Battle
{
private:
	Unit* Winner;
	int Survivors;

	int Frontage;
	Unit* UnitA;
	Unit* UnitB;
	

public:
	Battle(Unit*, Unit*, int);
	~Battle();

	void Fight();

	int GetSurvivors() { return Survivors; }
	Unit* GetWinner() { return Winner; }
};

