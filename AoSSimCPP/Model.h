#pragma once
#include "Weapon.h"
#include "GameEntity.h"
#include "Modifiers.h"
#include <string>
#include <vector>

/*Model: 
*/
class Model : public GameEntity
{
private:
	std::string Faction;

	//Core Stats
	uint16_t Move,
		maxWounds,
		Wounds,
		Bravery,
		Save;

	//Weapons
	std::vector<Weapon&> meleeWeapons,
						rangedWeapons;

	//Metadata
	uint16_t unitSize,
			 Cost;


public:
	Model(Model&);
	Model(std::string, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, std::string);
	~Model();

	void AddWeapon(bool, Weapon&);
	void PrintStats();

	//Combat rolls and stuff	
	int MeleeAttack(Model&);
	int RangedAttack(Model&);
	void TakeWounds(int);
	void EndTurn();

	int GetSave() { return Save; }
	std::string GetFaction() { return Faction; }
	int GetSize() { return unitSize; }
	int GetCost() { return Cost; }
	int GetWounds() { return Wounds; }
	int GetBravery() { return Bravery; }
};


