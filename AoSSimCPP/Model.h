#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "GameEntity.h"
#include "Stats.h"
#include "Printable.h"
#include "Die.h"

/*
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/

class Model : public GameEntity, Printable
{
private:
	//Core Stats
	ModelStats myStats;

	//Weapons
	std::vector<Weapon*> meleeWeapons,
						 rangedWeapons;
	//Metadata
	size_t unitSize,
			 unitCost;

	//Add later
	//std::vector<Abilities&>


public:
	Model(const std::string, const size_t, const size_t, const size_t, const size_t, const size_t, const size_t, const std::string);
	Model(const Model&);
	~Model();

	void AddWeapon(bool, Weapon*);
	void PrintStats();
	void EndTurn();

	//Combat rolls	
	size_t MeleeAttack(Model&);
	size_t RangedAttack(Model&);
	int TakeWounds(int);

	std::string GetFaction() { return Faction; }
	int GetSize() { return unitSize; }
	int GetCost() { return unitCost; }
	ModelStats& GetStats() { return myStats; }
};


