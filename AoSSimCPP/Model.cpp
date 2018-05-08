#include "stdafx.h"

#include "Model.h"
#include "Weapon.h"
#include "Die.h"
#include "GameEntity.h"

//Initialise using raw stat values.
//Used for reading from the model database files.
Model::Model(std::string name, 
	uint16_t move, 
	uint16_t wounds, 
	uint16_t bravery, 
	uint16_t save, 
	uint16_t unitsize, 
	uint16_t cost, 
	std::string faction) : GameEntity(name, faction)
{
	myStats.move = move;
	myStats.wounds = myStats.currentWounds = wounds;
	myStats.bravery = bravery;
	myStats.save = save;
	
	unitSize = unitsize;
	unitCost = cost;
	Faction = faction;
}

//Copy an existing model

/*Model::Model(const Model& reference)
{
	myStats = reference.myStats;
	unitSize = reference.unitSize;
	unitCost = reference.unitCost;
	Faction = reference.Faction;
}*/

Model::~Model()
{
}

void Model::PrintStats()
{
	std::cout << "|<>| " << ToUpper(Name) << " |<>|" << std::endl;
	std::cout << "  || " << Faction << " ||  " << std::endl;
	std::cout << std::endl;
	std::cout << "|==| STATS |==|" << std::endl;
	std::cout << " |o| Move: " << (int)myStats.move << '"' << std::endl;
	std::cout << " |o| Wounds: " << (int)myStats.wounds << std::endl;
	std::cout << " |o| Bravery: " << (int)myStats.bravery << std::endl;
	std::cout << " |o| Save: " << (int)myStats.save << "+" << std::endl;
	
	std::cout << std::endl;
	std::cout << "|==| MELEE WEAPONS |==|" << std::endl;
	for (auto w : meleeWeapons) w->PrintStats();

	std::cout << std::endl;
	std::cout << "|==| RANGED WEAPONS |==|" << std::endl;
	for (auto w : rangedWeapons) w->PrintStats();

	std::cout << std::endl;
	std::cout << "|==| METADATA |==|" << std::endl;
	std::cout << " |o| Unit Size: " << (int)unitSize << std::endl;
	std::cout << " |o| Points Cost: " << (int)unitCost << std::endl;
	std::cout << " |o| Army Role: " << std::endl;
}


int Model::MeleeAttack(Model& target)
{
	int wounds = 0;
	for (auto w : meleeWeapons) wounds += w->GenerateWounds(target.myStats.save);
	return wounds;
}

void Model::TakeWounds(int count)
{
	myStats.wounds -= count;
}

void Model::AddWeapon(bool melee, Weapon* weapon)
{
	if (melee) meleeWeapons.push_back(weapon);
	else rangedWeapons.push_back(weapon);
}
