#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "GameEntity.h"
#include "DataWriter.h"
#include "CombatData.h"

/*
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/
class Model : public GameEntity
{

public:
	Model(const std::string name, const size_t move, const size_t save, const size_t bravery, const size_t wounds, const size_t unitsize, const size_t cost, const std::string);
	Model(const Model&);
	~Model();

	Model& operator=(const Model&);

	void AddWeapon(std::shared_ptr<Weapon> weapon);
	void AddKeyword(const std::string keyword);

	void PrintStats();
	virtual void EndTurn();

	//Combat rolls	
	std::vector<WeaponAttack> MeleeAttack(Model&);
	std::vector<WeaponAttack> RangedAttack(Model&);
	size_t TakeDamage(std::vector<Wound> wounds);

	ModelProfile& GetStats() { return modelStats; }
	std::string GetFaction() const { return Faction; }
	int GetUnitSize() const { return unitSize; }
	int GetUnitCost() const { return unitCost; }
	bool HasKeyword( const std::string keyword ) const { return keywords.find(keyword) != keywords.end(); }


private:

	friend class DataWriter;

	//Core Stats
	ModelProfile modelStats;
	std::unordered_set<std::string> keywords;

	//Weapons
	std::vector<std::shared_ptr<Weapon>> meleeWeapons;
	std::vector<std::shared_ptr<Weapon>> rangedWeapons;
	
	//Matched play data
	size_t unitSize;
	size_t unitCost;

	//std::vector<Ability&> Abilities;

};


