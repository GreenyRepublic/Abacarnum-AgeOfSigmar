#include "stdafx.h"
#include "Unit.h"


Unit::Unit(const ModelProfile& modelprofile, size_t modelcount) :
	GameEntity(modelprofile.name),
	mUnitProfile(modelprofile, modelcount)
{
}

Unit::~Unit()
{
}

// Attack a target.
// Takes the profile model of the enemy unit and generate attacks.
UnitAttackAction Unit::MakeMeleeAttack(const UnitProfile& target, const int frontage)
{
	UnitAttackAction resultAttacks;
	resultAttacks.UnitProfile = mUnitProfile;

	return resultAttacks;
}

//Allocates wounds.
void Unit::TakeAttacks(const UnitAttackAction& attack)
{
	//TODO: Feed attack items through modifier stack
	
	for (const auto& attack : attack.AttackProfiles)
	{
		for (size_t i = 0; i < attack.wounds; i++)
		{	
		}
	}
}

void Unit::TakeBattleshock()
{
	
}

void Unit::EndTurn()
{ 

}

bool Unit::MakeSaves(AttackAction attack)
{

}