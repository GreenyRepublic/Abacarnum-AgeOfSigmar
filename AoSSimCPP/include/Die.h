#pragma once
#include "stdafx.h"
// Die roller, basically a helper/macro for the <random> lib

class Die
{
public:
	static int RollD3();
	static int RollD6();

private:
	Die() {};
	~Die();
	static std::uniform_int_distribution<unsigned int> dieDistribution;
	static std::default_random_engine dieGenerator;
};

// Encapsulates a die roll, and whether or not it was a success
// This will be useful for, say, abilities that trigger when a die roll is a certain value or higher, etc.
class DieRoll
{
public:
	DieRoll(size_t roll, size_t target) : mRollResult(roll), mRollTarget(target) {};
	DieRoll(size_t target) : mRollResult(Die::RollD6()), mRollTarget(target) {};
	
	const bool RollSucceeded() const { 
		return mRollResult >= mRollTarget &&
			mRollResult != 1; 
	}

	void ModifyRollResult(const int modifier)
	{
		mRollResult = max(mRollResult + modifier, 1);
	}

	void ModifyRollTarget(const int modifier)
	{
		mRollTarget = max(mRollTarget + modifier, 1);
	}

private:
	DieRoll() = delete;
	size_t mRollResult;
	size_t mRollTarget;
};
