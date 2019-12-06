#include "stdafx.h"
#include "Battle.h"
#include "DataWriter.h"

Battle::Battle() :
	PhaseFunctions(
		{ { BattlePhase::Fight, &Battle::ResolveFight },
		{ BattlePhase::Battleshock, &Battle::ResolveBattleshock } } ),
	CurrentPhase( BattlePhase::Hero ),
	TurnCount(0)
{
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

Battle::BattleStats Battle::FightBattle( BattlePhase start )
{
	CurrentPhase = start;

	while (CurrentPhase != BattlePhase::End)
	{
		CurrentPhase = (this->*PhaseFunctions[CurrentPhase])();
	}

	BattleStats stats;
	if (AttackingUnit->GetSurvivingModels() > 0)
	{
		stats.Winner = AttackingUnit->GetName();
		stats.Survivors = AttackingUnit->GetSurvivingModels();
	}
	else
	{
		stats.Winner = DefendingUnit->GetName();
		stats.Survivors = DefendingUnit->GetSurvivingModels();
	}

	stats.Turns = TurnCount;
	return stats;
}

void Battle::SetUnit(std::shared_ptr<Model> model, size_t count, Side side)
{
	switch (side)
	{
	case Attacker:
		AttackingUnit = std::make_unique<Unit>(model, count);
		break;
	case Defender:
		DefendingUnit = std::make_unique<Unit>(model, count);
		break;
	default:
		break;
	}
}

BattlePhase Battle::ResolveFight()
{
	TurnCount++;

	UnitAttacks atk;
	{
		atk = AttackingUnit->MeleeAttack(*DefendingUnit, 10);
		DefendingUnit->TakeAttacks(atk);
	}
	{
		atk = DefendingUnit->MeleeAttack(*AttackingUnit, 10);
		AttackingUnit->TakeAttacks(atk);
	}

	if (AttackingUnit->GetSurvivingModels() == 0 ||
		DefendingUnit->GetSurvivingModels() == 0)
	{
		return BattlePhase::End;
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

	if (AttackingUnit->GetSurvivingModels() == 0 ||
		DefendingUnit->GetSurvivingModels() == 0)
	{
		return BattlePhase::End;
	}
	return BattlePhase::Fight;
}
