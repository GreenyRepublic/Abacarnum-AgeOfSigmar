#pragma once
#include "stdafx.h"
#include "Unit.h"

class Battle
{
private:
	enum Side {A, B};
	Side Winner;
	int Survivors;

	int Frontage;
	Unit* UnitA;
	Unit* UnitB;
	

public:
	Battle(Unit*, Unit*, int);
	~Battle();

	void Fight();

	int GetSurvivors() { return Survivors; }
	Side GetWinner() { return Winner; }
};

