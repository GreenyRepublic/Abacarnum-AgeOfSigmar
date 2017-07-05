#pragma once
#include "stdafx.h"

#include "Weapon.h"
#include "Model.h"

class Faction
{
private:
	std::string Name;
	std::map<std::string, Weapon*> *weaponData;
	std::map<std::string, Model*> *modelData;

public:
	Faction(std::string);
	~Faction();

	//Add pointers to weapon and model profiles.
	void addWeapon(Weapon*);
	void addModel(Model*);

	//Just spits out some debug data nothing to see here gents move along.
	void PrintStats();

	//Get model/weapon profiles by name.
	Weapon* getWeapon(std::string);
	Model* getModel(std::string);
};

