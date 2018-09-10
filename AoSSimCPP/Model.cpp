#include "stdafx.h"
#include "Model.h"

//Initialise using raw stat values.
//Used for reading from the model database files.
Model::Model(std::string name,
	size_t move,
	size_t wounds,
	size_t bravery,
	size_t save,
	size_t unitsize,
	size_t cost,
	std::string faction) : GameEntity(name, faction), myStats(move, save, bravery, wounds), unitSize(unitsize), unitCost(cost)
{
}

Model::Model(const Model& ref) : GameEntity(ref.Name, ref.Faction), myStats(ref.myStats), unitSize(ref.unitSize), unitCost(ref.unitCost)
{
	meleeWeapons = ref.meleeWeapons;
	rangedWeapons = ref.rangedWeapons;
}

Model& Model::operator=(const Model & rhs)
{
	return Model(rhs);
}

Model::~Model()
{
}

void Model::AddWeapon(bool melee, std::shared_ptr<Weapon> weapon)
{
	if (melee) meleeWeapons.push_back(weapon);
	else rangedWeapons.push_back(weapon);
}

void Model::EndTurn()
{
}

std::vector<Attack> Model::MeleeAttack(Model& target)
{
	std::vector<Attack> attacks;
	for (auto w : meleeWeapons)
		attacks.push_back(w->AttackRoll());
	return attacks;
}

size_t Model::TakeWounds(size_t count)
{
	size_t taken = min(count, myStats.currentWounds);
	myStats.currentWounds -= taken;
	return count - taken;
}

void Model::PrintStats()
{
	std::cout << std::endl;
	std::cout << "|<>| " << Printable::ToUpper(Name) << " |<>|" << std::endl;
	std::cout << std::endl;
	std::cout << "	|==| STATS |==|" << std::endl;
	std::cout << "	 |o| Move: " << (int)myStats.move << '"' << std::endl;
	std::cout << "	 |o| Wounds: " << (int)myStats.wounds << std::endl;
	std::cout << "	 |o| Bravery: " << (int)myStats.bravery << std::endl;
	std::cout << "	 |o| Save: " << (int)myStats.save << "+" << std::endl;

	std::cout << std::endl;
	std::cout << "	|==| MELEE WEAPONS |==|" << std::endl;
	for (auto w : meleeWeapons) w->PrintStats();

	std::cout << std::endl;
	std::cout << "	|==| RANGED WEAPONS |==|" << std::endl;
	for (auto w : rangedWeapons) w->PrintStats();

	std::cout << std::endl;
	std::cout << "	|==| METADATA |==|" << std::endl;
	std::cout << "	 |o| Unit Size: " << (int)unitSize << std::endl;
	std::cout << "	 |o| Points Cost: " << (int)unitCost << std::endl;
	std::cout << "	 |o| Keywords: " << std::endl;
	std::cout << std::endl;
}