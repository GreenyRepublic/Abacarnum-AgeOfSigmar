#include "stdafx.h"

#include "Model.h"
#include "Weapon.h"
#include "Die.h"
#include "GameEntity.h"

/*
* Model.cpp: Defines the model class.
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, pointers to weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/ 

//Initialise using raw stat values.
//Used for reading from the model databases.
Model::Model(std::string name, 
	uint16_t move, 
	uint16_t wounds, 
	uint16_t bravery, 
	uint16_t save, 
	uint16_t unitsize, 
	uint16_t cost, 
	std::string faction) : GameEntity(name)
{
	Move = move;
	maxWounds = Wounds = wounds;
	Bravery = bravery;
	Save = save;
	
	unitSize = unitsize;
	Cost = cost;
	Faction = faction;
}

Model::~Model()
{
	//std::cout << "Model profile " << Name << " deleted!" << std::endl;
}

void Model::PrintStats()
{
	std::cout << "|<>| " << ToUpper(Name) << " |<>|" << std::endl;
	std::cout << "  || " << Faction << " ||  " << std::endl;
	std::cout << std::endl;
	std::cout << "|==| STATS |==|" << std::endl;
	std::cout << " |o| Move: " << (int)Move << '"' << std::endl;
	std::cout << " |o| Wounds: " << (int)Wounds << std::endl;
	std::cout << " |o| Bravery: " << (int)Bravery << std::endl;
	std::cout << " |o| Save: " << (int)Save << "+" << std::endl;
	
	std::cout << std::endl;
	std::cout << "|==| MELEE WEAPONS |==|" << std::endl;
	for (auto w : meleeWeapons)
	{
		std::cout << " |o| " << w.GetName(false) << std::endl;
		w.PrintStats();
	}

	std::cout << std::endl;
	std::cout << "|==| RANGED WEAPONS |==|" << std::endl;
	for (auto w : rangedWeapons)
	{
		std::cout << " |o| " << w.GetName(false) << std::endl;
	}
	std::cout << std::endl;

	std::cout << "|==| METADATA |==|" << std::endl;
	std::cout << " |o| Unit Size: " << (int)unitSize << std::endl;
	std::cout << " |o| Points Cost: " << (int)Cost << std::endl;
	std::cout << " |o| Army Role: " << std::endl;
}


int Model::MeleeAttack(Model& target)
{
	int wounds = 0;
	for (auto w : meleeWeapons)
	{
		wounds += w.GenerateWounds(target.GetSave());
	}
	return wounds;
}

void Model::TakeWounds(int count)
{
	Wounds -= count;
}

void Model::AddWeapon(bool melee, Weapon& weapon)
{
	if (melee) meleeWeapons.push_back(weapon);
	else rangedWeapons.push_back(weapon);
}
