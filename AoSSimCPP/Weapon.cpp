#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(std::string name, uint8_t range, uint8_t attacks, uint8_t tohit, uint8_t towound, uint8_t rend, uint8_t damage)
{
	Name = name;
	myStats.range = range; // This isn't really used right now.
	myStats.attacks = attacks;
	myStats.tohit = tohit;
	myStats.towound = towound;
	myStats.rend = rend;
	myStats.damage = damage;
}

Weapon::~Weapon()
{
}

void Weapon::PrintStats()
{
	std::cout << " |o| " << this->Name << " "
			  << " |- " << "Ra: " << myStats.range << '"'
			  << " | A: " << myStats.attacks
			  << " | H: " << myStats.tohit << "+"
			  << " | W: " << myStats.towound << "+"
			  << " | Re: " << myStats.rend
			  << " | D: " << myStats.damage
			  << std::endl;
}

int Weapon::MakeRoll(uint8_t target)
{
	return (Die::Roll() >= target);
}

//This is longer than it needs to be right now, as I need it to be clean for possible expansion when I add abilities etc.
uint8_t Weapon::GenerateWounds(uint8_t save)
{
	int hits, wounds, saves;
	hits = wounds = saves = 0;
	for (int i = 0; i < myStats.attacks; i++) hits += MakeRoll(myStats.tohit);
	for (int i = 0; i < hits; i++) wounds += MakeRoll(myStats.towound);
	for (int i = 0; i < wounds; i++) saves += ((Die::Roll() + myStats.rend) >= save);

	return (uint8_t) max(0, (wounds - saves) * myStats.damage);
}
