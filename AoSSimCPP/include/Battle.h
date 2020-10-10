#pragma once
#include "stdafx.h"
#include "types/ActionTypes.h"
#include "Unit.h"

enum class Side
{
	Attacker,
	Defender
};

enum class BattlePhase
{
	Hero		= 0,
	Move		= 1,
	Shoot		= 2,
	Charge		= 3,
	Fight		= 4,
	Battleshock	= 5,
	EndTurn		= 6,
	EndBattle	= 7,

	PhaseCount
};

class Battle
{
public:

	typedef std::pair < BattlePhase, std::function<BattlePhase>> PhaseFunction;

	Battle();
	~Battle();
	void SingleBattle( BattlePhase start = BattlePhase::Fight );
	void BatchBattle( BattlePhase start = BattlePhase::Fight );
	void SetUnit( const ModelProfile& model, size_t count, Side side);

	BattlePhase ResolveHero() { return BattlePhase::EndTurn; }
	BattlePhase ResolveMovement() { return BattlePhase::EndTurn; }
	BattlePhase ResolveShooting() { return BattlePhase::EndTurn; }
	BattlePhase ResolveCharge() { return BattlePhase::EndTurn; }
	BattlePhase ResolveFight();
	BattlePhase ResolveBattleshock();
	BattlePhase ResolveEndTurn();
	
	std::map<BattlePhase, std::function<BattlePhase(void)>> PhaseFunctions;

private:
	friend class DataWriter;
	class BattleStats
	{
	public:
		void SetWinner(const Unit& unit) 
		{
			mWinnerName = unit.GetName();
			mSurvivingModels = unit.GetSurvivingModels();
		}
		
		void SetTurns(const size_t turns)
		{
			mTurns = turns;
		}

		std::string GetWinnerName() const { return mWinnerName; }
		size_t GetWinnerSurvivingModels() const { return mSurvivingModels; }
		size_t GetNumberOfTurns() const { return mTurns; }

	private:
		std::string mWinnerName{ "" };
		size_t mSurvivingModels{ 0 };
		size_t mTurns{ 0 };
	};

	struct BatchBattleData
	{
		BatchBattleData() {};

		inline BatchBattleData& operator+=(BattleStats& stats)
		{
			size_t prevDenom = mTotalBattles++;
			mAverageSurvivors *= (static_cast<float>(prevDenom) / mTotalBattles);
			mAverageTurns *= (static_cast<float>(prevDenom) / mTotalBattles);

			mAverageSurvivors += (static_cast<float>(stats.GetWinnerSurvivingModels())) / mTotalBattles;
			mAverageTurns += (static_cast<float>(stats.GetNumberOfTurns())) / mTotalBattles;

			mTotalWins[stats.GetWinnerName()] += 1;
			if (mTotalWins[stats.GetWinnerName()] > mCurrentMax)
			{
				mCurrentMax = mTotalWins[stats.GetWinnerName()];
				mMostWins = stats.GetWinnerName();
			}
			return *this;
		}

		std::string mMostWins{ "" };
		size_t mTotalBattles{ 0 };
		float mAverageSurvivors{ 0 };
		float mAverageTurns{ 0 };

		std::map<std::string, size_t> mTotalWins{};
		size_t mCurrentMax{ 0 };
	};

	BattleStats FightBattle( BattlePhase start );

	BattlePhase mCurrentPhase;
	size_t mTurnCount;
	std::map<Side, std::shared_ptr<Unit>> mCombatants;
};
