#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "PrintData.h"
#include "Die.h"


enum WeaponType
{
	Melee,
	Ranged
};

struct Attack
{
	size_t Wounds;
	size_t Rend;
	size_t Damage;
	WeaponType Type;

	Attack(size_t w, size_t r, size_t d, WeaponType t) : Wounds(w), Rend(r), Damage(d), Type(t) {};
};


/*
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/

class Weapon : public GameEntity
{
public:

	struct WeaponStats
	{
		//Weapon Stats
		size_t range { 0 };
		size_t attacks { 0 };
		size_t tohit { 0 };
		size_t towound { 0 };
		size_t rend { 0 };
		size_t damage { 0 };

		WeaponStats(size_t r, size_t a, size_t h, size_t w, size_t n, size_t d) :
			range(r), attacks(a), tohit(h), towound(w), rend(n), damage(d) {};
	};

	Weapon(std::string name, size_t range, size_t attacks, size_t tohit, size_t towound, size_t rend, size_t damage, WeaponType type = WeaponType::Melee);
	~Weapon();

	void PrintStats();
	void EndTurn();

	WeaponType GetType () const { return weaponType; }

	Attack AttackRoll();
	WeaponStats& GetStats() { return weaponStats; }


private:
	
	//Stats
	WeaponStats weaponStats;
	WeaponType weaponType;
	
	//std::vector<Ability> Abilities;
};

