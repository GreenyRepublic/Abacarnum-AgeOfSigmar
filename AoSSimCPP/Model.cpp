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
Model::Model(std::string name, uint8_t move, uint8_t wounds, uint8_t bravery, uint8_t save, uint8_t unitsize, uint8_t cost, std::string faction) : GameEntity(name)
{
	Move = move;
	MaxWounds = Wounds = wounds;
	Bravery = bravery;
	Save = save;
	
	UnitSize = unitsize;
	Cost = cost;
	Faction = faction;

	MeleeWeapons = new std::vector<Weapon*>;
	RangedWeapons = new std::vector<Weapon*>;
}

//Initialise using another model as a template.
Model::Model(Model *model) : GameEntity(model->Name)
{
	Move = model-> Move;
	MaxWounds = Wounds = model-> Wounds;
	Bravery = model-> Bravery;
	Save = model-> Save;
	
	UnitSize = model-> UnitSize;
	Cost = model-> Cost;

	MeleeWeapons = new std::vector<Weapon*>;
	RangedWeapons = new std::vector<Weapon*>;

	for (auto w = model->MeleeWeapons->begin(); w != model->MeleeWeapons->end(); w++){ AddWeapon(true, *w); }
	for (auto w = model->RangedWeapons->begin(); w != model->RangedWeapons->end(); w++) { AddWeapon(false, *w); }

	//std::cout << "Model profile " << Name << " created!" << std::endl;
}

Model::~Model()
{
	delete(MeleeWeapons);
	delete(RangedWeapons);
	//std::cout << "Model profile " << Name << " deleted!" << std::endl;
}

void Model::PrintStats()
{

}


uint8_t Model::MeleeAttack(Model* target)
{
	Weapon* weap;
	int wounds = 0;
	for (auto w = MeleeWeapons->begin(); w != MeleeWeapons->end(); w++)
	{
		weap = *w;
		wounds += weap->GenerateWounds(target->GetSave());
	}
	return wounds;
}

void Model::TakeWound()
{
	Wounds--;
}


void Model::AddWeapon(bool melee, Weapon* weapon)
{
	if (melee) MeleeWeapons->push_back(weapon);
	else RangedWeapons->push_back(weapon);
}
