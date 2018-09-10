#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "GameEntity.h"
#include "Stats.h"
#include "Printable.h"
#include "Die.h"
#include "Ability.h"

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
	std::vector<std::shared_ptr<Weapon>> meleeWeapons,
						 rangedWeapons;
	//Metadata
	size_t unitSize,
			 unitCost;

	//Add later
	//std::vector<Ability&> Abilities;


public:
	Model(const std::string, const size_t, const size_t, const size_t, const size_t, const size_t, const size_t, const std::string);
	Model(const Model&);
	~Model();

	Model& operator=(const Model&);

	void AddWeapon(bool, std::shared_ptr<Weapon>);
	void PrintStats();
	void EndTurn();

	//Combat rolls	
	std::vector<Attack> MeleeAttack(Model&);
	std::vector<Attack> RangedAttack(Model&);
	size_t TakeWounds(size_t);

	std::string GetFaction() const { return Faction; }
	int GetSize() const { return unitSize; }
	int GetCost() const { return unitCost; }
	ModelStats& GetStats() { return myStats; }
};


