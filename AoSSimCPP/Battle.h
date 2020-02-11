#pragma once
#include "stdafx.h"
#include "Unit.h"

enum class Side
{
	Attacker,
	Defender
};

enum class BattlePhase
{
	Hero,
	Move,
	Shoot,	
	Charge,
	Fight,
	Battleshock,
	EndTurn,
	EndBattle
};

class Battle
{
public:

	typedef std::pair < BattlePhase, std::function<BattlePhase>> PhaseFunction;

	Battle();
	~Battle();
	void SingleBattle( BattlePhase start = BattlePhase::Fight );
	void BatchBattle( BattlePhase start = BattlePhase::Fight );
	void SetUnit( std::shared_ptr<ModelProfile> model, size_t count, Side side);

	/*virtual BattlePhase ResolveHero();
	virtual BattlePhase ResolveMovement();
	virtual BattlePhase ResolveShooting();
	virtual BattlePhase ResolveCharge();*/
	BattlePhase ResolveFight();
	BattlePhase ResolveBattleshock();
	BattlePhase ResolveEndTurn();
	
	std::map<BattlePhase, std::function<BattlePhase(void)>> PhaseFunctions;
	BattlePhase CurrentPhase;
	size_t TurnCount;

	std::unique_ptr<Unit> AttackingUnit;
	std::unique_ptr<Unit> DefendingUnit;

private:
	friend class DataWriter;
	struct BattleStats
	{
		std::string Winner{ "" };
		size_t Survivors{ 0 };
		size_t Turns{ 0 };
	};

	struct BatchBattleData
	{
		BatchBattleData() : totalWins() {};

		inline BatchBattleData& operator+=(BattleStats& stats)
		{
			size_t prevDenom = TotalBattles++;
			AverageSurvivors *= (static_cast<float>(prevDenom) / TotalBattles);
			AverageTurns *= (static_cast<float>(prevDenom) / TotalBattles);

			AverageSurvivors += (static_cast<float>(stats.Survivors)) / TotalBattles;
			AverageTurns += (static_cast<float>(stats.Turns)) / TotalBattles;

			totalWins[stats.Winner] += 1;
			if (totalWins[stats.Winner] > currentMax)
			{
				currentMax = totalWins[stats.Winner];
				MostWins = stats.Winner;
			}
			return *this;
		}

		std::string MostWins{ "" };
		size_t TotalBattles{ 0 };
		float AverageSurvivors{ 0 };
		float AverageTurns{ 0 };

		std::map<std::string, size_t> totalWins;
		size_t currentMax{ 0 };
	};

	BattleStats FightBattle( BattlePhase start );
};
