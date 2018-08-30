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
	std::string faction) : GameEntity(name, faction), myStats(move, save, bravery, wounds), unitSize(unitsize), unitCost(cost){}

Model::Model(const Model& ref)
{
	Model(ref.Name,
		ref.myStats.move,
		ref.myStats.wounds,
		ref.myStats.bravery,
		ref.myStats.save,
		ref.unitSize,
		ref.unitCost,
		ref.Faction);
}

Model::Model()
{
}

Model& Model::operator=(const Model & rhs)
{
	return Model(rhs);
}

Model::~Model()
{
	std::cout << Name << " dstr" << std::endl;
}

void Model::PrintStats()
{
	std::cout << std::endl;
	std::cout << "|<>| " << ToUpper(Name) << " |<>|" << std::endl;
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

void Model::EndTurn()
{
}

size_t Model::MeleeAttack(Model& target)
{
	size_t wounds = 0;
	for (auto w : meleeWeapons) wounds += w->GenerateWounds(target.myStats.save);
	return wounds;
}

size_t Model::TakeWounds(size_t count)
{
	int taken = min(myStats.currentWounds, count);
	return count - taken;
}

void Model::AddWeapon(bool melee, std::shared_ptr<Weapon> weapon)
{
	if (melee) meleeWeapons.push_back(weapon);
	else rangedWeapons.push_back(weapon);
}
