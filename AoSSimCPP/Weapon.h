#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "DataWriter.h"
#include "Die.h"
#include "CombatData.h"

/*
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/

class Weapon : public GameEntity
{
public:
	Weapon(std::string name, 
		size_t range, 
		size_t attacks, 
		size_t tohit, 
		size_t towound, 
		size_t rend, 
		size_t damage, 
		WeaponType type = WeaponType::Melee);
	~Weapon();
	void EndTurn();

	WeaponType GetType () const { return weaponType; }

	WeaponAttack AttackRoll();
	WeaponProfile& GetProfile() { return weaponProfile; }

private:

	friend class DataWriter;
	
	//Stats
	WeaponProfile weaponProfile;
	WeaponType weaponType;
	
	//std::vector<Ability> Abilities;
};

