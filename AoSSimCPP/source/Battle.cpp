#include "stdafx.h"
#include "Battle.h"
#include "DataWriter.h"

Battle::Battle() :
	PhaseFunctions(),
	mCurrentPhase( BattlePhase::Hero ),
	mTurnCount(0)
{
	PhaseFunctions.insert({
		{ BattlePhase::Fight,			[=]() { return this->Battle::ResolveFight(); } },
		{ BattlePhase::Battleshock,		[=]() { return this->Battle::ResolveBattleshock(); } },
		{ BattlePhase::EndTurn,			[=]() { return this->Battle::ResolveEndTurn(); } },
		});

}

Battle::~Battle()
{
		
}

void Battle::SingleBattle(BattlePhase start)
{
	BattleStats stats = FightBattle(start);
}

void Battle::BatchBattle(BattlePhase start)
{
}

Battle::BattleStats Battle::FightBattle( BattlePhase startPhase)
{
	mCurrentPhase = startPhase;

	while (mCurrentPhase != BattlePhase::EndBattle)
	{
		mCurrentPhase = (PhaseFunctions[mCurrentPhase])();
	}

	BattleStats stats; 

	(mCombatants[Side::Attacker]->GetSurvivingModels() > 0) ? 
		stats.SetWinner(*mCombatants[Side::Attacker]) : 
		stats.SetWinner(*mCombatants[Side::Defender]) ;

	stats.SetTurns(mTurnCount);

	return stats;
}

void Battle::SetUnit(const ModelProfile& model, size_t count, Side side)
{
	mCombatants[side] = std::make_shared<Unit>(model, count);
}

BattlePhase Battle::ResolveFight()
{
	for (size_t i = 0; i <= 1; ++i)
	{
		Side currentSide = static_cast<Side>(i);
		Side otherSide = static_cast<Side>((i + 1) % 2);

		auto attack = mCombatants[currentSide]->MakeMeleeAttack(*mCombatants[otherSide]);
		mCombatants[otherSide]->ReceiveAttack(attack);

		if (!mCombatants[currentSide]->GetSurvivingModels() ||
			!mCombatants[otherSide]->GetSurvivingModels())
		{
			return BattlePhase::EndBattle;
		}
	}
	return BattlePhase::Battleshock;
}

BattlePhase Battle::ResolveBattleshock()
{
	mCombatants[Side::Attacker]->TakeBattleshock();
	mCombatants[Side::Defender]->TakeBattleshock();
	
	if (mCombatants[Side::Attacker]->GetSurvivingModels() == 0 ||
		mCombatants[Side::Defender]->GetSurvivingModels() == 0)
	{
		return BattlePhase::EndBattle;
	}

	return BattlePhase::EndTurn;
}

BattlePhase Battle::ResolveEndTurn()
{
	mTurnCount++;
	return BattlePhase::Fight;
}
