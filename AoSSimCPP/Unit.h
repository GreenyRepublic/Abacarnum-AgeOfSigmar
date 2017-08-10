#pragma once
#include "stdafx.h"

#include "Model.h"

class Unit
{
private:
	std::vector<Model> Models;
	int PointsValue;
	int Mult;
	int Losses;

	//Since units in AoS are homogenuous (for now), we can store a reference to a 'type' model.
	Model* TypeModel;

	std::string Name;


public:
	Unit(Model*, int);
	~Unit();

	int MeleeAttack(Unit* target, int frontage);
	bool TakeWounds(int count);
	bool Battleshock();

	void NewTurn();
	int LiveCount() { return Models.size(); }
	std::string GetName() { return Name; }
	int GetLosses() { return Losses; }
};

