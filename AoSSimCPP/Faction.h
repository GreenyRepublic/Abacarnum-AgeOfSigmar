#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "PrintData.h"

class Faction
{
public:
	Faction(std::string);
	~Faction();

	void PrintStats();

	void AddWeapon(std::shared_ptr<Weapon>);
	void AddModel(std::shared_ptr<Model>);

	//Get model/weapon profiles by name.
	std::shared_ptr<Weapon> GetWeapon(std::string);
	std::shared_ptr<Model> GetModel(std::string);

	int operator<(const Faction& rhs) { return Name < rhs.Name; }

private:
	std::unordered_map<std::string, std::shared_ptr<Weapon>> weaponData;
	std::unordered_map<std::string, std::shared_ptr<Model>> modelData;
	std::string Name;

};

