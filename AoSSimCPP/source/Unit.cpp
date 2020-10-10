#include "stdafx.h"
#include "Unit.h"
#include "Die.h"


Unit::Unit(const ModelProfile& modelprofile, size_t unitsize) :
	GameEntity(modelprofile.mName),
	mTypeModel(modelprofile),
	mUnitSize(unitsize),
	mModelWoundCounts(unitsize, modelprofile.mWounds),
	mLossesThisTurn(0)
{
}

Unit::~Unit()
{
}

// Attack a target.
// Takes the profile model of the enemy unit and generate attacks.
UnitAttackAction Unit::MakeMeleeAttack(const Unit& target, const int frontage)
{
	UnitAttackAction unitattacks;
	for (auto& model : mModelWoundCounts)
	{
		AttackAction attack;
		for (auto& weapon : mTypeModel.mMeleeWeaponProfiles)
		{
			AttackAction::WeaponAttack weaponAttack(weapon);
			for (size_t i = 0; i < weapon.mAttacks; ++i)
			{
				weaponAttack.mHitRolls.push_back(DieRoll(weapon.mToHit));
				weaponAttack.mHitRolls.push_back(DieRoll(weapon.mToWound));
			}
			attack.mWeaponAttacks.push_back(weaponAttack);
		}
		unitattacks.mAttackProfiles.push_back(attack);
	}

	return unitattacks;
}

void Unit::ReceiveAttack(UnitAttackAction& attack)
{
	//TODO: Feed attack items through modifier stack

	for (const auto& profile : attack.mAttackProfiles)
	{
		for (const auto& weapon : profile.mWeaponAttacks)
		{
			const auto& weaponProfile = weapon.mWeaponProfile;
			for (size_t i = 0; i < weapon.mHitRolls.size(); ++i)
			{
				if (!weapon.mHitRolls[i].RollSucceeded() ||
					!weapon.mWoundRolls[i].RollSucceeded()) 
					continue;

				DieRoll saveRoll(Die::RollD6(), mTypeModel.mSave);
				saveRoll.ModifyRollResult(weaponProfile.mRend);
				if (!saveRoll.RollSucceeded())
				{
					mModelWoundCounts.back() = max(0, mModelWoundCounts.back() - weaponProfile.mDamage);
					if (mModelWoundCounts.back() == 0) mModelWoundCounts.pop_back();
				}
			}
		}
	}
}

void Unit::TakeBattleshock()
{
	
}

void Unit::EndTurn()
{ 

}

bool Unit::MakeSaves(AttackAction attack)
{
	return false;
}