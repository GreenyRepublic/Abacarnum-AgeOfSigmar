#include "stdafx.h"
#include "Weapon.h"
#include "Die.h"
#include <string>
#include <iostream>

/*
* Weapon.cpp: Defines the weapon class.
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/

Weapon::Weapon(std::string name, uint8_t range, uint8_t attacks, uint8_t tohit, uint8_t towound, uint8_t rend, uint8_t damage)
{
	Name = name;
	Range = range;
	Attacks = attacks;
	ToHit = tohit;
	ToWound = towound;
	Rend = rend;
	Damage = damage;
	//std::cout << "Weapon profile " << Name << " created!" << std::endl;
}

Weapon::~Weapon()
{
	//std::cout << "Weapon profile " << Name << " deleted!" << std::endl;
}

bool Weapon::HitRoll()
{
	return (Roll() > ToHit);
}

bool Weapon::WoundRoll()
{
	return (Roll() > ToWound);
}
