#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "GameEntity.h"
#include "DataWriter.h"
#include "CombatData.h"

/*
* Model: Encapsulates a single type of model in Age of Sigmar.
* Contains core stats, weapons and abilities, and functions for taking actions relevant to a single model.
* E.g Attacking with weapons, taking saving rolls.
*/
class Model
{

public:
	Model(const std::string name, const std::set<std::string> keywords, const size_t move, const size_t save, const size_t bravery, const size_t wounds, const size_t unitsize, const size_t cost);
	Model(const Model&);
	~Model();

	Model& operator=(const Model&);

	void AddWeapon(std::shared_ptr<Weapon> weapon);
	void AddKeyword(const std::string keyword);

	void PrintStats();
	virtual void EndTurn();

	//Combat rolls	
	std::vector<AttackProfile> MeleeAttack(ModelProfile& target);
	std::vector<AttackProfile> RangedAttack(ModelProfile& target);

	ModelProfile& GetProfile() { return mModelProfile; }
	int GetBlockSize() const { return mMatchedPlayProfile.blockSize; }
	int GetBlockCost() const { return mMatchedPlayProfile.blockCost; }
	int GetMaxBlocksPerUnit() const { return mMatchedPlayProfile.maxBlocksPerUnit; }

	bool HasKeyword( const std::string keyword ) const { return mModelProfile.keywords.count(keyword) > 0; }


private:

	friend class DataWriter;

	ModelProfile mModelProfile;
	MatchedPlayProfile mMatchedPlayProfile;

	//Weapons
	std::vector<std::shared_ptr<Weapon>> mMeleeWeapons;
	std::vector<std::shared_ptr<Weapon>> mRangedWeapos;
	

	//std::vector<Ability&> Abilities;
};


