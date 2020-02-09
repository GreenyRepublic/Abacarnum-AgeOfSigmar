#pragma once
#include "stdafx.h"
#include "Model.h"
#include "Profiles.h"

// ### Unit: ### //
/* A unit consists of one or more models (as defined by the warscroll). 
 * A unit attacks as a unit, takes casualties as a unit, and takes battleshock tests as a unit
 * Within the scope of this program no other data (position, etc) is needed
 */

class Unit : public GameEntity
{
public:
	Unit(const std::shared_ptr<Model> model, size_t size);
	~Unit();

	UnitAttack MakeMeleeAttack( UnitProfile& target, const int frontage = 10);
	UnitAttack MakeRangedAttack(const UnitProfile& target) {};

	void TakeAttacks(const UnitAttack& attacks);
	void TakeBattleshock();

	void EndTurn();
	void PrintStats() {};

	const UnitProfile& GetUnitProfile() const { return mUnitProfile;  }
	const Model& GetTypeModel() const { return mTypeModel; }
	const size_t GetSurvivingModelsCount() const { return mUnitProfile.currentModels.size(); }
	const size_t GetLosses() const { return mLosses; }	

private:

	friend class DataWriter;
	bool MakeSaves(AttackProfile attack);
	
	UnitProfile mUnitProfile;
	Model mTypeModel;

	size_t mPointValue;
	size_t mMaxBatches;
	size_t mLosses;
};

