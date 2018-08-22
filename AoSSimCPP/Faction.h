#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "Printable.h"

class Faction : Printable
{
private:
	std::unordered_map<std::string, Weapon> weaponData;
	std::unordered_map<std::string, Model> modelData;
	std::string Name;

public:
	Faction(std::string);
	~Faction();

	void PrintStats();

	void AddWeapon(Weapon);
	void AddModel(Model);

	//Get model/weapon profiles by name.
	Weapon* GetWeapon(std::string);
	Model* GetModel(std::string);
};

