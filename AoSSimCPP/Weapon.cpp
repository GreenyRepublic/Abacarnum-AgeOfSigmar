#include "stdafx.h"

#include "Weapon.h"
#include "Die.h"
#include "Model.h"
#include "GameEntity.h"

/*
* Weapon.cpp: Defines the weapon class.
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/

Weapon::Weapon(std::string name, uint8_t range, uint8_t attacks, uint8_t tohit, uint8_t towound, uint8_t rend, uint8_t damage) : GameEntity(name)
{
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

void Weapon::PrintStats()
{
	std::cout << "   |- " << "Ra: " << (int)Range << '"'
			  << " | A: " << (int)Attacks 
			  << " | H: " << (int)ToHit << "+"
			  << " | W: " << (int)ToWound << "+"
			  << " | Re: " << (int)Rend 
			  << " | D: " << (int)Damage 
			  << std::endl;
}

bool Weapon::HitRoll()
{
	return (Roll() >= ToHit);
}

bool Weapon::WoundRoll()
{
	return (Roll() >= ToWound);
}

//This is longer than it needs to be right now, as I need it to be clean for possible expansion when I add abilities etc.
uint8_t Weapon::GenerateWounds(uint8_t save)
{
	int hits = 0;
	int wounds = 0;
	int saves = 0;

	for (int i = 0; i < Attacks; i++) hits += (int)HitRoll();
	for (int i = 0; i < hits; i++) wounds += (int)WoundRoll();
	for (int i = 0; i < wounds; i++) saves += (int)((Roll() + Rend) >= save);

	return (uint8_t) max(0, (wounds - saves) * Damage);
}
