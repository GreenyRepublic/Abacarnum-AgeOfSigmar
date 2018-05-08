#include "stdafx.h"
#include "Faction.h"


Faction::Faction(std::string name)
{
}

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
		Model* m = i.second;
		std::cout << "|<>| " << m->GetName() << std::endl;
	}
}

void Faction::AddWeapon(Weapon* weapon)
{
	std::pair<std::string, Weapon*> entry(weapon->GetName(), weapon);
	weaponData.insert(entry);
}

void Faction::AddModel(Model* model)
{
	std::pair<std::string, Model*> entry(model->GetName(), model);
	modelData.insert(entry);
}

Weapon * Faction::GetWeapon(std::string name)
{
	try { return weaponData.at(name); }
	catch (std::out_of_range e) { return nullptr; }
}

Model * Faction::GetModel(std::string name)
{
	try { return modelData.at(name); }
	catch (std::out_of_range e) { return nullptr; }
}