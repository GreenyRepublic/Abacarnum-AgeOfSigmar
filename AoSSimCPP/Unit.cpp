#include "stdafx.h"
#include "Unit.h"


Unit::Unit(const std::shared_ptr<Model> model, size_t count) :
	GameEntity(model->GetName(), model->GetFaction()),
	TypeModel(model),
	Name(model->GetName()),
	PointValue(model->GetUnitCost()* (count / model->GetUnitSize())),
	Losses(0)
{
	for (size_t i = 0; i < count; i++) 
	{ 
		Models.push_back(*model);
	}
}

Unit::~Unit()
{
}

//Attack a target.
//Takes the profile model of the enemy unit, tests against it to generate wounds and slaps them on the enemy unit.
UnitAttacks Unit::MeleeAttack(Unit& target, int frontage)
{
	UnitAttacks resultAttacks;

	size_t i = 0;
	for (Model& model : Models)
	{
		if (i++ == frontage) break;
		for (WeaponAttack& atk : model.MeleeAttack(target.GetTypeModel()))
		{
			resultAttacks.WeaponAttacks.push_back(atk);
		}
	}
	return resultAttacks;
}

//Allocates wounds.
void Unit::TakeAttacks(UnitAttacks attacks)
{
	
	//TODO: Feed attack items through modifier stack
	
	for (auto attack : attacks.WeaponAttacks)
	{
		std::vector<Wound> wounds;
		for (size_t i = 0; i < attack.Wounds.Count; i++)
		{
			if (!MakeSave(attack))
			{
				Wound wound;
				wound.Count = attack.WeaponProfile.damage;
				wound.Type = Normal;
				wounds.push_back(wound);
			}
		}
		while (!wounds.empty() && Models.size() > 0)
		{
			if ( Models.back().TakeDamage(wounds) > 0) Models.pop_back();
			wounds.pop_back();
		}
	}
}

//Resolves battleshock, with a bool returning if the unit has been wiped out or not.
void Unit::TakeBattleshock()
{
	if (this->GetSurvivingModels() == 0) return;
	//Calculate losses.
	int roll = Die::RollD6();
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

bool Unit::MakeSave(WeaponAttack attack)
{
	//TODO: Abilities here
	return (Die::RollD6() > TypeModel->GetStats().save + attack.WeaponProfile.rend);
}