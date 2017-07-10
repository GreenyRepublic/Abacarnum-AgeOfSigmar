#pragma once
#include "stdafx.h"

#include "Model.h"

class Unit
{
private:
	std::vector<Model*> *Models;
	uint8_t PointsValue;
	uint8_t Mult;
	uint8_t Losses;

	//Since units in AoS are homogenuous (for now), we can store a reference to a 'type' model.
	Model* TypeModel;

public:
	Unit(Model*, int);
	~Unit();
	void MeleeAttack(Unit target, int frontage);
	void TakeWounds(int count);
	void Battleshock();
};

