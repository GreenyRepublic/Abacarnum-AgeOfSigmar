#pragma once
#include "types/ProfileTypes.h"
#include "Die.h"
#include <set>


struct BattleshockProfile
{
	size_t mLosses;
	BattleshockProfile(size_t losses) :
		mLosses(losses) {};
};

// A unit generates attacks and sends it to a target
struct AttackAction
{
	struct WeaponAttack
	{
		WeaponAttack(const WeaponProfile& weaponprofile)
			: mWeaponProfile(weaponprofile) {};
		WeaponProfile mWeaponProfile;
		std::vector<DieRoll> mHitRolls;
		std::vector<DieRoll> mWoundRolls;
	};
	AttackAction() {};
	ModelProfile mAttackingModel{};
	ModelProfile mTargetModel{};
	std::vector<WeaponAttack> mWeaponAttacks;

	std::size_t mMortalWounds{ 0 };
};

// Unit takes save rolls against wounds
struct SaveAction
{
	std::vector<WeaponProfile> mAttackingWeaponProfiles;
	std::vector<DieRoll> mSaveRolls;
};

struct UnitAttackAction
{
	std::vector<AttackAction> mAttackProfiles;
};