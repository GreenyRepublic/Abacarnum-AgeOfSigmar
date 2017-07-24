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
	PrintHeader(ToUpper(Name), 0);

	//Print models
	std::cout << "|| MODELS ||" << std::endl;
	std::cout << std::endl;
	Model* m;
	std::pair<std::string, Model*> p;
	for (auto i = modelData->begin(); i != modelData->end(); i++)
	{
		m = i->second;
		std::cout << "|<>| " << m->GetName(false) << std::endl;
	}
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
	catch (std::out_of_range e) { return nullptr; }
}

Model * Faction::GetModel(std::string name)
{
	try { return modelData->at(Standardise(name)); }
	catch (std::out_of_range e) { return nullptr; }
}