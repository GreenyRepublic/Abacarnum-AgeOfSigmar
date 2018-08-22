#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "Stats.h"
#include "Printable.h"
#include "Die.h"

/*
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/
class Weapon : public GameEntity, Printable
{
private:
	
	//Stats
	WeaponStats myStats;

	//To be added
	//std::vector<Ability> Abilities;

	int MakeRoll(size_t);

public:
	Weapon(std::string, size_t, size_t, size_t, size_t, size_t, size_t);
	~Weapon();

	void PrintStats();
	void EndTurn();

	size_t GenerateWounds(size_t);
};

