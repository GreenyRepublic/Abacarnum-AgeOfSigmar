#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "types/ProfileTypes.h"
#include "types/ActionTypes.h"

// ### Unit: ### //
/* A unit consists of one or more models (as defined by the warscroll). 
 * A unit attacks as a unit, takes casualties as a unit, and takes battleshock tests as a unit
 * Within the scope of this program no other data (position, etc) is needed
 */

class Unit : public GameEntity
{
public:
	Unit(const ModelProfile& modelprofile, const size_t modelcount);
	~Unit();

	UnitAttackAction MakeMeleeAttack( const UnitProfile& target, const int frontage = 10);
	UnitAttackAction MakeRangedAttack( const UnitProfile& target) {};

	void TakeAttacks(const UnitAttackAction& attacks);
	void TakeBattleshock();	

	void EndTurn();
	void PrintStats() {};

	const UnitProfile& GetUnitProfile() const { return mUnitProfile;  }
	const ModelProfile& GetTypeModel() const { return mUnitProfile.typeModel; }
	const size_t GetSurvivingModelsCount() const { return mUnitProfile.currentModels.size(); }
	const size_t GetLosses() const { return mUnitProfile.startingModelCount - mUnitProfile.currentModels.size(); }

private:
	friend class DataWriter;
	bool MakeSaves(AttackAction attack);
	
	UnitProfile mUnitProfile;
	std::vector<WeaponProfile> mMeleeWeaponProfiles;
	std::vector<WeaponProfile> mRangedWeaponProfiles;
};

