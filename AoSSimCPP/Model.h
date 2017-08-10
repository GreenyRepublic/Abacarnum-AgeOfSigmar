#pragma once
#include "Weapon.h"
#include "GameEntity.h"

#include <string>
#include <vector>

//Header for Model.cpp
class Model : public GameEntity
{
private:
	//Core Stats
	int Move;
	int MaxWounds;
	int Wounds;
	int Bravery;
	int Save;

	//Army Composition Stats
	int UnitSize;
	int Cost;
	std::string Faction;

	//Weapon Lists
	std::vector<Weapon*> MeleeWeapons;
	std::vector<Weapon*> RangedWeapons;

public:
	Model(std::string, int, int, int, int, int, int, std::string);
	Model(Model*);
	~Model();

	void AddWeapon(bool, Weapon*);
	void PrintStats();

	//Combat rolls and stuff	
	int MeleeAttack(Model*);
	void TakeWounds(int);

	int GetSave() { return Save; }
	std::string GetFaction() { return Faction; }
	int GetSize() { return UnitSize; }
	int GetCost() { return Cost; }
	int GetWounds() { return Wounds; }
	int GetBravery() { return Bravery; }
};


