#include "stdafx.h"
#include "Model.h"

//Initialise using raw stat values.
//Used for reading from the model database files.
Model::Model(std::string name,
	size_t move,
	size_t save,
	size_t bravery,
	size_t wounds,
	size_t unitsize,
	size_t cost,
	std::string faction) : GameEntity(name, faction), modelStats(move, save, bravery, wounds), unitSize(unitsize), unitCost(cost)
{
}

Model::Model(const Model& ref) : 
	GameEntity(ref.Name, ref.Faction), 
	modelStats(ref.modelStats), 
	unitSize(ref.unitSize), 
	unitCost(ref.unitCost)
{
	meleeWeapons = ref.meleeWeapons;
	rangedWeapons = ref.rangedWeapons;
}

Model& Model::operator=(const Model & rhs)
{
	return Model(rhs);
}

Model::~Model()
{
}

void Model::AddWeapon(std::shared_ptr<Weapon> weapon)
{
	switch (weapon->GetType())
	{
	case WeaponType::Melee:
		meleeWeapons.push_back(weapon);
		break;
	case WeaponType::Ranged:
		rangedWeapons.push_back(weapon);
		break;
	}
}

void Model::AddKeyword(const std::string keyword)
{
	keywords.insert(keyword);
}

void Model::EndTurn()
{
}

std::vector<WeaponAttack> Model::MeleeAttack(Model& target)
{
	std::vector<WeaponAttack> attacks;
	for (auto& weapon : meleeWeapons)
	{
		WeaponAttack atk = weapon->AttackRoll();
		if (atk.Wounds.Count > 0)
		{
			attacks.push_back(atk);
		}
	}
	return attacks;
}

size_t Model::TakeDamage(std::vector<Wound> wounds)
{
	for (auto& wound : wounds)
	{
		modelStats.currentWounds = max(0, modelStats.currentWounds - wound.Count);
	}
	return modelStats.currentWounds;
}