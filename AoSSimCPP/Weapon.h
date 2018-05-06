#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "Die.h"
#include "Model.h"
#include "Stats.h"

#include <string>
#include <vector>


/*
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/
class Weapon : public GameEntity
{
private:
	
	//Stats
	WeaponStats myStats;

	//To be added
	//std::vector<Ability> Abilities;

	int MakeRoll(uint8_t);

public:
	Weapon(std::string, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	~Weapon();

	void PrintStats();
	void EndTurn();

	uint8_t GenerateWounds(uint8_t);
};

