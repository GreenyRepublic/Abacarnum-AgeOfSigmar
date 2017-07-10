#pragma once
#include "stdafx.h"

#include "GameEntity.h"
#include "Weapon.h"
#include "Model.h"

class Faction : public GameEntity
{
private:
	std::map<std::string, Weapon*> *weaponData;
	std::map<std::string, Model*> *modelData;

public:
	Faction(std::string);
	~Faction();

	//Add pointers to weapon and model profiles.
	void AddWeapon(Weapon*);
	void AddModel(Model*);

	//Just spits out some debug data nothing to see here gents move along.
	void PrintStats();

	//Get model/weapon profiles by name.
	Weapon* GetWeapon(std::string);
	Model* GetModel(std::string);
};

