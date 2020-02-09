#include "stdafx.h"
#include "Battle.h"
#include "DataWriter.h"

Battle::Battle() :
	PhaseFunctions(),
	CurrentPhase( BattlePhase::Hero ),
	TurnCount(0)
{
	PhaseFunctions.insert({
		{ BattlePhase::Fight,			[=]() { return this->Battle::ResolveFight(); } },
		{ BattlePhase::Battleshock,		[=]() { return this->Battle::ResolveBattleshock(); } },
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

Battle::BattleStats Battle::FightBattle( BattlePhase startPhase )
{
	CurrentPhase = startPhase;

	while (CurrentPhase != BattlePhase::EndBattle)
	{
		CurrentPhase = (PhaseFunctions[CurrentPhase])();
	}

	BattleStats stats; 
	if (AttackingUnit->GetSurvivingModelsCount() > 0)
	{
		stats.Winner = AttackingUnit->GetName();
		stats.Survivors = AttackingUnit->GetSurvivingModelsCount();
	}
	else
	{
		stats.Winner = DefendingUnit->GetName();
		stats.Survivors = DefendingUnit->GetSurvivingModelsCount();
	}

	stats.Turns = TurnCount;
	return stats;
}

void Battle::SetUnit(std::shared_ptr<Model> model, size_t count, Side side)
{
	switch (side)
	{
	case Side::Attacker:
		AttackingUnit = std::make_unique<Unit>(model, count);
		break;
	case Side::Defender:
		DefendingUnit = std::make_unique<Unit>(model, count);
		break;
	default:
		break;
	}
}

BattlePhase Battle::ResolveFight()
{
	UnitAttack atk;
	{
		atk = AttackingUnit->MakeMeleeAttack(*DefendingUnit, 10);
		DefendingUnit->TakeAttacks(atk);
	}
	{
		atk = DefendingUnit->MakeMeleeAttack(*AttackingUnit, 10);
		AttackingUnit->TakeAttacks(atk);
	}

	if (AttackingUnit->GetSurvivingModelsCount() == 0 ||
		DefendingUnit->GetSurvivingModelsCount() == 0)
	{
		return BattlePhase::EndBattle;
	}
	return BattlePhase::Battleshock;
}

BattlePhase Battle::ResolveBattleshock()
{
	if (AttackingUnit->GetLosses() > 0)
	{
		AttackingUnit->TakeBattleshock();
	}

	if (DefendingUnit->GetLosses() > 0)
	{
		AttackingUnit->TakeBattleshock();
	}

	if (AttackingUnit->GetSurvivingModelsCount() == 0 ||
		DefendingUnit->GetSurvivingModelsCount() == 0)
	{
		return BattlePhase::EndBattle;
	}
	return BattlePhase::EndTurn;
}

BattlePhase Battle::ResolveEndTurn()
{
	TurnCount++;
	return BattlePhase::Fight;
}
