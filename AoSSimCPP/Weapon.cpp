#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(std::string name, size_t range, size_t attacks, size_t tohit, size_t towound, size_t rend, size_t damage, WeaponType type)
	: GameEntity(name, ""), 
	weaponProfile(range, attacks, tohit, towound, rend, damage), 
	weaponType(type)
{}

Weapon::~Weapon()
{
}

void Weapon::EndTurn()
{
}

WeaponAttack Weapon::AttackRoll()
{
	size_t hits = 0;
	size_t wounds = 0;
	for (size_t i = 0; i < weaponProfile.attacks; i++)
	{
		hits += (Die::RollD6() >= weaponProfile.tohit);
	}
	for (size_t i = 0; i < hits; i++)
	{
		wounds += (Die::RollD6() >= weaponProfile.towound);
	}

	WeaponAttack attack;
	attack.WeaponProfile = weaponProfile;
	attack.Wounds.Count = wounds;
	attack.Wounds.Type = WoundType::Normal;

	return attack;
}
