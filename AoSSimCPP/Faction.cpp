#include "stdafx.h"
#include "Faction.h"

Faction::~Faction()
{
}

void Faction::PrintStats()
{
	PrintHeader(ToUpper(Name), 0);

	//Print models
	std::cout << "|| MODELS ||" << std::endl;
	std::cout << std::endl;
	std::pair<std::string, Model*> p;
	for (auto i : modelData)
	{
		i.second.PrintStats();
	}
	std::cout << std::endl;
}

void Faction::AddWeapon(Weapon weapon)
{
	std::pair<std::string, Weapon> entry(weapon.GetName(), weapon);
	weaponData.insert(entry);
}

void Faction::AddModel(Model model)
{
	std::pair<std::string, Model> entry(model.GetName(), model);
	modelData.insert(entry);
}

Weapon& Faction::GetWeapon(std::string name)
{
	return weaponData.at(name);
}

Model& Faction::GetModel(std::string name)
{
	return modelData.at(name);
}