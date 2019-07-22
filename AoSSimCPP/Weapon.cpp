#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(std::string name, 
	size_t range, 
	size_t attacks, 
	size_t tohit, 
	size_t towound, 
	size_t rend, 
	size_t damage,
	WeaponType type) : GameEntity(name, ""), weaponStats(range, attacks, tohit, towound, rend, damage), weaponType(type)
{}

Weapon::~Weapon()
{
}

void Weapon::PrintStats()
{
	std::cout << "	 |o| " << Name << " "
			  << " |- " << "Range: " << (int)weaponStats.range << '"'
			  << " | Attacks: " << (int)weaponStats.attacks
			  << " | To Hit: " << (int)weaponStats.tohit << "+"
			  << " | To Wound: " << (int)weaponStats.towound << "+"
			  << " | Rend: " << -((int)weaponStats.rend)
			  << " | Damage: " << (int)weaponStats.damage
			  << std::endl;
}

void Weapon::EndTurn()
{
}

Attack Weapon::AttackRoll()
{
	size_t hits, wounds;
	hits = wounds = 0;
	for (size_t i = 0; i < weaponStats.attacks; i++) hits += (Die::RollD6() >= weaponStats.tohit);
	for (size_t i = 0; i < hits; i++) wounds += (Die::RollD6() >= weaponStats.towound);
	return Attack(wounds, weaponStats.rend, weaponStats.damage, weaponType);	
}
