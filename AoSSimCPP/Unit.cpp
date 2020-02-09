#include "stdafx.h"
#include "Unit.h"


Unit::Unit(const std::shared_ptr<Model> model, size_t count) :
	GameEntity(model->GetName(), model->GetFaction()),
	TypeModel(model),
	mEntityName(model->GetName()),
	mPointValue(model->GetUnitCost()* (count / model->GetUnitSize())),
	mLosses(0)
{
	for (size_t i = 0; i < count; i++) 
	{ 
		Models.push_back(*model);
	}
}

Unit::~Unit()
{
}

// Attack a target.
// Takes the profile model of the enemy unit and generate attacks.
UnitAttack Unit::MakeMeleeAttack(UnitProfile& target, const int frontage = 10)
{
	UnitAttack resultAttacks;

	size_t i = 0;
	for (size_t i = 0; i < mUnitProfile.currentModels.size(); ++i)
	{
		if (i == frontage) break;
		for (auto& atk : model.MeleeAttack(target.GetTypeModel()))
		{
			resultAttacks.WeaponAttacks.push_back(atk);
		}
	}
	return resultAttacks;
}

//Allocates wounds.
void Unit::TakeAttacks(UnitAttack attacks)
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
	if (this->GetSurvivingModelsCount() == 0) return;
	//Calculate losses.
	int roll = Die::RollD6();
	int numbersBonus = floor(Models.size()/10);
	int result = max(0, (roll + mLosses) - (Models.front().GetStats().bravery + numbersBonus));
	//std::cout << "Battleshock - " << Name << " loses " << result << " models!" << std::endl;

	if (result >= Models.size()) Models.clear();
	for (int i = 0; i < result; i++) Models.pop_back();
}

void Unit::EndTurn()
{
	mLosses = 0;
	for (auto& model : Models) model.EndTurn();
}

bool Unit::MakeSave(WeaponAttack attack)
{
	//TODO: Abilities here
	return (Die::RollD6() > TypeModel->GetStats().save + attack.WeaponProfile.rend);
}