#pragma once
#include "stdafx.h"
#include "GameEntity.h"
#include "types/ProfileTypes.h"
#include "types/ActionTypes.h"

// ### Unit: ### //
/* A unit consists of one or more models (as defined by the warscroll). 
 * A unit attacks as a unit, takes casualties as a unit, and takes battleshock tests as a unit
 * Within the scope of this program no other data (position, etc) is needed
 */

class Unit : public GameEntity
{
public:
	Unit(const ModelProfile& warscrollprofile, const size_t modelcount);
	~Unit();

	UnitAttackAction MakeMeleeAttack( const Unit& target, const int frontage = 10);
	UnitAttackAction MakeRangedAttack( const Unit& target) {};

	void ReceiveAttack( UnitAttackAction& attacks);
	void TakeBattleshock();		

	const ModelProfile& GetTypeModelProfile() const { return mTypeModel; }
	const size_t GetSurvivingModels() const { return mModelWoundCounts.size(); }
	const size_t GetTotalLosses() const { return mUnitSize - mModelWoundCounts.size(); }
	const size_t GetLossesThisTurn() const { return mLossesThisTurn; }

	void EndTurn();
	void PrintStats() {};

private:

	friend class DataWriter;

	bool MakeSaves(AttackAction attack);
	bool TakeDamage(size_t count);

	const ModelProfile mTypeModel;
	const size_t mUnitSize;				//How many models we start off with.
	std::vector<size_t> mModelWoundCounts;	//Models are homogenous across a unit (for now!) so we represent them as a simple array of wound counts.
	size_t mLossesThisTurn;
};

