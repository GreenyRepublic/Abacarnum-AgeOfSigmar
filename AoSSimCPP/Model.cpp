#include "stdafx.h"
#include "Model.h"
#include "Weapon.h"
#include "Die.h"
#include <string>
#include <vector>
#include <iostream>

/*
* Model.cpp: Defines the model class.
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, pointers to weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/ 

//Initialise using raw stat values.
Model::Model(std::string name, uint8_t move, uint8_t wounds, uint8_t bravery, uint8_t save, uint8_t unitsize, uint8_t cost, std::string faction)
{
	Name = name;
	Move = move;
	Wounds = wounds;
	Bravery = bravery;
	Save = save;
	
	UnitSize = unitsize;
	Cost = cost;
	Faction = faction;

	MeleeWeapons = new std::vector<Weapon*>;
	RangedWeapons = new std::vector<Weapon*>;
}

//Initialise using another model as a template.
Model::Model(Model *model)
{
	Name = model-> Name;
	Move = model-> Move;
	Wounds = model-> Wounds;
	Bravery = model-> Bravery;
	Save = model-> Save;
	
	UnitSize = model-> UnitSize;
	Cost = model-> Cost;

	MeleeWeapons = new std::vector<Weapon*>;
	RangedWeapons = new std::vector<Weapon*>;

	//std::cout << "Model profile " << Name << " created!" << std::endl;
}

Model::~Model()
{
	delete(MeleeWeapons);
	delete(RangedWeapons);
	//std::cout << "Model profile " << Name << " deleted!" << std::endl;
}

int Model::SaveRoll()
{
	return Roll();
}

void Model::AddWeapon(bool melee, Weapon* weapon)
{
	if (melee) MeleeWeapons->push_back(weapon);
	else RangedWeapons->push_back(weapon);
}

