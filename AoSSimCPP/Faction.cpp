#include "stdafx.h"
#include "Faction.h"


Faction::Faction(std::string name)
{
	Name = name;
	weaponData = new std::map<std::string, Weapon*>;
	modelData = new std::map<std::string, Model*>;
}

Faction::~Faction()
{
	std::cout << "Faction " << Name << " deleted!" << std::endl;
}

void Faction::addWeapon(Weapon * weapon)
{
	std::pair<std::string, Weapon*> entry(weapon->getName(), weapon);
	weaponData->insert(entry);
}

void Faction::addModel(Model * model)
{
	std::pair<std::string, Model*> entry(model->getName(), model);
	modelData->insert(entry);
}

Weapon * Faction::getWeapon(std::string name)
{
	try { return weaponData->at(name); }
	catch (std::out_of_range e) { std::cout << "Weapon " << name << " not found! (" << e.what() << ")" << std::endl; }
	throw nullptr;
}

Model * Faction::getModel(std::string name)
{
	try { return modelData->at(name); }
	catch (std::out_of_range e) { std::cout << "Model " << name << " not found! (" << e.what() << ")" << std::endl; }
	throw nullptr;
}
