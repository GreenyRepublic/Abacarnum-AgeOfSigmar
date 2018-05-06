#include "stdafx.h"

#include "Unit.h"
#include "Model.h"
#include "Die.h"


Unit::Unit(Model& model, int count)
{
	for (int i = 0; i < count; i++) { Models.push_back(Model(model)); }

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
	Model& type = target.Models.front;
	int wounds = 0;
	int i = 0;
	for (auto m : Models)
	{
		if (i == frontage) break;
		wounds += m.MeleeAttack(type);
		i++;
	}
	//std::cout << "Generate: " << wounds << " wounds!" << std::endl;
	
}

//Allocates wounds and returns whether or not the unit has been wiped out.
bool Unit::TakeWounds(int count)
{
	while(Models.size() > 0)
	{
		//std::cout << Models.size() << std::endl;
		Model m = Models.at(Models.size()-1);

		if (m.GetWounds() > count)
		{
			m.TakeWounds(count); 
			return false;
		}

		else 
		{ 
			count -= m.GetWounds();
			Models.pop_back();
			Losses++;
			//std::cout << count << std::endl;
		}
	}
	//std::cout << "DING " << Models.size() << std::endl;
	return true;
}

//Resolves battleshock, with a bool returning if the unit has been wiped out or not.
bool Unit::Battleshock()
{
	//Calculate losses.
	int roll = Roll();
	int bonus = floor(Models.size()/10);
	int result = max(0, (roll + Losses) - (TypeModel->GetBravery() + bonus));
	//std::cout << "Battleshock - " << Name << " loses " << result << " models!" << std::endl;

	if (result >= Models.size())
	{
		Models.clear();
		return true;
	}
	
	for (int i = 0; i < result; i++)
	{
		Models.pop_back();
	}
	return false;
}

void Unit::NewTurn()
{
	Losses = 0;
	for (auto model : Models) model.EndTurn();
}