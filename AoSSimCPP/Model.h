#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "GameEntity.h"
#include "PrintData.h"
#include "Die.h"
#include <unordered_set>

/*
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/

class Model : public GameEntity
{

public:
	struct ModelStats
	{
		//Unit Stats
		size_t move { 0 };
		size_t save { 0 };
		size_t bravery { 0 };
		size_t wounds { 0 };
		size_t currentWounds { 0 };

		ModelStats(size_t m, size_t s, size_t b, size_t w) :
			move(m), save(s), bravery(b), wounds(w), currentWounds(w) {};
	};

	Model(const std::string name, const size_t move, const size_t save, const size_t bravery, const size_t wounds, const size_t unitsize, const size_t cost, const std::string);
	Model(const Model&);
	~Model();

	Model& operator=(const Model&);

	void AddWeapon(std::shared_ptr<Weapon> weapon);
	void AddKeyword(const std::string keyword);

	void PrintStats();
	void EndTurn();

	//Combat rolls	
	std::vector<Attack> MeleeAttack(Model&);
	//std::vector<Attack> RangedAttack(Model&);
	size_t TakeWounds(size_t);

	ModelStats& GetStats() { return modelStats; }
	std::string GetFaction() const { return Faction; }
	int GetSize() const { return unitSize; }
	int GetCost() const { return unitCost; }

	bool HasKeyWord( const std::string keyword ) const { return keywords.find(keyword) != keywords.end(); }


private:
	//Core Stats
	ModelStats modelStats;
	std::unordered_set<std::string> keywords;

	//Weapons
	std::vector<std::shared_ptr<Weapon>> meleeWeapons;
	std::vector<std::shared_ptr<Weapon>> rangedWeapons;
	
	//Matched play data
	size_t unitSize;
	size_t unitCost;

	//std::vector<Ability&> Abilities;

};


