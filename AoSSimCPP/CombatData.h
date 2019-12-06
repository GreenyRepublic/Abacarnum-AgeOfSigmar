#pragma once
#include "stdafx.h"
#include "Profiles.h"

//Common data types and data 'bundles' commonly passed about

class Weapon;

enum WeaponType
{
	Melee,
	Ranged
};

enum WoundType
{
	Normal,
	Mortal
};

struct Wound
{
	WoundType Type;
	size_t Count;
};

struct WeaponAttack
{
	WeaponProfile WeaponProfile;
	Wound Wounds;
};

struct UnitAttacks
{
	std::vector<WeaponAttack> WeaponAttacks;
};
