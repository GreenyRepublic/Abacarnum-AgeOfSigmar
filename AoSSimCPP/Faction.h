#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "Printable.h"

class Faction
{
private:
	std::unordered_map<std::string, std::shared_ptr<Weapon>> weaponData;
	std::unordered_map<std::string, std::shared_ptr<Model>> modelData;
	std::string Name;

public:
	Faction(std::string);
	~Faction();

	void PrintStats();

	void AddWeapon(std::shared_ptr<Weapon>);
	void AddModel(std::shared_ptr<Model>);

	//Get model/weapon profiles by name.
	std::shared_ptr<Weapon> GetWeapon(std::string);
	std::shared_ptr<Model> GetModel(std::string);
};

