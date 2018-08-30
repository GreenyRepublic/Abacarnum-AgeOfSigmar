#include "stdafx.h"
#include "Faction.h"

Faction::Faction(std::string name) : Name(name){}

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
		i.second->PrintStats();
	}
	std::cout << std::endl;
}

void Faction::AddWeapon(std::shared_ptr<Weapon> weapon)
{
	std::pair<std::string, std::shared_ptr<Weapon>> entry(weapon->GetName(), weapon);
	weaponData.insert(entry);
}

void Faction::AddModel(std::shared_ptr<Model> model)
{
	modelData.insert(std::pair<std::string, std::shared_ptr<Model>>(model->GetName(), model));
}

std::shared_ptr<Weapon> Faction::GetWeapon(std::string name)
{
	return weaponData.at(name);
}

std::shared_ptr<Model> Faction::GetModel(std::string name)
{
	return modelData.at(name);
}