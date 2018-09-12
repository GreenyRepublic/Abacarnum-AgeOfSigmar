#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "Ability.h"
#include "Stats.h"
#include "Printable.h"
#include "Die.h"

/*
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/
class Weapon : public GameEntity
{
private:
	
	//Stats
	AttackType attackType;
	WeaponStats myStats;

	//To be added
	//std::vector<Ability> Abilities;

public:
	Weapon(std::string, size_t, size_t, size_t, size_t, size_t, size_t, AttackType);
	~Weapon();

	void PrintStats();
	void EndTurn();

	void SetType(AttackType t) { attackType = t; }
	Attack AttackRoll();
	WeaponStats& GetStats() { return myStats; }
};

