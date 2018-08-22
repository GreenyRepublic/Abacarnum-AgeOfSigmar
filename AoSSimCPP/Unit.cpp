#include "stdafx.h"
#include "Unit.h"


Unit::Unit(Model& model, int count)
{

	for (int i = 0; i < count; i++) { Models.push_back(Model(model)); }
	Name = model.GetName();
	modelsPerBatch = ceil(count / model.GetSize());
	pointValue = modelsPerBatch * model.GetCost();
	Losses = 0;
}

Unit::~Unit()
{	
}

//Attack a target.
//Takes the profile model of the enemy unit, tests against it to generate wounds and slaps them on the enemy unit.
void Unit::MeleeAttack(Unit& target, int frontage)
{
	Model& type = target.Models.back();
	int wounds = 0;
	int i = 0;
	for (auto m : Models)
	{
		if (i == frontage) break;
		wounds += m.MeleeAttack(type);
		i++;
	}
	target.TakeWounds(wounds);
}

//Allocates wounds and deletes if the unit has been wiped out.
void Unit::TakeWounds(int wounds)
{
	while (wounds > 0)
	{
		wounds = Models.back().TakeWounds(wounds);
	}
}

//Resolves battleshock, with a bool returning if the unit has been wiped out or not.
void Unit::TakeBattleshock()
{
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
	for (auto model : Models) model.EndTurn();
}

void Unit::PrintStats() { }