#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(std::string name, 
	size_t range, 
	size_t attacks, 
	size_t tohit, 
	size_t towound, 
	size_t rend, 
	size_t damage) : GameEntity(name, ""), myStats(range, attacks, tohit, towound, rend, damage)
{
}

Weapon::~Weapon()
{
}

void Weapon::PrintStats()
{
	std::cout << "	 |o| " << Name << " "
			  << " |- " << "Range: " << (int)myStats.range << '"'
			  << " | Attacks: " << (int)myStats.attacks
			  << " | To Hit: " << (int)myStats.tohit << "+"
			  << " | To Wound: " << (int)myStats.towound << "+"
			  << " | Rend: " << -((int)myStats.rend)
			  << " | Damage: " << (int)myStats.damage
			  << std::endl;
}

void Weapon::EndTurn()
{
}

Attack Weapon::AttackRoll()
{
	size_t hits, wounds;
	hits = wounds = 0;
	for (size_t i = 0; i < myStats.attacks; i++) hits += (Die::Roll() >= myStats.tohit);
	for (size_t i = 0; i < hits; i++) wounds += (Die::Roll() >= myStats.towound);
	return Attack(wounds, myStats.rend, myStats.damage);	
}
