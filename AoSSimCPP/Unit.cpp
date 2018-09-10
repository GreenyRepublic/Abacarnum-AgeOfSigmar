#include "stdafx.h"
#include "Unit.h"


Unit::Unit(const std::shared_ptr<Model> model, size_t count) : GameEntity(model->GetName(), model->GetFaction())
{
	for (int i = 0; i < count; i++) 
	{ 
		Models.push_back(*model);
	}
	typeModel = model;
	Name = model->GetName();
	pointValue = model->GetCost() * (count/model->GetSize());
	Losses = 0;
}

Unit::~Unit()
{
}

//Attack a target.
//Takes the profile model of the enemy unit, tests against it to generate wounds and slaps them on the enemy unit.
void Unit::MeleeAttack(Unit& target, int frontage)
{
	auto type = *target.typeModel;
	size_t i = 0;
	for (auto& m : Models)
	{
		if (i == frontage) break;
		target.ResolveHits(m.MeleeAttack(type));
		i++;
	}
}

//Allocates wounds.
void Unit::ResolveHits(std::vector<Attack> attacks)
{
	//TODO: Feed attack items through modifier stack
	
	for (auto atk : attacks)
	{
		size_t damage = 0;
		for (size_t i = 0; i < atk.wounds; i++)
		{
			damage += (Die::Roll(-atk.rend) > typeModel->GetStats().save) * atk.damage;
		}
		while (damage > 0 && Models.size() > 0)
		{
			damage = Models.back().TakeWounds(damage);
			if (damage > 0) Models.pop_back();
		}
	}

	
}

//Resolves battleshock, with a bool returning if the unit has been wiped out or not.
void Unit::TakeBattleshock()
{
	if (this->GetLive() == 0) return;
	//Calculate losses.
	int roll = Die::Roll();
	int numbersBonus = floor(Models.size()/10);
	int result = max(0, (roll + Losses) - (Models.front().GetStats().bravery + numbersBonus));
	//std::cout << "Battleshock - " << Name << " loses " << result << " models!" << std::endl;

	if (result >= Models.size()) Models.clear();
	for (int i = 0; i < result; i++) Models.pop_back();
}

void Unit::EndTurn()
{
	Losses = 0;
	for (auto& model : Models) model.EndTurn();
}

void Unit::PrintStats() 
{
	Printable::PrintHeader("Unit: " + Name, 1);
	Printable::PrintHeader("Type Model", 2);
	Models.at(0).PrintStats();
}