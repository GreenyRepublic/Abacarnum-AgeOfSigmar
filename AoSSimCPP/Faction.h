#pragma once
#include "Weapon.h"
#include "Model.h"

class Faction
{
private:
	std::map<std::string, Weapon*> weaponData;
	std::map<std::string, Model*> modelData;
	std::string Name;

public:
	Faction(std::string);
	~Faction();

	void AddWeapon(Weapon*);
	void AddModel(Model*);

	void PrintStats();

	//Get model/weapon profiles by name.
	Weapon* GetWeapon(std::string);
	Model* GetModel(std::string);
};

