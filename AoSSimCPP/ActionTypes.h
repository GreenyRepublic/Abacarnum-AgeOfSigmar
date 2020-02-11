#pragma once
#include "ProfileTypes.h"
#include <set>


struct BattleshockProfile
{
	size_t losses;
	BattleshockProfile(size_t losses) :
		losses(losses) {};
};

struct AttackAction
{
	WeaponProfile attackingWeapon{ WeaponProfile() };
	ModelProfile attackingModel{ ModelProfile() };
	ModelProfile defendingModel{ ModelProfile() };

	size_t hits{ 0 };
	size_t wounds{ 0 };
	size_t mortalWounds{ 0 };

	AttackAction() {};
	AttackAction(WeaponProfile& weapon, ModelProfile& attackmodel, ModelProfile& defmodel, size_t hits, size_t wounds, size_t mortalwounds) :
		attackingWeapon(weapon),
		attackingModel(attackmodel),
		defendingModel(defmodel) {};
};

struct UnitAttackAction
{
	UnitProfile UnitProfile;
	std::vector<AttackAction> AttackProfiles;
};

