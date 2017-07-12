#include "stdafx.h"

#include "Unit.h"
#include "Model.h"
#include "Die.h"


Unit::Unit(Model* model, int number)
{
	Models = new std::vector<Model*>;
	TypeModel = model;
	for (int i = 0; i < number; i++) { Models->push_back(new Model(model)); }

	Mult = ceil(number / model->GetSize());
	PointsValue = Mult * model->GetCost();
	Losses = 0;
}

Unit::~Unit()
{
	for (auto m = Models->begin(); m != Models->end(); m++)	delete(*m);
	delete(Models);
}

//Attack a target.
//Takes the profile model of the enemy unit, tests against it to generate wounds and then passes those wounds to the target unit.
void Unit::MeleeAttack(Unit target, int frontage)
{
	Model type = target.TypeModel;
	uint8_t wounds = 0;
	int i = 0;
	for (auto m = Models->begin(); m != Models->end(); m++)
	{
		if (i == frontage) break;
		Model mod = *m;
		wounds += mod.MeleeAttack(&type);
	}
	std::cout << "Generate: " << wounds << " wounds!" << std::endl;
	target.TakeWounds(wounds);
}

//Allocates wounds and returns whether or not the unit has been wiped out.
bool Unit::TakeWounds(int count)
{
	for (int i = Models->size() - 1; i > -1; i--)
	{
		Model* m = Models->at(i);
		if (m == nullptr) continue;
		if (m->GetWounds() > count)
		{
			m->TakeWounds(count); 
			return false;
		}

		else 
		{ 
			count -= m->GetWounds();
			delete(m);
			Models->pop_back();
			Losses++;
			if (Models->size() == 0) return true;
		}
	}
}

//Resolves battleshock, with a bool returning if the unit has been wiped out or not.
bool Unit::Battleshock()
{
	//Calculate losses.
	int roll = Roll();
	int bonus = floor(Models->size()/10);
	int result = max(0, (roll + Losses) - (TypeModel->GetBravery() + bonus));
	return true;
}

void Unit::NewTurn()
{
	Losses = 0;
}
