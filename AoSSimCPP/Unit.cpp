#include "stdafx.h"

#include "Unit.h"
#include "Model.h"


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

//
void Unit::MeleeAttack(Unit target, int frontage)
{
	Model type = target.TypeModel;
	uint8_t wounds = 0;
	for (auto m = Models->begin(); m != Models->end(); m++)
	{
		Model mod = *m;
		wounds += mod.MeleeAttack(&type);
	}
	std::cout << "Generate: " << wounds << " wounds!" << std::endl;
}

void Unit::TakeWounds(int count)
{
}

void Unit::Battleshock()
{
}
