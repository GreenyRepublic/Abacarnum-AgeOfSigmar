#include "stdafx.h"

#include "Weapon.h"



Weapon::Weapon(std::string name, uint8_t range, uint8_t attacks, uint8_t tohit, uint8_t towound, uint8_t rend, uint8_t damage) : GameEntity(name)
{
	Range = range; // This isn't really used right now.
	Attacks = attacks;
	toHit = tohit;
	toWound = towound;
	Rend = rend;
	Damage = damage;
}

Weapon::~Weapon()
{
}

void Weapon::PrintStats()
{
	std::cout << " |- " << "Ra: " << Range << '"'
			  << " | A: " << Attacks 
			  << " | H: " << toHit << "+"
			  << " | W: " << toWound << "+"
			  << " | Re: " << Rend 
			  << " | D: " << Damage 
			  << std::endl;
}

int Weapon::MakeRoll(uint8_t target)
{
	int target;
	if (mods.tohit.first == Add) target = toHit + mods.hit.second;
	if (mods.tohit.first == Divide) target = toHit / mods.hit.second;
	if (mods.tohit.first == Multiply) target = toHit * mods.hit.second;
	return (Die::Roll() >= target);
}

//This is longer than it needs to be right now, as I need it to be clean for possible expansion when I add abilities etc.
uint8_t Weapon::GenerateWounds(uint8_t save, Modifiers mods)
{
	int hits = 0;
	int wounds = 0;
	int saves = 0;

	for (int i = 0; i < Attacks; i++) hits += MakeRoll(mods, toHit);
	for (int i = 0; i < hits; i++) wounds += MakeRoll(mods, toWound);
	for (int i = 0; i < wounds; i++) saves += ((Die::Roll() + Rend) >= save);

	return (uint8_t) max(0, (wounds - saves) * Damage);
}
