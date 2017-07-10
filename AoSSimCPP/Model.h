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
	uint8_t Move;
	uint8_t MaxWounds;
	uint8_t Wounds;
	uint8_t Bravery;
	uint8_t Save;

	//Army Composition Stats
	uint8_t UnitSize;
	uint8_t Cost;
	std::string Faction;

	//Weapon Lists
	std::vector<Weapon*> *MeleeWeapons;
	std::vector<Weapon*> *RangedWeapons;

public:
	Model(std::string, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, std::string);
	Model(Model*);
	~Model();

	void AddWeapon(bool, Weapon*);
	void PrintStats();

	//Combat rolls and stuff	
	uint8_t MeleeAttack(Model*);
	void TakeWound();

	uint8_t GetSave() { return Save; }
	std::string GetFaction() { return Faction; }
	uint8_t GetSize() { return UnitSize; }
	uint8_t GetCost() { return Cost; }
};


