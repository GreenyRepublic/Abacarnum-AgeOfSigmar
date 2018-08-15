#pragma once
#include "Weapon.h"
#include "GameEntity.h"
#include "Stats.h"
#include "Die.h"

/*
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/

class Model : public GameEntity
{
private:
	//Core Stats
	ModelStats myStats;

	//Weapons
	std::vector<std::string> meleeWeapons,
						rangedWeapons;
	//Metadata
	uint16_t unitSize,
			 unitCost;

	//Add later
	//std::vector<Abilities&>


public:
	Model(const std::string, const uint16_t, const uint16_t, const uint16_t, const uint16_t, const uint16_t, const uint16_t, const std::string);
	~Model();

	void AddWeapon(bool, std::string);
	void PrintStats();

	//Combat rolls	
	size_t MeleeAttack(Model&);
	size_t RangedAttack(Model&);
	void TakeWounds(int);
	void EndTurn();

	std::string GetFaction() { return Faction; }
	int GetSize() { return unitSize; }
	int GetCost() { return unitCost; }
	ModelStats& GetStats() { return myStats; }
};


