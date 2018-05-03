#include "stdafx.h"

#include "Weapon.h"
#include "Die.h"
#include "Model.h"
#include "GameEntity.h"



Weapon::Weapon(std::string name, uint8_t range, uint8_t attacks, uint8_t tohit, uint8_t towound, uint8_t rend, uint8_t damage) : GameEntity(name)
{
	Range = range;
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
			  << " | H: " << ToHit << "+"
			  << " | W: " << ToWound << "+"
			  << " | Re: " << Rend 
			  << " | D: " << Damage 
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
int Weapon::GenerateWounds(int save)
{
	int hits = 0;
	int wounds = 0;
	int saves = 0;

	for (int i = 0; i < Attacks; i++) hits += (int)HitRoll();
	for (int i = 0; i < hits; i++) wounds += (int)WoundRoll();
	for (int i = 0; i < wounds; i++) saves += (int)((Roll() + Rend) >= save);

	return (int) max(0, (wounds - saves) * Damage);
}
