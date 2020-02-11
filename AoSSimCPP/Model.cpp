#include "stdafx.h"
#include "Model.h"

//Initialise using raw stat values.
//Used for reading from the model database files.


Model::Model(
	const std::string name,
	const std::set<std::string> keywords,
	const size_t move,
	const size_t save,
	const size_t bravery,
	const size_t wounds,
	const size_t unitsize,
	const size_t cost) :
	mModel(name, move, save, bravery, wounds, keywords),
	mMatchedPlayProfile(unitsize, 4, cost)
{
}

Model::Model(const Model& ref) :
	mModel(ref.mModel), 
	mMatchedPlayProfile(ref.mMatchedPlayProfile),
	mMeleeWeapons(ref.mMeleeWeapons),
	mRangedWeapos(ref.mRangedWeapos)
{
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
		mMeleeWeapons.push_back(weapon);
		break;
	case WeaponType::Ranged:
		mRangedWeapos.push_back(weapon);
		break;
	}
}

void Model::AddKeyword(const std::string keyword)
{
	mModel.keywords.insert(keyword);
}

void Model::EndTurn()
{
}

std::vector<AttackProfile> Model::MeleeAttack(Model& target)
{
	std::vector<AttackProfile> attacks;
	for (auto& weapon : mMeleeWeapons)
	{
		 auto attack = weapon->AttackRoll();
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