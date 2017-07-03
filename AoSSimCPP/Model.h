#pragma once
#include <string>
#include <vector>
#include "Weapon.h"
//Header for Model.cpp
class Model
{
private:
	//Core Stats
	std::string Name;
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

	int SaveRoll();
	std::string getName() { return Name; }
	std::string getFaction() { return Faction; }
};


