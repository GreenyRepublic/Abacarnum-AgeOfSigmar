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
			  << " | Rend: " << (int)myStats.rend
			  << " | Damage: " << (int)myStats.damage
			  << std::endl;
}

void Weapon::EndTurn()
{

}

int Weapon::MakeRoll(size_t target)
{
	return (Die::Roll() >= target);
}

//This is longer than it needs to be right now, as I need it to be clean for possible expansion when I add abilities etc.
size_t Weapon::GenerateWounds(size_t save)
{
	int hits, wounds, saves;
	hits = wounds = saves = 0;
	for (int i = 0; i < myStats.attacks; i++) hits += MakeRoll(myStats.tohit);
	for (int i = 0; i < hits; i++) wounds += MakeRoll(myStats.towound);
	for (int i = 0; i < wounds; i++) saves += ((Die::Roll() + myStats.rend) >= save);

	return (size_t) max(0, (wounds - saves) * myStats.damage);
}
