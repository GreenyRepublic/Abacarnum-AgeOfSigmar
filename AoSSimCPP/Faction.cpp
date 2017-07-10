#include "stdafx.h"
#include "Faction.h"


Faction::Faction(std::string name) : GameEntity(name)
{
	weaponData = new std::map<std::string, Weapon*>;
	modelData = new std::map<std::string, Model*>;
}

Faction::~Faction()
{
	std::cout << "Faction " << Name << " deleted!" << std::endl;
}

void Faction::PrintStats()
{
	PrintHeader(Name, 0);

	//Print models
	std::cout << "|| Models ||" << std::endl;
	std::cout << std::endl;
	Model* m;
	std::pair<std::string, Model*> p;
	for (auto i = modelData->begin(); i != modelData->end(); i++)
	{
		m = i->second;
		std::cout << "|<>| " << m->GetName(false) << std::endl;
	}


	std::cout << "Weapons: " << weaponData->size() << std::endl;
	std::cout << "Models: " << modelData->size() << std::endl;
}

void Faction::AddWeapon(Weapon * weapon)
{
	std::pair<std::string, Weapon*> entry(weapon->GetName(true), weapon);
	weaponData->insert(entry);
}

void Faction::AddModel(Model * model)
{
	std::pair<std::string, Model*> entry(model->GetName(true), model);
	modelData->insert(entry);
}

Weapon * Faction::GetWeapon(std::string name)
{
	try { return weaponData->at(Standardise(name)); }
	catch (std::out_of_range e) { std::cout << "Weapon " << name << " not found! (" << e.what() << ")" << std::endl; }
	return nullptr;
}

Model * Faction::GetModel(std::string name)
{
	try { return modelData->at(Standardise(name)); }
	catch (std::out_of_range e) { std::cout << "Model " << name << " not found! (" << e.what() << ")" << std::endl; }
	return nullptr;
}